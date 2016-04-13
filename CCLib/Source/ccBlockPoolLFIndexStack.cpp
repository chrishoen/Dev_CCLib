/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "cc_functions.h"
#include "ccDefs.h"
#include "ccMemoryPtr.h"
#include "ccBlockPoolLFIndexStack.h"

using namespace std;

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

int BlockPoolLFIndexStackState::getMemorySize()
{
   return cc_round_upto16(sizeof(BlockPoolLFIndexStackState));
}

BlockPoolLFIndexStackState::BlockPoolLFIndexStackState()
{
   // All null.
   mFreeListNumNodes = 0;
}

void BlockPoolLFIndexStackState::initialize(BlockPoolParms* aParms)
{
   // Do not initialize, if already initialized.
   if (!aParms->mConstructorFlag) return;

   // Allocate for one extra dummy node.
   mFreeListNumNodes = aParms->mNumBlocks + 1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This local class calculates and stores the memory sizes needed by the class.

class BlockPoolLFIndexStack::MemorySize
{
public:
   // Members.
   int mStateSize;
   int mFreeListNextSize;
   int mMemorySize;

   // Calculate and store memory sizes.
   MemorySize::MemorySize(BlockPoolParms* aParms)
   {
      mStateSize         = BlockPoolLFIndexStackState::getMemorySize();
      mFreeListNextSize  = cc_round_upto16(cNewArrayExtraMemory + (aParms->mNumBlocks + 1)*sizeof(AtomicLFIndex));
      mMemorySize = mStateSize + mFreeListNextSize;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockPoolLFIndexStack::getMemorySize(BlockPoolParms* aParms)
{
   MemorySize tMemorySize(aParms);
   return tMemorySize.mMemorySize;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

BlockPoolLFIndexStack::BlockPoolLFIndexStack()
{
   // All null.
   mX = 0;
   mFreeListNext = 0;
   mOwnMemoryFlag = false;
   mMemory = 0;
}

BlockPoolLFIndexStack::~BlockPoolLFIndexStack()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void BlockPoolLFIndexStack::initialize(BlockPoolParms* aParms,void* aMemory)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize memory.

   // Deallocate memory, if any exists.
   finalize();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mMemory = malloc(BlockPoolLFIndexStack::getMemorySize(aParms));
      mOwnMemoryFlag = true;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mOwnMemoryFlag = false;
   }

   // Calculate memory sizes.
   MemorySize tMemorySize(aParms);

   // Calculate memory addresses.
   MemoryPtr tMemoryPtr(mMemory);

   char* tStateMemory        = tMemoryPtr.cfetch_add(tMemorySize.mStateSize);
   char* tFreeListNextMemory = tMemoryPtr.cfetch_add(tMemorySize.mFreeListNextSize);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Construct the state.
   if (aParms->mConstructorFlag)
   {
      // Call the constructor.
      mX = new(tStateMemory)BlockPoolLFIndexStackState;
   }
   else
   {
      // The constructor has already been called.
      mX = (BlockPoolLFIndexStackState*)tStateMemory;
   }
   // Initialize the state.
   mX->initialize(aParms);

   // Construct the linked list array.
   if (aParms->mConstructorFlag)
   {
      // Call the constructor.
      mFreeListNext = new(tFreeListNextMemory)AtomicLFIndex[mX->mFreeListNumNodes];
   }
   else
   {
      // The constructor has already been called.
      mFreeListNext = (AtomicLFIndex*)tFreeListNextMemory;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Initialize linked list, if it has not already been initialized.
   if (aParms->mConstructorFlag)
   {
      // Initialize linked list array. Each node next node is the one after it.
      for (int i = 0; i < mX->mFreeListNumNodes - 1; i++)
      {
         mFreeListNext[i].store(LFIndex(i + 1, 0));
      }
      // The last node has no next node.
      mFreeListNext[mX->mFreeListNumNodes - 1].store(LFIndex(cInvalid, 0));

      // List head points to the first node.
      mX->mFreeListHead.store(LFIndex(0, 0));
      // List size is initially a full stack.
      mX->mFreeListSize = mX->mFreeListNumNodes;

      // Pop the dummy node.
      int tDummyNode;
      pop(&tDummyNode);
   }
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Deallocate memory for the stack.

void BlockPoolLFIndexStack::finalize()
{
   if (mOwnMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
   }
   mMemory = 0;
   mOwnMemoryFlag = false;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Size

int BlockPoolLFIndexStack::size()
{ 
   return mX->mFreeListSize.load(memory_order_relaxed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This detaches the head node.
// Use an offset of one so that pop and push indices range 0..NumElements-1.

bool BlockPoolLFIndexStack::pop(int* aNodeIndex)
{
   // Store the head node in a temp.
   // This is the node that will be detached.
   LFIndex tHead = mX->mFreeListHead.load(memory_order_relaxed);

   int tLoopCount=0;
   while (true)
   {
      // Exit if the list is empty.
      if (tHead.mIndex == cInvalid) return false;

      // Set the head node to be the node that is after the head node.
      if (mX->mFreeListHead.compare_exchange_weak(tHead, LFIndex(mFreeListNext[tHead.mIndex].load(memory_order_relaxed).mIndex,tHead.mCount+1),memory_order_acquire,memory_order_relaxed)) break;

      if (++tLoopCount==10000) throw 103;
   }
   mX->mFreeListSize.fetch_sub(1,memory_order_relaxed);

   // Return the detached original head node.
   *aNodeIndex = tHead.mIndex - 1;
   return true;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Insert a node into the list before the list head node.
// Use an offset of one so that pop and push indices range 0..NumElements-1.

bool BlockPoolLFIndexStack::push(int aNodeIndex)
{
   int tNodeIndex = aNodeIndex + 1;

   // Store the head node in a temp.
   LFIndex tHead = mX->mFreeListHead.load(memory_order_relaxed);

   int tLoopCount=0;
   while (true)
   {
      // Attach the head node to the pushed node.
      mFreeListNext[tNodeIndex].store(tHead,memory_order_relaxed);

      // The pushed node is the new head node.
      atomic<int>* tListHeadIndexPtr = (std::atomic<int>*)&mX->mFreeListHead;
      if ((*tListHeadIndexPtr).compare_exchange_weak(tHead.mIndex, tNodeIndex,memory_order_release,memory_order_relaxed)) break;
      if (++tLoopCount == 10000) throw 103;
   }

   // Done.
   mX->mFreeListSize.fetch_add(1,memory_order_relaxed);
   return true;
}

}//namespace
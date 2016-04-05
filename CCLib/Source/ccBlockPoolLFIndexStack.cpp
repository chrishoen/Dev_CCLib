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
#include "ccBlockPoolLFIndexStack.h"

using namespace std;

namespace CC
{

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Constructor, initialize members for an empty stack of size zero 

BlockPoolLFIndexStackState::BlockPoolLFIndexStackState()
{
   // All null.
   mNumElements     = 0;
   mListNumElements = 0;
}

void BlockPoolLFIndexStackState::initialize(BlockPoolParms* aParms)
{
   // Store.
   mNumElements     = aParms->mNumBlocks;
   // Allocate for one extra dummy node.
   mListNumElements = aParms->mNumBlocks + 1;
}

int BlockPoolLFIndexStackState::getMemorySize()
{
   return cc_round_upto16(sizeof(BlockPoolLFIndexStackState));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

BlockPoolLFIndexStack::BlockPoolLFIndexStack()
{
   // All null.
   mX = 0;
   mListNext = 0;
   mFreeMemoryFlag = false;
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
      mFreeMemoryFlag = true;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mFreeMemoryFlag = false;
   }

   // Calculate memory sizes.
   int tStateSize = BlockPoolLFIndexStackState::getMemorySize();
   int tArraySize = (aParms->mNumBlocks + 1)*sizeof(AtomicLFIndex);

   // Calculate memory addresses.
   char* tStateMemory   = (char*)mMemory;
   char* tArrayMemory = tStateMemory + tStateSize;

   // Initialize state.
   mX = new(tStateMemory) BlockPoolLFIndexStackState;
   mX->initialize(aParms);

   // Initialize the linked list array.
   mListNext = new(tArrayMemory) AtomicLFIndex[mX->mListNumElements];

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Initialize linked list array. Each node next node is the one after it.
   for (int i = 0; i < mX->mListNumElements-1; i++)
   {
      mListNext[i].store(LFIndex(i+1,0));
   }
   // The last node has no next node.
   mListNext[mX->mListNumElements-1].store(LFIndex(cInvalid,0));

   // List head points to the first node.
   mX->mListHead.store(LFIndex(0,0));
   // List size is initially a full stack.
   mX->mListSize = mX->mListNumElements;

   // Pop the dummy node.
   int tDummyNode;
   pop(&tDummyNode);
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Finalize

void BlockPoolLFIndexStack::finalize()
{
   if (mFreeMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
   }
   mMemory = 0;
   mFreeMemoryFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockPoolLFIndexStack::getMemorySize(BlockPoolParms* aParms)
{
   int tStateSize = BlockPoolLFIndexStackState::getMemorySize();
   int tArraySize = (aParms->mNumBlocks + 1)*sizeof(AtomicLFIndex);
   int tMemorySize = tStateSize + tArraySize;
   return tMemorySize;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Size

int BlockPoolLFIndexStack::size()
{ 
   return mX->mListSize.load(memory_order_relaxed);
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
   LFIndex tHead = mX->mListHead.load(memory_order_relaxed);

   int tLoopCount=0;
   while (true)
   {
      // Exit if the list is empty.
      if (tHead.mIndex == cInvalid) return false;

      // Set the head node to be the node that is after the head node.
      if (mX->mListHead.compare_exchange_weak(tHead, LFIndex(mListNext[tHead.mIndex].load(memory_order_relaxed).mIndex,tHead.mCount+1),memory_order_acquire,memory_order_relaxed)) break;

      if (++tLoopCount==10000) throw 103;
   }
   mX->mListSize.fetch_sub(1,memory_order_relaxed);

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
   LFIndex tHead = mX->mListHead.load(memory_order_relaxed);

   int tLoopCount=0;
   while (true)
   {
      // Attach the head node to the pushed node.
      mListNext[tNodeIndex].store(tHead,memory_order_relaxed);

      // The pushed node is the new head node.
      atomic<int>* tListHeadIndexPtr = (std::atomic<int>*)&mX->mListHead;
      if ((*tListHeadIndexPtr).compare_exchange_weak(tHead.mIndex, tNodeIndex,memory_order_release,memory_order_relaxed)) break;
      if (++tLoopCount == 10000) throw 103;
   }

   // Done.
   mX->mListSize.fetch_add(1,memory_order_relaxed);
   return true;
}

}//namespace
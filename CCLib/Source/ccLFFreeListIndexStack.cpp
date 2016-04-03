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
#include "ccLFFreeListIndexStack.h"

using namespace std;

namespace CC
{

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Constructor, initialize members for an empty stack of size zero 

LFFreeListIndexStackState::LFFreeListIndexStackState()
{
   // All null.
   mNumElements = 0;
   mListAllocate = 0;
}

void LFFreeListIndexStackState::initialize(int aNumElements)
{
   // Store.
   mNumElements  = aNumElements;
   // Allocate for one extra dummy node.
   mListAllocate = aNumElements + 1;
}

int LFFreeListIndexStackState::getMemorySize()
{
   return cc_round_upto16(sizeof(LFFreeListIndexStackState));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

LFFreeListIndexStack::LFFreeListIndexStack()
{
   // All null.
   mX = 0;
   mListNext = 0;
   mExternalMemoryFlag = false;
   mMemory = 0;
}

LFFreeListIndexStack::~LFFreeListIndexStack()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void LFFreeListIndexStack::initialize(int aNumElements,void* aMemory)
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
      mMemory = malloc(LFFreeListIndexStack::getMemorySize(aNumElements));
      mExternalMemoryFlag = false;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mExternalMemoryFlag = true;
   }

   // Calculate memory sizes.
   int tStateSize = LFFreeListIndexStackState::getMemorySize();
   int tArraySize = (aNumElements + 1)*sizeof(AtomicLFIndex);

   // Calculate memory addresses.
   char* tStateMemory   = (char*)mMemory;
   char* tArrayMemory = tStateMemory + tStateSize;

   // Initialize state.
   mX = new(tStateMemory) LFFreeListIndexStackState;
   mX->initialize(aNumElements);

   // Initialize the linked list array.
   mListNext = new(tArrayMemory) AtomicLFIndex[mX->mListAllocate];

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Initialize linked list array. Each node next node is the one after it.
   for (int i = 0; i < mX->mListAllocate-1; i++)
   {
      mListNext[i].store(LFIndex(i+1,0));
   }
   // The last node has no next node.
   mListNext[mX->mListAllocate-1].store(LFIndex(cInvalid,0));

   // List head points to the first node.
   mX->mListHead.store(LFIndex(0,0));
   // List size is initially a full stack.
   mX->mListSize = mX->mListAllocate;

   // Pop the dummy node.
   int tDummyNode;
   pop(&tDummyNode);
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Finalize

void LFFreeListIndexStack::finalize()
{
   if (!mExternalMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
      mMemory = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int LFFreeListIndexStack::getMemorySize(int aNumElements)
{
   int tStateSize = LFFreeListIndexStackState::getMemorySize();
   int tArraySize = (aNumElements + 1)*sizeof(AtomicLFIndex);
   int tMemorySize = tStateSize + tArraySize;
   return tMemorySize;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Size

int LFFreeListIndexStack::size()
{ 
   return mX->mListSize.load(memory_order_relaxed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This detaches the head node.
// Use an offset of one so that pop and push indices range 0..NumElements-1.

bool LFFreeListIndexStack::pop(int* aNodeIndex)
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

bool LFFreeListIndexStack::push(int aNodeIndex)
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
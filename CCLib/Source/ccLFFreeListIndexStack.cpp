/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "ccLFFreeListIndexStack.h"

using namespace std;

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

LFFreeListIndexStack::LFFreeListIndexStack()
{
   // All null
   mMemory = 0;
   mListNext = 0;
   mNumElements = 0;
}

LFFreeListIndexStack::~LFFreeListIndexStack()
{
   finalize();
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Initialize

void LFFreeListIndexStack::initialize(int aNumElements)
{
   finalize();

   
   mNumElements  = aNumElements;
   mListAllocate = aNumElements + 1;
   mListNext = new AtomicLFIndex[mListAllocate];

   for (int i = 0; i < mListAllocate-1; i++)
   {
      mListNext[i].store(LFIndex(i+1,0));
   }

   mListNext[mListAllocate-1].store(LFIndex(cInvalid,0));

   mListHead.store(LFIndex(0,0));
   mListSize = mListAllocate;

   int tDummyNode;
   pop(&tDummyNode);
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Finalize

void LFFreeListIndexStack::finalize()
{
   if (mMemory)    free(mMemory);
   if (mListNext)  free(mListNext);
   mMemory    = 0;
   mListNext  = 0;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Size

int LFFreeListIndexStack::size()
{ 
   return mListSize.load(memory_order_relaxed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This detaches the head node.

bool LFFreeListIndexStack::pop(int* aNodeIndex)
{
   // Store the head node in a temp.
   // This is the node that will be detached.
   LFIndex tHead = mListHead.load(memory_order_relaxed);

   int tLoopCount=0;
   while (true)
   {
      // Exit if the list is empty.
      if (tHead.mIndex == cInvalid) return false;

      // Set the head node to be the node that is after the head node.
      if (mListHead.compare_exchange_weak(tHead, LFIndex(mListNext[tHead.mIndex].load(memory_order_relaxed).mIndex,tHead.mCount+1),memory_order_acquire,memory_order_relaxed)) break;

      if (++tLoopCount==10000) throw 103;
   }
   mListSize.fetch_sub(1,memory_order_relaxed);

   // Return the detached original head node.
   *aNodeIndex = tHead.mIndex;
   return true;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Insert a node into the list before the list head node.

bool LFFreeListIndexStack::push(int aNodeIndex)
{
   int tNodeIndex = aNodeIndex;

   // Store the head node in a temp.
   LFIndex tHead = mListHead.load(memory_order_relaxed);

   int tLoopCount=0;
   while (true)
   {
      // Attach the head node to the pushed node.
      mListNext[tNodeIndex].store(tHead,memory_order_relaxed);

      // The pushed node is the new head node.
      if ((*mListHeadIndexPtr).compare_exchange_weak(tHead.mIndex, tNodeIndex,memory_order_release,memory_order_relaxed)) break;
      if (++tLoopCount == 10000) throw 103;
   }

   // Done.
   mListSize.fetch_add(1,memory_order_relaxed);
   return true;
}

}//namespace
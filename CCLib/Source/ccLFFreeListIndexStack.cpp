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

   // Store.
   mNumElements  = aNumElements;
   // Allocate for one extra dummy node.
   mListAllocate = aNumElements + 1;

   // Allocate linked list array.
   mListNext = new AtomicLFIndex[mListAllocate];
   // Initialize it. Each node next node is the one after it.
   for (int i = 0; i < mListAllocate-1; i++)
   {
      mListNext[i].store(LFIndex(i+1,0));
   }
   // The last node has no next node.
   mListNext[mListAllocate-1].store(LFIndex(cInvalid,0));

   // List head points to the first node.
   mListHead.store(LFIndex(0,0));
   // List size is initially full.
   mListSize = mListAllocate;

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
   if (mListNext)
   {
      free(mListNext);
   }
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
// Use an offset of one so that pop and push indices range 0..NumElements-1.

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
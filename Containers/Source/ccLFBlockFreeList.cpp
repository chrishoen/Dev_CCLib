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

#include "ccLFBlockFreeList.h"

using namespace std;

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

LFBlockFreeList::LFBlockFreeList()
{
   // All null
   mMemory = 0;
   mListNext = 0;
   mListAllocate = 0;
}

LFBlockFreeList::~LFBlockFreeList()
{
   finalize();
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Initialize

void LFBlockFreeList::initialize(int aAllocate,int aBlockSize)
{
   finalize();

   mBlockSize     = aBlockSize;
   mListAllocate  = aAllocate + 1;

   mMemory = malloc(mListAllocate*mBlockSize);
   mListNext = new AtomicLFIndex[mListAllocate];

   for (int i = 0; i < mListAllocate-1; i++)
   {
      mListNext[i].store(LFIndex(i+1,0));
   }

   mListNext[mListAllocate-1].store(LFIndex(cInvalid,0));

   mListHead.store(LFIndex(0,0));
   mListSize = mListAllocate;

   BaseLFBlock* tDummyBlock = listPop();
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Finalize

void LFBlockFreeList::finalize()
{
   if (mMemory)    free(mMemory);
   if (mListNext)  free(mListNext);
   mMemory    = 0;
   mListNext  = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a block, based on block array index

void* LFBlockFreeList::element(int aIndex)
{
   return (void*)((char*)mMemory + mBlockSize*aIndex);
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Size

int LFBlockFreeList::size()
{ 
   return mListSize.load(memory_order_relaxed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This detaches the head node.

BaseLFBlock* LFBlockFreeList::listPop()
{
   // Store the head node in a temp.
   // This is the node that will be detached.
   LFIndex tHead = mListHead.load(memory_order_relaxed);

   int tLoopCount=0;
   while (true)
   {
      // Exit if the list is empty.
      if (tHead.mIndex == cInvalid) return 0;

      // Set the head node to be the node that is after the head node.
      if (mListHead.compare_exchange_weak(tHead, LFIndex(mListNext[tHead.mIndex].load(memory_order_relaxed).mIndex,tHead.mCount+1),memory_order_acquire,memory_order_relaxed)) break;

      if (++tLoopCount==10000) throw 103;
   }
   mListSize.fetch_sub(1,memory_order_relaxed);

   // Return the detached original head node.
   int tNodeIndex = tHead.mIndex;
   BaseLFBlock* tBlock = (BaseLFBlock*)element(tNodeIndex);
   tBlock->mLFNodeIndex = tHead.mIndex;
   return tBlock;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Insert a node into the list before the list head node.

bool LFBlockFreeList::listPush(BaseLFBlock* aBlock)
{
   int tNodeIndex = aBlock->mLFNodeIndex;

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
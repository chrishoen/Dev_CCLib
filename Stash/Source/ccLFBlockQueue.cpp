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

#include "ccLFBlockQueue.h"

namespace CC
{
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   LFBlockQueue::LFBlockQueue()
   {
      // All null
      mMemory = 0;
      mAllocate = 0;
      mParms.mPacked = 0;
   }

   LFBlockQueue::~LFBlockQueue()
   {
      // Deallocate the array
      if (mMemory) delete mMemory;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void LFBlockQueue::initialize(int aAllocate,int aBlockSize)
   {
      // Initialize variables
      mAllocate = aAllocate;
      mBlockSize = aBlockSize;
      mParms.mPacked = 0;

      // Allocate memory for the array
      mMemory = malloc(mAllocate*mBlockSize);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Return a pointer to a block, based on block array index

   void* LFBlockQueue::element(int aIndex)
   {
      return (void*)((char*)mMemory + mBlockSize*aIndex);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a write operation. If the queue is not full then
   // it succeeds. It updates the variable pointed by the input pointer with the 
   // WriteIndex that is to be used to access queue memory for the write, it
   // increments ReadAvailable and returns true. If it fails because the queue is 
   // full then it returns false.

   bool LFBlockQueue::tryStartWrite(int* aWriteIndex)
   {
      // Locals
      LFQueueParms tCompare, tExchange, tOriginal;
      int tWriteIndex;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare = mParms;
         // Exit if the queue is full
         if (tCompare.Parms.mReadAvailable==mAllocate) return false;

         // Update queue parameters for the exchange variable
         tExchange = tCompare;
         tExchange.Parms.mReadAvailable++;
         tWriteIndex = tExchange.Parms.mWriteIndex;
         if (++tExchange.Parms.mWriteIndex == mAllocate) tExchange.Parms.mWriteIndex=0;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         tOriginal.mPacked = InterlockedCompareExchange((PLONG)(&mParms.mPacked), tExchange.mPacked, tCompare.mPacked);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal.mPacked == tCompare.mPacked) break;
      }

      // Store results
      *aWriteIndex = tWriteIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is a place holder.

   void LFBlockQueue::finishWrite()
   {
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a read operation. If the queue is not empty then it 
   // succeeds, it  updates the variable pointed by the input pointer with the 
   // ReadIndex that is to be used to access queue memory for the read and returns 
   // true. If it fails because the queue is empty then it returns false.

   bool LFBlockQueue::tryStartRead(int* aReadIndex)
   {
      // Store the current parms in a temp. This doesn't need to be atomic
      // because it is assumed to run on a 32 bit architecture.
      LFQueueParms tParms;
      tParms.mPacked = mParms.mPacked;

      // Exit if the queue is empty.
      if (tParms.Parms.mReadAvailable == 0) return false;

      // Update the read index
      int tReadIndex = tParms.Parms.mWriteIndex - tParms.Parms.mReadAvailable;
      if (tReadIndex < 0) tReadIndex = tReadIndex + mAllocate;

      // Store result
      *aReadIndex = tReadIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to finish a read operation. It decrements ReadAvailable.

   void LFBlockQueue::finishRead()
   {
      // Locals
      LFQueueParms tCompare, tExchange, tOriginal;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare = mParms;

         // Update queue parameters for the exchange variable
         tExchange = tCompare;
         tExchange.Parms.mReadAvailable--;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         tOriginal.mPacked = InterlockedCompareExchange((PLONG)(&mParms.mPacked), tExchange.mPacked, tCompare.mPacked);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal.mPacked == tCompare.mPacked) break;
      }
   }

}//namespace
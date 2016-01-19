#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "prnPrint.h"

#include "LFQueue.h"

namespace LFQueue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Integer array
   static unsigned mArray[1000];

   // Number of blocks allocated
   static unsigned mAllocate = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue State Members

   //---------------------------------------------------------------------------
   // These two variables are each 16 bits and they are packed into a 32 bit 
   // structure because the atomic compare exchange operation used works on
   // 32 bit integers. This limits the queue size to 64K elements. The only 
   // code that can safely change these variables is contained here. Any other
   // code should be read only.
   //
   // WriteIndex is used to circularly index into queue memory for write 
   // operations. ReadAvailable is used to indicate the number of reads that 
   // are available. They have the following ranges:
   //
   //      0 <= WriteIndex    <= Capacity-1
   //      0 <= ReadAvailable <= Capacity
   //
   //      IF ReadAvailable == 0        THEN the queue is empty
   //      IF ReadAvailable == Capacity THEN the queue is full
   //
   //  The ReadIndex is derived from WriteIndex and ReadAvailable.
   //
   //      ReadIndex = WriteIndex - ReadAvailable;
   //      IF ReadIndex < 0 THEN ReadIndex = ReadIndex + Capacity;
   //---------------------------------------------------------------------------

   typedef struct
   { 
      unsigned mWriteValue      :8;  
      unsigned mWriteIndex      :8;  
      unsigned mReadAvailable   :8;  
      unsigned mPadding         :8;  
   } LFQueueState;

   static LFQueueState mState;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize (unsigned aAllocate)
   {
      // Initialize variables
      mAllocate  = aAllocate;

      mState.mWriteValue = 0;  
      mState.mWriteIndex = 0;  
      mState.mReadAvailable = 0;  

      for (int i=0;i<1000;i++)
      {
         mArray[i]=0;
      }
   }

   //***************************************************************************
   // Finalize

   void finalize()
   {
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Use a compare and swap loop to apply a function to update a variable.
   //
   //    Value      points to the variable to be updated.
   //    Exchange   points to a variable that contains the new value.
   //    Original   points to a variable that contains the original value.
   //    Function   points to the function that updates the variable.
   //
   //    Returns true if the variable was successfully updated.
   //

   typedef bool (*CasLoopFunction)(LFQueueState* aExchange, int aParm1);

   static bool applyCasLoopFunction(
      LFQueueState*    aValue,
      LFQueueState*    aExchange,
      LFQueueState*    aOriginal,
      CasLoopFunction  aFunction,
      int              aParm1)
   {
      // Locals
      LFQueueState tCompare, tExchange, tOriginal;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare  = *aValue;
         tExchange = tCompare;

         // Update the exchange variable with a new value.
         // Exit the loop if unsuccessful.
         if (!aFunction(&tExchange,aParm1)) return false;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         *(LONG*)(&tOriginal) = InterlockedCompareExchange((PLONG)aValue, *(LONG*)(&tExchange), *(LONG*)(&tCompare));

         // If the original and the compare values are the same then there was
         // no preemption or contention and the exchange was a success, so exit
         // the loop. If they were not the same then retry.
         if (*(LONG*)(&tOriginal) == *(LONG*)(&tCompare)) break;
      }

      // Return the results.

      if (aExchange != NULL)
      {
         *aExchange = tExchange;
      }

      if (aOriginal != NULL)
      {
         *aOriginal = tOriginal;
      }

      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a write operation. If the queue is not full then
   // it succeeds. It updates the variable pointed by the input pointer with the 
   // WriteIndex that is to be used to access queue memory for the write, it
   // increments ReadAvailable and returns true. If it fails because the queue is 
   // full then it returns false.

   bool tryWriteUpdate(LFQueueState* aState, int aParm1)
   {
      // Exit if the queue is full or will be full.
      if (aState->mReadAvailable == mAllocate) return false;

      // Store the tail write value.
      aState->mWriteValue = aParm1;
      // Increment the write index, wrap if necessary.
      if (++aState->mWriteIndex == mAllocate) aState->mWriteIndex=0;
      // Increment the read available count.
      aState->mReadAvailable++;

      return true;
   }

   bool tryWrite (unsigned aWriteValue)
   {
      // Locals
      LFQueueState tOriginal;

      // Test and update the queue state to write.
      if (applyCasLoopFunction(&mState,0,&tOriginal,tryWriteUpdate,aWriteValue))
      {
         // Store the value in the array.
         mArray[tOriginal.mWriteIndex] = aWriteValue;
         return true;
      }
      else
      {
         // The queue is full, return false.
         return false;
      }
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a read operation. If the queue is not empty then it 
   // succeeds, it  updates the variable pointed by the input pointer with the 
   // ReadIndex that is to be used to access queue memory for the read and returns 
   // true. If it fails because the queue is empty then it returns false.
   // This is called for a operation. It decrements ReadAvailable.

   bool tryReadUpdate(LFQueueState* aState,int aParm1)
   {
      // Update queue state for the exchange variable
      aState->mReadAvailable--;

      return true;
   }

   bool tryRead(unsigned* aReadValue)
   {
      // Store the current parms in a temp. This doesn't need to be atomic
      // because it is assumed to run on a 32 bit architecture.
      LFQueueState tState = mState;

      // Exit if the queue is empty.
      if (tState.mReadAvailable == 0) return false;

      // Update the read index
      int tReadIndex = tState.mWriteIndex - tState.mReadAvailable;
      if (tReadIndex < 0) tReadIndex = tReadIndex + mAllocate;

      // Store result
      *aReadValue = mArray[tReadIndex];

      // Update the queue state to finish a read.
      applyCasLoopFunction(&mState,0,0,tryReadUpdate,0);

      // Done.
      return true;
   }
}
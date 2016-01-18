#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "prnPrint.h"

#include "LFBlockQueue.h"

namespace LFBlockQueue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Pointer to allocated memory
   static void* mMemory = 0;

   // Number of blocks allocated
   static unsigned mAllocate = 0;

   // Size of each block allocated
   static unsigned mBlockSize = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue State Members

   //---------------------------------------------------------------------------
   // These three variables are packed into a 32 bit structure because the
   // atomic compare exchange operation used works on 32 bit integers. This
   // limits the queue size. The only code that can safely change these
   // variables is contained here. Any other code should be read only.
   //
   // WriteInProgress is used to count the number of write operations that are
   // in progress. A writer increments this with a start write operation and 
   // decrements it with a finish write operation.
   //
   // WriteIndex is used to circularly index into queue memory for write 
   // operations.
   // 
   // ReadAvailable is used to indicate the number of reads that are available.
   //
   // These variables have the following ranges:
   //
   //      0 <= WriteInProgress <= MaxWriteInProgress
   //      0 <= WriteIndex <= Allocate-1
   //      0 <= ReadAvailable + WriteInProgress <= Allocate
   //
   //      IF ReadAvailable == 0        THEN the queue is empty
   //      IF ReadAvailable == Allocate THEN the queue is full
   //
   //  The ReadIndex is derived from WriteIndex and ReadAvailable.
   //
   //      ReadIndex = WriteIndex - ReadAvailable;
   //      IF ReadIndex < 0 THEN ReadIndex = ReadIndex + Allocate;
   //---------------------------------------------------------------------------

   // Max number of writers
   static const LONG cMaxWriteInProgress = 255;
   
   typedef union
   {
       struct    
       { 
         unsigned mWriteInProgress : 8;  
         unsigned mWriteIndex      :12;  
         unsigned mReadAvailable   :12;  
       } State;
       signed mPacked;
   } LFBlockQueueState;

   static LFBlockQueueState mState;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Allocate memory for the block array and initialize the queue logic
   // variables. It is passed the number of blocks to allocate and the size
   // of the blocks.

   void initialize(unsigned aAllocate,unsigned aBlockSize)
   {
      // Initialize variables
      mAllocate = aAllocate;
      mBlockSize = aBlockSize;
      mState.mPacked = 0;

      // Allocate memory for the array
      mMemory = malloc(mAllocate*mBlockSize);
   }

   //******************************************************************************
   // Deallocate memory

   void finalize()
   {
      // Deallocate the array
      if (mMemory) delete mMemory;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Return a pointer to a block, based on block array index

   void* element(unsigned aIndex)
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

   void* tryStartWrite()
   {
      // Locals
      LFBlockQueueState tCompare, tExchange, tOriginal;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare = mState;
         tExchange = tCompare;

         // Exit if the queue is full or will be full.
         if (tExchange.State.mReadAvailable + tExchange.State.mWriteInProgress >= mAllocate) return 0;
         // Exit if there are too many writes in progress.
         if (tExchange.State.mWriteInProgress==cMaxWriteInProgress) return 0;

         // Update queue state for the exchange variable.
         tExchange.State.mWriteInProgress++;
         if (++tExchange.State.mWriteIndex == mAllocate) tExchange.State.mWriteIndex=0;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         tOriginal.mPacked = InterlockedCompareExchange((PLONG)(&mState.mPacked), tExchange.mPacked, tCompare.mPacked);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal.mPacked == tCompare.mPacked) break;
      }

      // Return a pointer to the element to write to.
      return element(tOriginal.State.mWriteIndex);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to finish a write operation. It increments ReadAvailable
   // and decrements WriteInProgress.

   void finishWrite()
   {
      // Locals
      LFBlockQueueState tCompare, tExchange, tOriginal;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare  = mState;
         tExchange = tCompare;

         // Update queue state for the exchange variable
         tExchange.State.mReadAvailable++;
         tExchange.State.mWriteInProgress--;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         tOriginal.mPacked = InterlockedCompareExchange((PLONG)(&mState.mPacked), tExchange.mPacked, tCompare.mPacked);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal.mPacked == tCompare.mPacked) break;
      }
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a read operation. If the queue is not empty then it 
   // succeeds, it  updates the variable pointed by the input pointer with the 
   // ReadIndex that is to be used to access queue memory for the read and returns 
   // true. If it fails because the queue is empty then it returns false.

   void* tryStartRead()
   {
      // Store the current parms in a temp. Because there can only be one
      // reader, this doesn't need to be atomic.
      LFBlockQueueState tState;
      tState.mPacked = mState.mPacked;

      // Exit if the queue is empty.
      if (tState.State.mReadAvailable == 0) return 0;

      // Update the read index
      int tReadIndex = tState.State.mWriteIndex - tState.State.mReadAvailable;
      if (tReadIndex < 0) tReadIndex = tReadIndex + mAllocate;

      // Return a pointer to the element to read from.
      return element(tReadIndex);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to finish a read operation. It decrements ReadAvailable.

   void finishRead()
   {
      // Locals
      LFBlockQueueState tCompare, tExchange, tOriginal;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare  = mState;
         tExchange = tCompare;

         // Update queue state for the exchange variable
         tExchange.State.mReadAvailable--;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         tOriginal.mPacked = InterlockedCompareExchange((PLONG)(&mState.mPacked), tExchange.mPacked, tCompare.mPacked);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal.mPacked == tCompare.mPacked) break;
      }
   }
}
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "LFObjectQueue.h"

namespace LFObjectQueue
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
   static const unsigned cBlockSize = 16;

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
   
   typedef struct
   { 
      unsigned mWriteInProgress : 8;  
      unsigned mWriteIndex      :12;  
      unsigned mReadAvailable   :12;  
   } LFBlockQueueState;

   static LFBlockQueueState mState;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is a function that converts from a byte size to a number of blocks.

   static unsigned numOfBlocksFromSize(size_t aSize)
   {
      unsigned tSize;

      // Align the size upward to be on a sixteen byte boundary.
      if ((aSize & 15) == 0)
      {
         tSize = (unsigned)aSize;
      }
      else
      {
         tSize = (((unsigned)aSize >> 4) << 4) + 16;
      }

      return tSize/16;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Allocate memory for the block array and initialize the queue logic
   // variables. It is passed the number of blocks to allocate and the size
   // of the blocks.

   void initialize (size_t aAllocateBytes)
   {
      // Initialize variables
      mAllocate  = numOfBlocksFromSize (aAllocateBytes);

      mState.mWriteInProgress = 0;  
      mState.mWriteIndex = 0;  
      mState.mReadAvailable = 0;  

      // Allocate memory for the array
      mMemory = malloc(mAllocate*cBlockSize);
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
      return (void*)((char*)mMemory + cBlockSize*aIndex);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Use a compare and swap loop to apply a function to update a variable.
   //
   //    Value      points to the variable to be updated.
   //    Exchange   points to a variable that contains the new value.
   //    Original   points to a variable that contains the original value.
   //    Function   points to the function that updates the variable.
   //
   //    Returns true if the variable was successfully updated.
   //

   typedef bool (*CasLoopFunction)(LFBlockQueueState* aExchange, int aNumBlocks);

   static bool applyCasLoopFunction(
      LFBlockQueueState*  aValue,
      LFBlockQueueState*  aExchange,
      LFBlockQueueState*  aOriginal,
      CasLoopFunction     aFunction,
      int                 aNumBlocks)
   {
      // Locals
      LFBlockQueueState tCompare, tExchange, tOriginal;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare  = *aValue;
         tExchange = tCompare;

         // Update the exchange variable with a new value.
         // Exit the loop if unsuccessful.
         if (!aFunction(&tExchange,aNumBlocks)) return false;

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

   bool tryWriteStartUpdate(LFBlockQueueState* aState, int aNumBlocks)
   {
      // Exit if the queue is full or will be full.
      if (aState->mReadAvailable + aState->mWriteInProgress + aNumBlocks >= mAllocate) return false;
      // Exit if there are too many writes in progress.
      if (aState->mWriteInProgress==cMaxWriteInProgress) return false;

      // Increment the write in progress count.
      aState->mWriteInProgress += aNumBlocks;
      // Increment the write index, wrap if necessary.
      if (++aState->mWriteIndex == mAllocate) aState->mWriteIndex=0;

      return true;
   }

   void* tryStartWrite (size_t aNumBytes)
   {
      // Locals
      LFBlockQueueState tOriginal;
      unsigned tNumBlocks = numOfBlocksFromSize(aNumBytes);

      // Test and update the queue state to start a write.
      if (applyCasLoopFunction(&mState,0,&tOriginal,tryWriteStartUpdate,tNumBlocks))
      {
         // Return a pointer to the element to write to.
         return element(tOriginal.mWriteIndex);
      }
      else
      {
         // The queue is full, return a null pointer.
         return 0;
      }
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to finish a write operation. It increments ReadAvailable
   // and decrements WriteInProgress.

   bool finishWriteUpdate(LFBlockQueueState* aState,int aNumBlocks)
   {
      // Update the queue state to finish a write.
      aState->mReadAvailable   += aNumBlocks;
      aState->mWriteInProgress -= aNumBlocks;

      return true;
   }

   void finishWrite(size_t aNumBytes)
   {
      // Local
      unsigned tNumBlocks = numOfBlocksFromSize(aNumBytes);

      // Update the queue state to finish a write.
      applyCasLoopFunction(&mState,0,0,finishWriteUpdate,tNumBlocks);
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
      // Store the current state in a temp. Because there can only be one reader, 
      // this doesn't need to be atomic.
      LFBlockQueueState tState = mState;

      // Exit if the queue is empty.
      if (tState.mReadAvailable == 0) return 0;

      // Update the read index
      int tReadIndex = tState.mWriteIndex - tState.mReadAvailable;
      if (tReadIndex < 0) tReadIndex = tReadIndex + mAllocate;

      // Return a pointer to the element to read from.
      return element(tReadIndex);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to finish a read operation. It decrements ReadAvailable.

   bool finishReadUpdate(LFBlockQueueState* aState,int aNumBlocks)
   {
      // Update queue state for the exchange variable
      aState->mReadAvailable--;

      return true;
   }

   void finishRead()
   {
      // Update the queue state to finish a read.
      applyCasLoopFunction(&mState,0,0,finishReadUpdate,0);
   }
}
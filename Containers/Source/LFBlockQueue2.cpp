#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "ccLFCasLoop.h"
#include "LFBlockQueue2.h"

namespace LFBlockQueue2
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
   // Allocate memory for the block array and initialize the queue logic
   // variables. It is passed the number of blocks to allocate and the size
   // of the blocks.

   void initialize(unsigned aAllocate,unsigned aBlockSize)
   {
      // Initialize variables
      mAllocate  = aAllocate;
      mBlockSize = aBlockSize;

      mState.mWriteInProgress = 0;  
      mState.mWriteIndex = 0;  
      mState.mReadAvailable = 0;  

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

   bool tryWriteStartUpdate(void* aExchange)
   {
      LFBlockQueueState* tState = (LFBlockQueueState*)aExchange;

      // Exit if the queue is full or will be full.
      if (tState->mReadAvailable + tState->mWriteInProgress >= mAllocate) return false;
      // Exit if there are too many writes in progress.
      if (tState->mWriteInProgress==cMaxWriteInProgress) return false;

      // Update queue state for the exchange variable.
      tState->mWriteInProgress++;
      if (++tState->mWriteIndex == mAllocate) tState->mWriteIndex=0;

      return true;
   }

   void* tryStartWrite()
   {
      // Locals
      LFBlockQueueState tOriginal;

      // Test and update the queue state to start a write.
      if (CC::applyLFCasLoopFunction(&mState,0,&tOriginal,tryWriteStartUpdate))
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

   bool finishWriteUpdate(void* aExchange)
   {
      LFBlockQueueState* tState = (LFBlockQueueState*)aExchange;

      // Update queue state for the exchange variable
      tState->mReadAvailable++;
      tState->mWriteInProgress--;

      return true;
   }

   void finishWrite()
   {
      // Update the queue state to finish a write.
      CC::applyLFCasLoopFunction(&mState,0,0,finishWriteUpdate);
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

   bool finishReadUpdate(void* aExchange)
   {
      LFBlockQueueState* tState = (LFBlockQueueState*)aExchange;

      // Update queue state for the exchange variable
      tState->mReadAvailable--;

      return true;
   }

   void finishRead()
   {
      // Update the queue state to finish a read.
      CC::applyLFCasLoopFunction(&mState,0,0,finishReadUpdate);
   }
}
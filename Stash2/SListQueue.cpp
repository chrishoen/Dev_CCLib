#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "prnPrint.h"

#include "ccTokenStack.h"
#include "SListQueue.h"

namespace SListQueue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // SList Members

   typedef struct
   { 
      int mValue;  
      int mNext;  
   } SListBlock;

   static const int cInvalid = 999;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue State Members

   typedef struct
   { 
      int mHeadIndex     :8;  
      int mTailIndex     :8;  
      int mReadAvailable :8;  
   } LFQueueState;

   static LFQueueState mState;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Block array
   static SListBlock mBlockArray[1000];

   // Number of blocks allocated
   static int mAllocate = 0;

   // Stack of indices into block array
   static CC::TokenStack mStack;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize (int aAllocate)
   {
      // Initialize variables
      mAllocate  = aAllocate;

      mState.mHeadIndex = cInvalid;  
      mState.mTailIndex = cInvalid;  
      mState.mReadAvailable = 0;  

      mStack.initialize(mAllocate);

      for (int i=0;i<mAllocate;i++)
      {
         mStack.tryPush(i);
         mBlockArray[i].mValue = 0;
         mBlockArray[i].mNext = cInvalid;
      }
   }

   //***************************************************************************
   // Finalize

   void finalize()
   {
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a write operation. If the queue is not full then
   // it succeeds. It updates the variable pointed by the input pointer with the 
   // WriteIndex that is to be used to access queue memory for the write, it
   // increments ReadAvailable and returns true. If it fails because the queue is 
   // full then it returns false.

   bool tryWrite22 (int aWriteValue)
   {
      // Exit if the queue is full or will be full.
      if (mState.mReadAvailable == mAllocate) return false;

      // Try to allocate an index from the stack
      int tWriteIndex = cInvalid;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in the write block.
      mBlockArray[tWriteIndex].mValue = aWriteValue;
      mBlockArray[tWriteIndex].mNext = cInvalid;

      // If the queue is empty
      if (mState.mReadAvailable == 0)
      {
         // Add the block at the queue head and tail.
         mState.mHeadIndex = tWriteIndex;
         mState.mTailIndex = tWriteIndex;
         mState.mReadAvailable++;
      }
      // Else the queue is not empty
      else
      {
         // Add the block at the queue tail.
         mBlockArray[mState.mTailIndex].mNext = tWriteIndex;
         mState.mTailIndex = tWriteIndex;
         mState.mReadAvailable++;
      }

      // Done
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a read operation. If the queue is not empty then it 
   // succeeds, it  updates the variable pointed by the input pointer with the 
   // ReadIndex that is to be used to access queue memory for the read and returns 
   // true. If it fails because the queue is empty then it returns false.
   // This is called for a operation. It decrements ReadAvailable.

   bool tryRead22 (int* aReadValue) 
   {
      // Exit if the queue is empty.
      if (mState.mReadAvailable == 0) return false;

      // Store the head index in a temp.
      int tOriginalHeadIndex = mState.mHeadIndex;

      // Extract the read value from the head block.
      *aReadValue = mBlockArray[mState.mHeadIndex].mValue;

      // Update the head index.
      mState.mHeadIndex = mBlockArray[mState.mHeadIndex].mNext;

      // Decrement the queue state.
      mState.mReadAvailable--;

      // Push the original head index back onto the stack.
      mStack.tryPush(tOriginalHeadIndex);

      // Done.
      return true;
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

   typedef bool (*CasLoopFunction)(LFQueueState* aExchange,int aIndex);

   static bool applyCasLoopFunction(
      LFQueueState*    aValue,
      LFQueueState*    aExchange,
      LFQueueState*    aOriginal,
      CasLoopFunction  aFunction,
      int              aIndex)
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
         if (!aFunction(&tExchange,aIndex)) return false;

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

   bool tryWriteUpdate(LFQueueState* aState,int aWriteIndex)
   {
      // Exit if the queue is full.
      if (aState->mReadAvailable == mAllocate) return false;

      // If the queue is empty
      if (aState->mReadAvailable == 0)
      {
         // Add the block at the queue head and tail.
         aState->mHeadIndex = aWriteIndex;
         aState->mTailIndex = aWriteIndex;
         aState->mReadAvailable++;
      }
      // Else the queue is not empty
      else
      {
         // Add the block at the queue tail.
         aState->mTailIndex = aWriteIndex;
         aState->mReadAvailable++;
      }
      // Success
      return true;
   }

   bool tryWrite (int aWriteValue)
   {
      // Locals
      LFQueueState tOriginal;

      // Exit if the queue is full or will be full.
      if (mState.mReadAvailable == mAllocate) return false;

      // Try to allocate an index from the stack
      int tWriteIndex = cInvalid;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in the write block.
      mBlockArray[tWriteIndex].mValue = aWriteValue;
      mBlockArray[tWriteIndex].mNext = cInvalid;

      // Attempt to update the queue state for a write.
      if (applyCasLoopFunction(&mState,0,&tOriginal,tryWriteUpdate,tWriteIndex))
      {
         // The attempt succeeded. If the original tail block is valid
         // then attach this block to it.
         if (tOriginal.mTailIndex != cInvalid)
         {
            mBlockArray[tOriginal.mTailIndex].mNext = tWriteIndex;
         }
         return true;
      }
      else
      {
         // The attempt failed.
         // The queue is full, push the write index back to the stack.
         mStack.tryPush(tWriteIndex);
         return false;
      }

      // Done
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a read operation. If the queue is not empty then it 
   // succeeds, it  updates the variable pointed by the input pointer with the 
   // ReadIndex that is to be used to access queue memory for the read and returns 
   // true. If it fails because the queue is empty then it returns false.
   // This is called for a operation. It decrements ReadAvailable.

   bool tryReadUpdate(LFQueueState* aState,int aIndex)
   {
      // Update queue state for the exchange variable
      aState->mReadAvailable--;
      aState->mHeadIndex = aIndex;
      // Success
      return true;
   }

   bool tryRead (int* aReadValue) 
   {
      // Locals
      LFQueueState tOriginal;

      // Store the current state in a temp. Because there can only be one reader, 
      // this doesn't need to be atomic.
      LFQueueState tState = mState;

      // Exit if the queue is empty.
      if (tState.mReadAvailable == 0) return false;
      // Exit if the head block is invalid.
      if (tState.mHeadIndex == cInvalid) return false;

      int tNextHeadIndex = mBlockArray[mState.mHeadIndex].mNext;

      // Update the queue state to for a read.
      applyCasLoopFunction(&mState,0,&tOriginal,tryReadUpdate,tNextHeadIndex);

      // Extract the read value from the original head block.
      *aReadValue = mBlockArray[tOriginal.mHeadIndex].mValue;

      // Push the original head index back onto the stack.
      mStack.tryPush(tOriginal.mHeadIndex);

      // Done.
      return true;
   }

}
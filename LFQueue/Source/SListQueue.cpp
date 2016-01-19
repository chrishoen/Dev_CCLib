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
      int mHeadIndex;  
      int mTailIndex;  
      int mReadAvailable;  
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

      mState.mHeadIndex = 0;  
      mState.mTailIndex = 0;  
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

   bool tryWrite (int aWriteValue)
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

   bool tryRead(int* aReadValue)
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
}
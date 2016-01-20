#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "prnPrint.h"

#include "ccTokenStack.h"
#include "SList2Queue.h"

namespace SList2Queue
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

   int mHeadIndex;  
   int mTailIndex;  

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Block array
   static SListBlock mBlock[1000];

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

      mStack.initialize(mAllocate);

      for (int i=mAllocate-1; i>=0; --i)
      {
         mStack.tryPush(i);
         mBlock[i].mValue = 0;
         mBlock[i].mNext = cInvalid;
      }
#if 0
      mStack.tryPop(&mTailIndex);
      mBlock[mTailIndex].mValue = 0;
      mBlock[mTailIndex].mNext = cInvalid;
      mHeadIndex = mTailIndex;  
#endif

      mHeadIndex = cInvalid;
      mTailIndex = cInvalid;  
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
      // Try to allocate an index from the stack
      int tWriteIndex;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in the write block.
      mBlock[tWriteIndex].mValue = aWriteValue;
      mBlock[tWriteIndex].mNext = cInvalid;

      // Add the block at the queue tail.
      mBlock[mTailIndex].mNext = tWriteIndex;
      mTailIndex = tWriteIndex;

      if (mHeadIndex == cInvalid)
      {
         mHeadIndex = mTailIndex;
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

   bool tryRead (int* aReadValue) 
   {
      // Exit if the queue is empty.
      if (mHeadIndex == cInvalid) return false;

      // Store the head index in a temp.
      int tSaveIndex = mHeadIndex;

      // Extract the read value from the head block.
      *aReadValue = mBlock[mHeadIndex].mValue;

      // Update the head index.
      mHeadIndex = mBlock[mHeadIndex].mNext;

      // Push the original head index back onto the stack.
      mStack.tryPush(tSaveIndex);

      // Done.
      return true;
   }


}
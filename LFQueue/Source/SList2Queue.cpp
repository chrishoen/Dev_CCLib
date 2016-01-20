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
   } SListNode;

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

   // Node array
   static SListNode mNode[1000];

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
         mNode[i].mValue = 0;
         mNode[i].mNext = cInvalid;
      }

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
      mNode[tWriteIndex].mValue = aWriteValue;
      mNode[tWriteIndex].mNext = cInvalid;

      // Add the block at the queue tail.
      mNode[mTailIndex].mNext = tWriteIndex;
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
      *aReadValue = mNode[mHeadIndex].mValue;

      // Update the head index.
      mHeadIndex = mNode[mHeadIndex].mNext;

      // Push the original head index back onto the stack.
      mStack.tryPush(tSaveIndex);

      // Done.
      return true;
   }


}
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

   int mPopIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize (int aAllocate)
   {
      // Initialize variables
      mAllocate = aAllocate + 1;

      mStack.initialize(mAllocate);

      for (int i=mAllocate-1; i>=0; --i)
      {
         mStack.tryPush(i);
         mNode[i].mValue = 0;
         mNode[i].mNext = cInvalid;
      }

      mStack.tryPop(&mHeadIndex);
      mTailIndex = mHeadIndex;  
   }

   //***************************************************************************
   // Finalize

   void finalize()
   {
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   static bool boolCas(int* aDestin, int aExchange, int aCompare)
   {
      int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
      return tOriginal == aCompare; 
   }

   static int valCas(int* aDestin, int aExchange, int aCompare)
   {
      int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
      return tOriginal; 
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a write operation. If the queue is not full then
   // it succeeds. It updates the variable pointed by the input pointer with the 
   // WriteIndex that is to be used to access queue memory for the write, it
   // increments ReadAvailable and returns true. If it fails because the queue is 
   // full then it returns false.

   bool tryWrite2 (int aWriteValue)
   {
      // Try to allocate an index from the stack.
      // Exit if the stack is empty.
      int tWriteIndex;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in a new node.
      mNode[tWriteIndex].mValue = aWriteValue;
      mNode[tWriteIndex].mNext = cInvalid;

      // Attach the node to the queue tail.
      mNode[mTailIndex].mNext = tWriteIndex;
      mTailIndex = tWriteIndex;

      // Done
      return true;
   }

   bool tryWrite (int aWriteValue)
   {
      // Try to allocate an index from the stack
      // Exit if the stack is empty.
      int tWriteIndex;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in a new node.
      mNode[tWriteIndex].mValue = aWriteValue;
      mNode[tWriteIndex].mNext = cInvalid;

      // Attach the node to the queue tail.
      int tTailIndex;
      while (true)
      {
         tTailIndex = mTailIndex;

         if (boolCas(&mNode[tTailIndex].mNext, tWriteIndex, cInvalid)) break;
         boolCas(&mTailIndex, mNode[tTailIndex].mNext, tTailIndex);
      }
      boolCas(&mTailIndex,tWriteIndex,tTailIndex);

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
      // Store the read index in a temp.
      int tReadIndex = mNode[mHeadIndex].mNext;

      // Exit if the queue is empty.
      if (tReadIndex == cInvalid) return false;

      // Extract the read value from the head block.
      *aReadValue = mNode[tReadIndex].mValue;

      // Push the previous head index back onto the stack.
      mStack.tryPush(mHeadIndex);

      // Update the head index.
      mHeadIndex = tReadIndex;

      // Done.
      return true;
   }


}
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "prnPrint.h"

#include "ccTokenStack.h"
#include "LFAtomic.h"
#include "LFIntQueue.h"

using namespace std;

namespace LFIntQueue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // SList Members

   typedef struct
   { 
      int mValue;  
      atomic<int> mNext;  
   } SListNode;

   static const int cInvalid = 999;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue State Members

   atomic<int> mHeadIndex;  
   atomic<int> mTailIndex;  

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
      mAllocate = aAllocate + 1;

      mStack.initialize(mAllocate);

      for (int i=mAllocate-1; i>=0; --i)
      {
         mStack.tryPush(i);
         mNode[i].mValue = 0;
         mNode[i].mNext = cInvalid;
      }

      mStack.tryPop((int*)&mHeadIndex);
      mTailIndex = mHeadIndex.load();  
   }

   //***************************************************************************
   // Finalize

   void finalize()
   {
   }


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds. It attempts to pop an index from the index stack. If
   // the stack is empty then the queue is full and it exits. The popped index
   // is used to initialize a new node, which stores the input value that is
   // to be written. The new node is then attached to the queue tail node and
   // the tail index is updated.

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

         int tInvalid = cInvalid;
         if (mNode[tTailIndex].mNext.compare_exchange_weak(tInvalid, tWriteIndex)) break;
         mTailIndex.compare_exchange_weak(tTailIndex, mNode[tTailIndex].mNext);
      }
      mTailIndex.compare_exchange_strong(tTailIndex, tWriteIndex);

      // Done
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This attempts to read a value from the queue. If the queue is not empty
   // then it succeeds. It extracts the read value from the head node, pushes the
   // previous head index back onto the stack and updates the head index.

   bool tryRead (int* aReadValue) 
   {
      int tHeadIndex;
      while (true)
      {
         // Store the read index in a temp.
         tHeadIndex = mHeadIndex;

         // Exit if the queue is empty.
         if (mNode[tHeadIndex].mNext == cInvalid) return false;

         if (mHeadIndex.compare_exchange_weak(tHeadIndex, mNode[tHeadIndex].mNext)) break;
      }
      // Extract the read value from the head block.
      int tReadIndex = mNode[tHeadIndex].mNext;
      *aReadValue = mNode[tReadIndex].mValue;

      // Push the previous head index back onto the stack.
      mStack.tryPush(tHeadIndex);

      // Done.
      return true;
   }
}
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "prnPrint.h"

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
      int         mValue;
      atomic<int> mQueueNext;
      atomic<int> mListNext;
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
   // Free List Members

   bool listPush  (int  aIndex);
   bool listPop   (int* aIndex);

   atomic<int> mListIndex;
   atomic<int> mListSize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Node array
   static SListNode mNode[1000];

   // Number of blocks allocated
   static int mAllocate = 0;
   static int mQueueAllocate = 0;
   static int mListAllocate = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize (int aAllocate)
   {
      mAllocate      = aAllocate;
      mQueueAllocate = aAllocate + 1;
      mListAllocate  = aAllocate + 2;

      for (int i=0; i<mListAllocate-1; i++)
      {
         mNode[i].mValue = 0;
         mNode[i].mQueueNext = cInvalid;
         mNode[i].mListNext  = i + 1;
      }

      mNode[mListAllocate-1].mValue = 0;
      mNode[mListAllocate-1].mQueueNext = cInvalid;
      mNode[mListAllocate-1].mListNext = cInvalid;

      mListSize  = mListAllocate-1;
      mListIndex = 0;

      listPop((int*)&mHeadIndex);
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
      if (!listPop(&tWriteIndex)) return false;

      // Store the write value in a new node.
      mNode[tWriteIndex].mValue = aWriteValue;
      mNode[tWriteIndex].mQueueNext = cInvalid;

      // Attach the node to the queue tail.
      int tTailIndex;
      while (true)
      {
         tTailIndex = mTailIndex;

         int tInvalid = cInvalid;
         if (mNode[tTailIndex].mQueueNext.compare_exchange_weak(tInvalid, tWriteIndex)) break;
         mTailIndex.compare_exchange_weak(tTailIndex, mNode[tTailIndex].mQueueNext);
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
         if (mNode[tHeadIndex].mQueueNext == cInvalid) return false;

         if (mHeadIndex.compare_exchange_weak(tHeadIndex, mNode[tHeadIndex].mQueueNext)) break;
      }
      // Extract the read value from the head block.
      int tReadIndex = mNode[tHeadIndex].mQueueNext;
      *aReadValue = mNode[tReadIndex].mValue;

      // Push the previous head index back onto the stack.
      listPush(tHeadIndex);

      // Done.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list after the list tail node.

   bool listPush (int aIndex)
   {
      // Exit if the list is full.
      if (mListSize >= mAllocate) return false;

      int tListNext;
      while (true)
      {
         // Save the index to the next node.
         tListNext = mNode[mListIndex].mListNext;

         // Point the new node at the node that the tail points to. 
         mNode[aIndex].mListNext = tListNext;

         // Point the tail at the new node.
         if (mNode[mListIndex].mListNext.compare_exchange_weak(tListNext, aIndex)) break;
      }

      // Done.
      mListSize++;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the node that is after the tail node.

   bool listPop (int* aIndex) 
   {
//    printf("listPop %d %d %d\n",mListSize,mListIndex,mNode[mListIndex].mListNext);
      int tIndex;
      while (true)
      {
         // Store the index of the node that is to be detached in a temp.
         tIndex = mNode[mListIndex].mListNext;
         // Exit if the queue is empty.
         if (tIndex == cInvalid) return false;

         // Attempt to detach the node.
         if (mNode[mListIndex].mListNext.compare_exchange_weak(tIndex, mNode[tIndex].mListNext)) break;
      }

      // Reset the detached node.
      mNode[tIndex].mValue = 0;
      mNode[tIndex].mQueueNext  = cInvalid;
      mNode[tIndex].mListNext  = cInvalid;

      // Return result.
      *aIndex = tIndex;

      // Done.
      mListSize--;
      return true;
   }

}
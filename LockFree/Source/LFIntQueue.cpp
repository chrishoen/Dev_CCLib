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

   atomic<int> mQueueHead;  
   atomic<int> mQueueTail;  

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Free List Members

   bool listPush  (int  aIndex);
   bool listPop   (int* aIndex);

   atomic<int> mListTail;
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
      mListTail = 0;

      listPop((int*)&mQueueHead);
      mQueueTail = mQueueHead.load(); 
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds. It attempts to pop a node from the free list. If
   // the free list is empty then the queue is full and it exits. The value
   // is to be written is stored in the new node. The new node is then attached
   // to the queue tail node and the tail index is updated.

   bool tryWrite (int aWriteValue)
   {
      // Try to allocate a node from the free list.
      // Exit if the stack is empty.
      int tWriteNode;
      if (!listPop(&tWriteNode)) return false;

      // Store the write value in a new node.
      mNode[tWriteNode].mValue = aWriteValue;
      mNode[tWriteNode].mQueueNext = cInvalid;

      // Attach the node to the queue tail.
      int tQueueTail;
      while (true)
      {
         tQueueTail = mQueueTail;

         int tInvalid = cInvalid;
         if (mNode[tQueueTail].mQueueNext.compare_exchange_weak(tInvalid, tWriteNode)) break;
         mQueueTail.compare_exchange_weak(tQueueTail, mNode[tQueueTail].mQueueNext);
      }
      mQueueTail.compare_exchange_strong(tQueueTail, tWriteNode);

      // Done
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This attempts to read a value from the queue. If the queue is not empty
   // then it succeeds. It extracts the read value from the head node, pushes the
   // previous head node back onto the free list and updates the head index.

   bool tryRead (int* aReadValue) 
   {
      int tQueueHead;
      while (true)
      {
         // Store the read index in a temp.
         tQueueHead = mQueueHead;

         // Exit if the queue is empty.
         if (mNode[tQueueHead].mQueueNext == cInvalid) return false;

         if (mQueueHead.compare_exchange_weak(tQueueHead, mNode[tQueueHead].mQueueNext)) break;
      }
      // Extract the read value from the head block.
      int tReadNode = mNode[tQueueHead].mQueueNext;
      *aReadValue = mNode[tReadNode].mValue;

      // Push the previous head node back onto the free list.
      listPush(tQueueHead);

      // Done.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list after the list tail node.

   bool listPush (int aNode)
   {
      // Exit if the list is full.
      if (mListSize >= mAllocate) return false;

      int tListNext;
      while (true)
      {
         // Save the index to the next node.
         tListNext = mNode[mListTail].mListNext;

         // Point the new node at the node that the tail points to. 
         mNode[aNode].mListNext = tListNext;

         // Point the tail at the new node.
         if (mNode[mListTail].mListNext.compare_exchange_weak(tListNext, aNode)) break;
      }

      // Done.
      mListSize++;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the node that is after the tail node.

   bool listPop (int* aNode) 
   {
      int tNode;
      while (true)
      {
         // Store the index of the node that is to be detached in a temp.
         tNode = mNode[mListTail].mListNext;
         // Exit if the queue is empty.
         if (tNode == cInvalid) return false;

         // Attempt to detach the node.
         if (mNode[mListTail].mListNext.compare_exchange_weak(tNode, mNode[tNode].mListNext)) break;
      }

      // Reset the detached node.
      mNode[tNode].mValue = 0;
      mNode[tNode].mQueueNext = cInvalid;
      mNode[tNode].mListNext  = cInvalid;

      // Return result.
      *aNode = tNode;

      // Done.
      mListSize--;
      return true;
   }
}

#if 0
    printf("listPop %d %d %d\n",mListSize,mListTail,mNode[mListTail].mListNext);
#endif

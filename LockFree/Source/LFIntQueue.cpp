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

   atomic<int> mListHead;
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
      mListHead = 0;

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
      // Exit if it is empty.
      int tNode;
      if (!listPop(&tNode)) return false;

      // Initialize the node with the value.
      mNode[tNode].mValue = aWriteValue;
      mNode[tNode].mQueueNext = cInvalid;

      // Attach the node to the queue tail.
      int tQueueTail;
      while (true)
      {
         tQueueTail = mQueueTail;

         int tInvalid = cInvalid;
         if (mNode[tQueueTail].mQueueNext.compare_exchange_weak(tInvalid, tNode)) break;
         mQueueTail.compare_exchange_weak(tQueueTail, mNode[tQueueTail].mQueueNext);
      }
      mQueueTail.compare_exchange_strong(tQueueTail, tNode);

      // Done
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This attempts to read a value from the queue. If the queue is not empty
   // then it succeeds. The next node in the queue to be read is the one 
   // immedialtely after the head node. It extracts the read value from the read
   // node, pushes the previous head node back onto the free list and updates the
   // head index.

   bool tryRead (int* aReadValue) 
   {
      // Store the head node in a temp.
      int tQueueHead = mQueueHead;
      while (true)
      {
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
   // Insert a node into the list before the list tail node.
   // There can be no concurrent calls to this.

   bool listPush (int aNode)
   {
      // Exit if the list is full.
      if (mListSize >= mAllocate) return false;

      // Store the node the tail is attached to in a temp.
      int tNextNode = mNode[mListHead].mListNext;
      while (true)
      {
         // Attach the node to the node that the tail is attached to.
         mNode[aNode].mListNext = tNextNode;

         // Attach the tail node to the node.
         if (mNode[mListHead].mListNext.compare_exchange_weak(tNextNode, aNode)) break;
      }

      // Done.
      mListSize++;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the node that is before the tail list node.
   // There can be concurrent calls to this.

   bool listPop (int* aNode) 
   {
      // Store the node that is before the tail in a temp.
      int tNextNode = mNode[mListHead].mListNext;
      while (true)
      {
         // Exit if the queue is empty.
         if (tNextNode == cInvalid) return false;

         // Attempt to detach the node.
         if (mNode[mListHead].mListNext.compare_exchange_weak(tNextNode, mNode[tNextNode].mListNext)) break;
      }

      // Reset the detached node.
      mNode[tNextNode].mValue = 0;
      mNode[tNextNode].mQueueNext = cInvalid;
      mNode[tNextNode].mListNext  = cInvalid;

      // Return result.
      *aNode = tNextNode;

      // Done.
      mListSize--;
      return true;
   }
}



#if 0
   bool tryRead (int* aReadValue) 
   {
      // Store the read node index in a temp.
      int tReadNode = mNode[mQueueHead].mQueueNext;

      // Exit if the queue is empty.
      if (tReadNode == cInvalid) return false;

      // Extract the value from the read node.
      *aReadValue = mNode[tReadNode].mValue;

      // Push the previous head node back onto the free list.
      listPush(mQueueHead);

      // Update the head node to be the one that was just read from.
      mQueueHead = tReadNode;

      // Done.
      return true;
   }
#endif

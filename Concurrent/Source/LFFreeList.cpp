#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "prnPrint.h"

#include "LFIndex.h"
#include "LFFreeList.h"

using namespace std;

namespace LFFreeList
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Node for a combined Free List and Queue

   typedef struct
   {
      atomic<int>   mListNext;
   } ListNode;

   static const int cInvalid = 0x80000000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Free List Members

   bool listPush(int  aIndex);
   bool listPop(int* aIndex);

   atomic<int> mListHead;
   atomic<int> mListSize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Node array
   static ListNode* mNode = 0;

   // Number of blocks allocated
   static int mListAllocate = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Metrics Members

   atomic<unsigned long long> mPushRetry;
   atomic<unsigned long long> mPopRetry;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize(int aAllocate)
   {
      mListAllocate  = aAllocate;

      if (mNode) free(mNode);
      mNode = new ListNode[mListAllocate];

      for (int i = 0; i < mListAllocate - 1; i++)
      {
         mNode[i].mListNext = i + 1;
      }

      mNode[mListAllocate - 1].mListNext = cInvalid;

      mListSize = mListAllocate - 1;
      mListSize = mListAllocate;
      mListHead = 0;

      mPushRetry  = 0;
      mPopRetry   = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize

   void finalize()
   {
      if (mNode)
      {
         free(mNode);
         mNode = 0;
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show

   int listSize(){ return mListSize; }

   void show()
   {
      printf("LFFreeList\n");
      printf("PushRetry   %llu\n",mPushRetry);
      printf("PopRetry    %llu\n",mPopRetry);
      printf("ListSize    %d\n",  mListSize);
   }


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list before the list head node.

   bool listPush(int aNode)
   {
      // Store the head node in a temp.
      int tHead = mListHead;
      while (true)
      {
         // Attach the head node to the pushed node .
         mNode[aNode].mListNext = tHead;

         // The pushed node is the new head node.
         if (mListHead.compare_exchange_weak(tHead, aNode)) break;
         mPushRetry++;
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

   bool listPop(int* aNode)
   {
      // Store the head node in a temp.
      // This is the node that will be detached.
      int tHead = mListHead;
      while (true)
      {
         // Exit if the queue is empty.
         if (tHead == cInvalid) return false;

         // Set the head node to be the node that is after the head node.
         if (mListHead.compare_exchange_weak(tHead, mNode[tHead].mListNext)) break;
         mPopRetry++;
      }

      // Return result.
      *aNode = tHead;

      // Done.
      mListSize--;
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Test

   //***************************************************************************

   int mTest = 1;

   void initializeTest(int aTest)
   {
      mTest = aTest;
   }

   //***************************************************************************

   bool test()
   {
      int tNode;
      if (listPop(&tNode))
      {
         listPush(tNode);
         return true;
      }
      else
      {
         return false;
      }

      return true;
   }

}//namespace

/*==============================================================================

Non-blocking stack [Treiber’s algorithm]

proc push(new)
do
  old = top
  new.next = old
while not CAS(top, old, new)
end

proc pop
do
  old = top
  return null if old == null
  new = old.next
while not CAS(top, old, new)
return old
end



==============================================================================*/

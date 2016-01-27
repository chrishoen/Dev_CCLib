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
      AtomicLFIndex  mListNext;
   } ListNode;

   static const int cInvalid = 0x80000000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Free List Members

   bool listPush(int  aIndex);
   bool listPop(int* aIndex);

   AtomicLFIndex mListHead;
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
         mNode[i].mListNext.store(LFIndex(i+1,0));
      }

      mNode[mListAllocate-1].mListNext.store(LFIndex(cInvalid,0));

      mListHead.store(LFIndex(0,0));
      mListSize = mListAllocate;

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
      LFIndex tHead;

      int tLoopCount=0;
      while (true)
      {
         if (++tLoopCount==10000) throw 103;

         // Store the head node in a temp.
         tHead = mListHead.load();

         // Attach the head node to the pushed node .
         mNode[aNode].mListNext.store(tHead);

         // The pushed node is the new head node.
         if (mListHead.compare_exchange_strong(tHead, LFIndex(aNode, tHead.mCount+1))) break;
         mPushRetry++;
      }

      // Done.
      mListSize++;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the head node.

   bool listPop(int* aNode)
   {
      LFIndex tHead;

      int tLoopCount=0;
      while (true)
      {
         if (++tLoopCount==10000) throw 104;

         // Store the head node in a temp.
         // This is the node that will be detached.
         tHead = mListHead.load();

         // Exit if the list is empty.
         if (tHead.mIndex == cInvalid) return false;

         // Set the head node to be the node that is after the head node.
         if (mListHead.compare_exchange_strong(tHead, LFIndex(mNode[tHead.mIndex].mListNext.load().mIndex,tHead.mCount+1))) break;
         mPopRetry++;
      }

      // Return the detached original head node.
//    mNode[tHead.mIndex].mListNext.store(LFIndex(cInvalid,0));
      *aNode = tHead.mIndex;

      // Done.
      mListSize--;
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Test

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

   bool test1()
   {
      mPushRetry++;
      return true;
   }

   //***************************************************************************

   bool test2()
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

   //***************************************************************************

   bool test3()
   {
      int tNode1,tNode2;
      bool tPass1,tPass2;

      tPass1 = listPop(&tNode1);
      tPass2 = listPop(&tNode2);

      if (tPass2) listPush(tNode2);
      if (tPass1) listPush(tNode1);

      return tPass1 && tPass2;
   }

   //***************************************************************************

   bool test()
   {
      switch (mTest)
      {
      case 1: return test1();
      case 2: return test2();
      case 3: return test3();
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

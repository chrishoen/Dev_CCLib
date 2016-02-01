#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "my_functions.h"
#include "prnPrint.h"

#include "LFIndex.h"
#include "LFBackoff.h"
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

   bool listPop(int* aIndex);
   bool listPush(int  aIndex);

   atomic<int>   mListSize;
   AtomicLFIndex mListHead;
   
   atomic<int>* mListHeadIndexPtr = (atomic<int>*)&mListHead;
   atomic<int>& mListHeadIndexRef = (atomic<int>&)*mListHeadIndexPtr;

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

   atomic<unsigned long long> mPopRetry;
   atomic<unsigned long long> mPopRetry1;
   atomic<unsigned long long> mPopRetry2;
   atomic<unsigned long long> mPopRetry3;

   atomic<unsigned long long> mPushRetry;
   atomic<unsigned long long> mPushRetry1;
   atomic<unsigned long long> mPushRetry2;
   atomic<unsigned long long> mPushRetry3;

   unsigned long long popRetry()   {return mPopRetry.load();}
   unsigned long long pushRetry()  {return mPushRetry.load();}
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

      mPopRetry   = 0;
      mPopRetry1   = 0;
      mPopRetry2   = 0;
      mPopRetry3   = 0;
      mPushRetry  = 0;
      mPushRetry1  = 0;
      mPushRetry2  = 0;
      mPushRetry3  = 0;
      Prn::print(0, "LFFreeList::initialize %d",mListSize.load());
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
      char tString[40];
      Prn::print(0,"LFFreeList---------------------------\n");
      Prn::print(0,"PopRetry           %16s",my_stringLLU(tString,mPopRetry));
      Prn::print(0,"PopRetry1          %16s",my_stringLLU(tString,mPopRetry1));
      Prn::print(0,"PopRetry2          %16s",my_stringLLU(tString,mPopRetry2));
      Prn::print(0,"PopRetry3          %16s",my_stringLLU(tString,mPopRetry3));
      Prn::print(0,"");
      Prn::print(0,"PushRetry          %16s",my_stringLLU(tString,mPushRetry));
      Prn::print(0,"PushRetry1         %16s",my_stringLLU(tString,mPushRetry1));
      Prn::print(0,"PushRetry2         %16s",my_stringLLU(tString,mPushRetry2));
      Prn::print(0,"PushRetry3         %16s",my_stringLLU(tString,mPushRetry3));
      Prn::print(0,"");

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
         // Store the head node in a temp.
         // This is the node that will be detached.
         tHead = mListHead.load();

         // Exit if the list is empty.
         if (tHead.mIndex == cInvalid) return false;

         // Set the head node to be the node that is after the head node.
         if (mListHead.compare_exchange_weak(tHead, LFIndex(mNode[tHead.mIndex].mListNext.load().mIndex,tHead.mCount+1))) break;
         LFBackoff::wait();

         if (++tLoopCount==10000) throw 103;
      }
      if (tLoopCount != 0)
      {
         mPopRetry++;
         if (tLoopCount == 1) mPopRetry1++;
         else if (tLoopCount == 2) mPopRetry2++;
         else if (tLoopCount == 3) mPopRetry3++;
      }

      // Return the detached original head node.
      *aNode = tHead.mIndex;

      // Done.
      mListSize--;
      return true;
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
         // Store the head node in a temp.
         tHead = mListHead.load();

         // Attach the head node to the pushed node .
         mNode[aNode].mListNext.store(tHead);

         // The pushed node is the new head node.
         if (mListHeadIndexRef.compare_exchange_weak(tHead.mIndex, aNode)) break;
         LFBackoff::wait();

         if (++tLoopCount == 10000) throw 103;
      }
      if (tLoopCount != 0)
      {
         mPushRetry++;
         if (tLoopCount == 1) mPushRetry1++;
         else if (tLoopCount == 2) mPushRetry2++;
         else if (tLoopCount == 3) mPushRetry3++;
      }

      // Done.
      mListSize++;
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

   bool test4()
   {
      LFBackoff::wait();
      return true;
   }

   //***************************************************************************

   bool test()
   {
      switch (mTest)
      {
      case 1: return test1();
      case 2: return test2();
      case 3: return test3();
      case 4: return test4();
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

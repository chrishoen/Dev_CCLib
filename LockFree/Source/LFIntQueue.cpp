#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "my_functions.h"
#include "prnPrint.h"

#include "LFIndex.h"
#include "LFBackoff.h"
#include "LFIntQueue.h"

using namespace std;

namespace LFIntQueue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Support

   static const int cInvalid = 0x80000000;
   typedef unsigned long long int Padding[128];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Node Members

   static int*            mValue     = 0;
   static AtomicLFIndex*  mQueueNext = 0;
   static AtomicLFIndex*  mListNext  = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue Members

   AtomicLFIndex mQueueHead;
   AtomicLFIndex mQueueTail;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Free List Members

   bool listPush(int  aNode);
   bool listPop(int*  aNode);

   static atomic<int>   mListSize;
   static AtomicLFIndex mListHead;
   
   static atomic<int>* mListHeadIndexPtr = (atomic<int>*)&mListHead;
   static atomic<int>& mListHeadIndexRef = (atomic<int>&)*mListHeadIndexPtr;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Backoff Members

   static int mBackoffQueue1;
   static int mBackoffQueue2;
   static int mBackoffList1;
   static int mBackoffList2;

   void setBackoff(double aQueue1, double aQueue2,double aList1, double aList2)
   {
      mBackoffQueue1 = LFBackoff::convertFromUsec(aQueue1);
      mBackoffQueue2 = LFBackoff::convertFromUsec(aQueue2);
      mBackoffList1  = LFBackoff::convertFromUsec(aList1);
      mBackoffList2  = LFBackoff::convertFromUsec(aList2);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Backoff Members

   static int mBackoff11 = 0;
   static int mBackoff12 = 0;
   static int mBackoff21 = 0;
   static int mBackoff22 = 0;

   void initializeBackoff (int aB11, int aB12,int aB21, int aB22)
   {
      mBackoff11 = aB11;
      mBackoff12 = aB12;
      mBackoff21 = aB21;
      mBackoff22 = aB22;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Number of blocks allocated
   static int mAllocate = 0;
   static int mQueueAllocate = 0;
   static int mListAllocate = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Metrics Members

   atomic<unsigned long long> mWriteRetry;
   atomic<unsigned long long> mReadRetry;
   atomic<unsigned long long> mPopRetry;
   atomic<unsigned long long> mPushRetry;

   unsigned long long writeRetry() {return mWriteRetry.load();}
   unsigned long long readRetry()  {return mReadRetry.load();}
   unsigned long long popRetry()   {return mPopRetry.load();}
   unsigned long long pushRetry()  {return mPushRetry.load();}

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize(int aAllocate)
   {
      finalize();

      mAllocate      = aAllocate;
      mQueueAllocate = aAllocate + 1;
      mListAllocate  = aAllocate + 1;

      mValue = new int[mListAllocate];
      mQueueNext = new AtomicLFIndex[mListAllocate];
      mListNext = new AtomicLFIndex[mListAllocate];

      for (int i = 0; i < mListAllocate-1; i++)
      {
         mValue[i] = 0;
         mQueueNext[i].store(LFIndex(cInvalid,0));
         mListNext[i].store(LFIndex(i+1,0));
      }

      mValue[mListAllocate-1] = 0;
      mQueueNext[mListAllocate-1].store(LFIndex(cInvalid,0));
      mListNext[mListAllocate-1].store(LFIndex(cInvalid,0));

      mListHead.store(LFIndex(0,0));
      mListSize = mListAllocate;

      int tIndex;
      listPop(&tIndex);
      mQueueHead.store(LFIndex(tIndex,0));
      mQueueTail = mQueueHead.load();

      mWriteRetry = 0;
      mReadRetry  = 0;
      mPushRetry  = 0;
      mPopRetry   = 0;

      mBackoff11 = 0;
      mBackoff12 = 0;
      mBackoff21 = 0;
      mBackoff22 = 0;
}

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize

   void finalize()
   {
      if (mValue)     free(mValue);
      if (mQueueNext) free(mQueueNext);
      if (mListNext)  free(mListNext);
      mValue     = 0;
      mQueueNext = 0;
      mListNext  = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show

// int listSize(){ return mListHead.load().mCount; }
   int listSize(){ return mListSize.load(); }

   void show()
   {
      char tString[40];
      Prn::print(0,"LFIntQueue------------------\n");
      Prn::print(0,"WriteRetry         %16s",my_stringLLU(tString,mWriteRetry));
      Prn::print(0,"ReadRetry          %16s",my_stringLLU(tString,mReadRetry));
      Prn::print(0,"PopRetry           %16s",my_stringLLU(tString,mPopRetry));
      Prn::print(0,"PushRetry          %16s",my_stringLLU(tString,mPushRetry));
      Prn::print(0,"LFIntQueue------------------\n");
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds. It attempts to pop a node from the free list. If
   // the free list is empty then the queue is full and it exits. The value
   // is to be written is stored in the new node. The new node is then attached
   // to the queue tail node and the tail index is updated.

   bool tryWrite(int aValue)
   {
      // Try to allocate a node from the free list.
      // Exit if it is empty.
      LFIndex tNode;
      if (!listPop(&tNode.mIndex)) return false;

      // Initialize the node with the value.
      mValue[tNode.mIndex] = aValue;
      mQueueNext[tNode.mIndex].store(LFIndex(cInvalid,0));

      // Attach the node to the queue tail.
      LFIndex tTail,tNext;

      LFBackoff tBackoff(mBackoffQueue1,mBackoffQueue2);
      int tLoopCount=0;
      while (true)
      {
         tTail = mQueueTail.load();
         tNext = mQueueNext[tTail.mIndex].load();

         if (tTail == mQueueTail.load())
         {
            if (tNext.mIndex == cInvalid)
            {
               if (mQueueNext[tTail.mIndex].compare_exchange_weak(tNext, LFIndex(tNode.mIndex, tNext.mCount+1))) break;
            }
            else
            {
               mQueueTail.compare_exchange_weak(tTail, LFIndex(tNext.mIndex, tTail.mCount+1));
            }
         }

         if (++tLoopCount==10000) throw 101;
         tBackoff.expBackoff();
      }
      if (tLoopCount) mWriteRetry.fetch_add(1,memory_order_relaxed);

      mQueueTail.compare_exchange_strong(tTail, LFIndex(tNode.mIndex, tTail.mCount+1));

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

   bool tryRead(int* aValue)
   {
      LFIndex tHead, tTail, tNext;

      LFBackoff tBackoff(mBackoffQueue1,mBackoffQueue2);
      int tLoopCount=0;
      while (true)
      {
         tHead = mQueueHead.load();
         tTail = mQueueTail.load();
         tNext = mQueueNext[tHead.mIndex].load();

         if (tHead == mQueueHead.load())
         {
            if (tHead.mIndex == tTail.mIndex)
            {
               if (tNext.mIndex == cInvalid) return false;
               mQueueTail.compare_exchange_weak(tTail, LFIndex(tNext.mIndex, tTail.mCount+1));
            }
            else
            {
               *aValue = mValue[tNext.mIndex];
               if (mQueueHead.compare_exchange_weak(tHead, LFIndex(tNext.mIndex, tHead.mCount+1)))break;
            }
         }

         if (++tLoopCount==10000) throw 102;
         tBackoff.expBackoff();
      }
      if (tLoopCount) mReadRetry.fetch_add(1,memory_order_relaxed);

      listPush(tHead.mIndex);

      // Done.
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the head node.

   bool listPop(int* aNode)
   {
      LFIndex tHead;

      LFBackoff tBackoff(mBackoffList1,mBackoffList2);
      int tLoopCount=0;
      while (true)
      {
         // Store the head node in a temp.
         // This is the node that will be detached.
         tHead = mListHead.load();

         // Exit if the list is empty.
         if (tHead.mIndex == cInvalid) return false;

         // Set the head node to be the node that is after the head node.
         if (mListHead.compare_exchange_weak(tHead, LFIndex(mListNext[tHead.mIndex].load().mIndex,tHead.mCount+1))) break;

         if (++tLoopCount==10000) throw 103;
         tBackoff.expBackoff();
      }
      if (tLoopCount != 0)
      {
         mPopRetry.fetch_add(1,memory_order_relaxed);
      }

      // Return the detached original head node.
      *aNode = tHead.mIndex;

      // Done.
      mListSize.fetch_sub(1,memory_order_relaxed);
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list before the list head node.

   bool listPush(int aNode)
   {
      LFIndex tHead;

      LFBackoff tBackoff(mBackoffList1,mBackoffList2);
      int tLoopCount=0;
      while (true)
      {
         // Store the head node in a temp.
         tHead = mListHead.load();

         // Attach the head node to the pushed node .
         mListNext[aNode].store(tHead);

         // The pushed node is the new head node.
         if (mListHeadIndexRef.compare_exchange_weak(tHead.mIndex, aNode)) break;

         if (++tLoopCount == 10000) throw 103;
         tBackoff.expBackoff();
      }
      if (tLoopCount != 0)
      {
         mPushRetry.fetch_add(1,memory_order_relaxed);
      }

      // Done.
      mListSize.fetch_add(1,memory_order_relaxed);
      return true;
   }

}//namespace

/*==============================================================================
Non-blocking queue [Michael and Scott algorithm]

structure pointer_t {ptr:   pointer to node_t, count: unsigned integer}
structure node_t    {value: data_type,         next: pointer_t}
structure queue_t   {Head:  pointer t,         Tail: pointer_t}


initialize(Q: pointer to queue_t)
      node = new node()                                                # Allocate a free node
      node�>next.ptr = NULL                                            # Make it the only node in the linked list
      Q�>Head = Q�>Tail = node                                         # Both Head and Tail point to it



enqueue(Q: pointer to queue_t, value: data type)
E1:   node = new node()                                                # Allocate a new node from the free list  
E2:   node�>value = value                                              # Copy enqueued value into node
E3:   node�>next.ptr = NULL                                            # Set next pointer of node to NULL
E4:   loop                                                             # Keep trying until Enqueue is done
E5:       tail = Q�>Tail                                               # Read Tail.ptr and Tail.count together
E6:       next = tail.ptr�>next                                        # Read next ptr and count fields together
E7:       if tail == Q�>Tail                                           # Are tail and next consistent?
E8:           if next.ptr == NULL                                      # Was Tail pointing to the last node?
E9:               if CAS(&tail.ptr�>next, next, <node, next.count+1>)  # Try to link node at the end of the linked list
E10:                  break                                            # Enqueue is done. Exit loop
E11:              endif
E12:          else                                                     # Tail was not pointing to the last node
E13:              CAS(&Q�>Tail, tail, <next.ptr, tail.count+1>)        # Try to swing Tail to the next node
E14:          endif
E15:      endif
E16:    endloop
E17:    CAS(&Q�>Tail, tail, <node, tail.count+1>)                      # Enqueue is done. Try to swing Tail to the






dequeue(Q: pointer to queue t, pvalue: pointer to data type): boolean
D1:   loop                                                             # Keep trying until Dequeue is done
D2:       head = Q�>Head                                               # Read Head
D3:       tail = Q�>Tail                                               # Read Tail
D4:       next = head�>next                                            # Read Head.ptr�>next
D5:       if head == Q�>Head                                           # Are head, tail, and next consistent?
D6:           if head.ptr == tail.ptr                                  # Is queue empty or Tail falling behind?
D7:               if next.ptr == NULL                                  # Is queue empty?
D8:                   return FALSE                                     # Queue is empty, couldn�t dequeue
D9:               endif
D10:              CAS(&Q�>Tail, tail, <next.ptr, tail.count+1>)        # Tail is falling behind. Try to advance it
D11:          else                                                     # No need to deal with Tail
D12:              *pvalue = next.ptr�>value                            # Read value before CAS, otherwise another dequeue might free the next node
D13:              if CAS(&Q�>Head, head, <next.ptr, head.count+1>)     # Try to swing Head to the next node
D14:                  break                                            # Dequeue is done. Exit loop
D15:              endif
D16:          endif
D17:      endif
D18:  endloop
D19: free(head.ptr)                                                    # It is safe now to free the old dummy node
D20: return TRUE                                                       # Queue was not empty, dequeue succeeded









Non-blocking stack [Treiber�s algorithm]

proc push(node)
do
  old = head
  node.next = old
while not CAS(head, old, node)
end

proc pop
do
  old = head
  return null if old == null
while not CAS(head, old, <old.next,head.count+1>)
return head
end

==============================================================================*/

#if 0
   bool listPush2(int aNode)
   {
      LFIndex tHead;

      int tLoopCount=0;
      while (true)
      {
         if (++tLoopCount==10000) throw 103;

         // Store the head node in a temp.
         tHead = mListHead.load(memory_order_relaxed);

         // Attach the head node to the pushed node .
         mNode[aNode].mListNext.store(tHead,memory_order_relaxed);

         // The pushed node is the new head node.
         if (mListHead.compare_exchange_strong(tHead, LFIndex(aNode, tHead.mCount+1))) break;
         mPushRetry++;
      }

      // Done.
      mListSize++;
      return true;
   }

#endif
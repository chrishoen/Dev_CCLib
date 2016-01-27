#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "prnPrint.h"

#include "LFIndex.h"
#include "LFIntQueue.h"

using namespace std;

namespace LFIntQueue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Node for a combined Free List and Queue

   typedef struct
   {
      int            mValue;
      AtomicLFIndex  mQueueNext;
      AtomicLFIndex  mListNext;
   } QueueListNode;

   static const int cInvalid = 0x80000000;

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

   bool listPush(int  aIndex);
   bool listPop(int* aIndex);

   atomic<int>   mListSize;
   AtomicLFIndex mListHead;
   
   atomic<int>* mListHeadIndexPtr = (atomic<int>*)&mListHead;
   atomic<int>& mListHeadIndexRef = (atomic<int>&)*mListHeadIndexPtr;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Node array
   static QueueListNode* mNode = 0;

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
   atomic<unsigned long long> mPushRetry;
   atomic<unsigned long long> mPopRetry;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize(int aAllocate)
   {
      mAllocate      = aAllocate;
      mQueueAllocate = aAllocate + 1;
      mListAllocate  = aAllocate + 1;

      if (mNode) free(mNode);
      mNode = new QueueListNode[mListAllocate];

      for (int i = 0; i < mListAllocate-1; i++)
      {
         mNode[i].mValue = 0;
         mNode[i].mQueueNext.store(LFIndex(cInvalid,0));
         mNode[i].mListNext.store(LFIndex(i+1,0));
      }

      mNode[mListAllocate-1].mValue = 0;
      mNode[mListAllocate-1].mQueueNext.store(LFIndex(cInvalid,0));
      mNode[mListAllocate-1].mListNext.store(LFIndex(cInvalid,0));

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

// int listSize(){ return mListHead.load().mCount; }
   int listSize(){ return mListSize; }

   void show()
   {
      printf("LFIntQueue\n");
      printf("WriteRetry  %llu\n",mWriteRetry);
      printf("ReadRetry   %llu\n",mReadRetry);
      printf("PushRetry   %llu\n",mPushRetry);
      printf("PopRetry    %llu\n",mPopRetry);
      printf("ListSize    %d\n",  listSize());
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
      mNode[tNode.mIndex].mValue = aValue;
      mNode[tNode.mIndex].mQueueNext.store(LFIndex(cInvalid,0));

      // Attach the node to the queue tail.
      LFIndex tTail,tNext;
      int tLoopCount=0;
      while (true)
      {
         if (++tLoopCount==10000) throw 101;

         tTail = mQueueTail.load();
         tNext = mNode[tTail.mIndex].mQueueNext.load();

         if (tTail == mQueueTail.load())
         {
            if (tNext.mIndex == cInvalid)
            {
               if (mNode[tTail.mIndex].mQueueNext.compare_exchange_strong(tNext, LFIndex(tNode.mIndex, tNext.mCount+1))) break;
            }
            else
            {
               mQueueTail.compare_exchange_strong(tTail, LFIndex(tNext.mIndex, tTail.mCount+1));
            }
         }
         mWriteRetry++;
      }
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

      int tLoopCount=0;
      while (true)
      {
         if (++tLoopCount==10000) throw 102;

         tHead = mQueueHead.load();
         tTail = mQueueTail.load();
         tNext = mNode[tHead.mIndex].mQueueNext.load();

         if (tHead == mQueueHead.load())
         {
            if (tHead.mIndex == tTail.mIndex)
            {
               if (tNext.mIndex == cInvalid) return false;
               mQueueTail.compare_exchange_strong(tTail, LFIndex(tNext.mIndex, tTail.mCount+1));
            }
            else
            {
               *aValue = mNode[tNext.mIndex].mValue;
               if (mQueueHead.compare_exchange_strong(tHead, LFIndex(tNext.mIndex, tHead.mCount+1)))break;
            }
         }
         mReadRetry++;
      }
      listPush(tHead.mIndex);

      // Done.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list before the list head node.

   bool listPush2(int aNode)
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

   bool listPush(int aNode)
   {
      LFIndex tHead;

      int tLoopCount=0;
      while (true)
      {
         if (++tLoopCount == 10000) throw 103;

         // Store the head node in a temp.
         tHead = mListHead.load();

         // Attach the head node to the pushed node .
         mNode[aNode].mListNext.store(tHead);

         // The pushed node is the new head node.
         if (mListHeadIndexRef.compare_exchange_strong(tHead.mIndex, aNode)) break;
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

   int mTest = 1;

   void initializeTest(int aTest)
   {
      mTest = aTest;
   }

   //***************************************************************************

   bool test1()
   {
      mWriteRetry++;
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
Non-blocking queue [Michael and Scott algorithm]

structure pointer_t {ptr:   pointer to node_t, count: unsigned integer}
structure node_t    {value: data_type,         next: pointer_t}
structure queue_t   {Head:  pointer t,         Tail: pointer_t}


initialize(Q: pointer to queue_t)
      node = new node()                                                # Allocate a free node
      node–>next.ptr = NULL                                            # Make it the only node in the linked list
      Q–>Head = Q–>Tail = node                                         # Both Head and Tail point to it



enqueue(Q: pointer to queue_t, value: data type)
E1:   node = new node()                                                # Allocate a new node from the free list  
E2:   node–>value = value                                              # Copy enqueued value into node
E3:   node–>next.ptr = NULL                                            # Set next pointer of node to NULL
E4:   loop                                                             # Keep trying until Enqueue is done
E5:       tail = Q–>Tail                                               # Read Tail.ptr and Tail.count together
E6:       next = tail.ptr–>next                                        # Read next ptr and count fields together
E7:       if tail == Q–>Tail                                           # Are tail and next consistent?
E8:           if next.ptr == NULL                                      # Was Tail pointing to the last node?
E9:               if CAS(&tail.ptr–>next, next, <node, next.count+1>)  # Try to link node at the end of the linked list
E10:                  break                                            # Enqueue is done. Exit loop
E11:              endif
E12:          else                                                     # Tail was not pointing to the last node
E13:              CAS(&Q–>Tail, tail, <next.ptr, tail.count+1>)        # Try to swing Tail to the next node
E14:          endif
E15:      endif
E16:    endloop
E17:    CAS(&Q–>Tail, tail, <node, tail.count+1>)                      # Enqueue is done. Try to swing Tail to the






dequeue(Q: pointer to queue t, pvalue: pointer to data type): boolean
D1:   loop                                                             # Keep trying until Dequeue is done
D2:       head = Q–>Head                                               # Read Head
D3:       tail = Q–>Tail                                               # Read Tail
D4:       next = head–>next                                            # Read Head.ptr–>next
D5:       if head == Q–>Head                                           # Are head, tail, and next consistent?
D6:           if head.ptr == tail.ptr                                  # Is queue empty or Tail falling behind?
D7:               if next.ptr == NULL                                  # Is queue empty?
D8:                   return FALSE                                     # Queue is empty, couldn’t dequeue
D9:               endif
D10:              CAS(&Q–>Tail, tail, <next.ptr, tail.count+1>)        # Tail is falling behind. Try to advance it
D11:          else                                                     # No need to deal with Tail
D12:              *pvalue = next.ptr–>value                            # Read value before CAS, otherwise another dequeue might free the next node
D13:              if CAS(&Q–>Head, head, <next.ptr, head.count+1>)     # Try to swing Head to the next node
D14:                  break                                            # Dequeue is done. Exit loop
D15:              endif
D16:          endif
D17:      endif
D18:  endloop
D19: free(head.ptr)                                                    # It is safe now to free the old dummy node
D20: return TRUE                                                       # Queue was not empty, dequeue succeeded









Non-blocking stack [Treiber’s algorithm]

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

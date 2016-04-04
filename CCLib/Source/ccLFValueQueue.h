#ifndef _CCLFVALUEQUEUE_H_
#define _CCLFVALUEQUEUE_H_
/*==============================================================================

Lock Free Value Queue Class TEmplate. 

This implements a value queue. The queue is thread safe. It uses a atomic
interlocked compare and exchanges to guard against concurrency contentions.
It implements the Michael and Scott algorithm with no backoff.
This can be used for Multiple Writer Multiple Reader.

This implements a value queue. It uses a atomic interlocked compare and
exchanges to guard against concurrency contentions.

It implements the Michael and Scott algorithm with no backoff. It maintains
storage for the blocks by implementing a free list that uses the Trieber 
algorithm with no backoff.

This can be used for Multiple Writer Muliple Reader.

==============================================================================*/
#include <atomic>
#include "ccLFIndex.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element>
class LFValueQueue
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // Number of values allocated
   int mAllocate;
   int mQueueAllocate;
   int mListAllocate;

   // Array of values
   Element* mValue;

   // Queue array and variables
   AtomicLFIndex*    mQueueNext;
   AtomicLFIndex     mQueueHead;
   AtomicLFIndex     mQueueTail;

   // Free List array and variables
   AtomicLFIndex*    mListNext;
   AtomicLFIndex     mListHead;
   std::atomic<int>  mListSize;

   std::atomic<int>* mListHeadIndexPtr = (std::atomic<int>*)&mListHead;

   static const int  cInvalid = 0x80000000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor

   LFValueQueue()
   {
      // All null
      mValue = 0;
      mQueueNext = 0;
      mListNext = 0;
      mAllocate = 0;
      mQueueAllocate = 0;
      mListAllocate = 0;
   }

   ~LFValueQueue()
   {
      finalize();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize(int aAllocate)
   {
      finalize();

      mAllocate = aAllocate;
      mQueueAllocate = aAllocate + 1;
      mListAllocate = aAllocate + 1;

      mValue = new Element[mListAllocate];
      mQueueNext = new AtomicLFIndex[mListAllocate];
      mListNext = new AtomicLFIndex[mListAllocate];

      for (int i = 0; i < mListAllocate - 1; i++)
      {
         mValue[i] = 0;
         mQueueNext[i].store(LFIndex(cInvalid, 0));
         mListNext[i].store(LFIndex(i + 1, 0));
      }

      mValue[mListAllocate - 1] = 0;
      mQueueNext[mListAllocate - 1].store(LFIndex(cInvalid, 0));
      mListNext[mListAllocate - 1].store(LFIndex(cInvalid, 0));

      mListHead.store(LFIndex(0, 0));
      mListSize = mListAllocate;

      int tIndex;
      listPop(&tIndex);
      mQueueHead.store(LFIndex(tIndex, 0));
      mQueueTail = mQueueHead.load();

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
      mValue = 0;
      mQueueNext = 0;
      mListNext = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Size

   int size()
   {
      return mListAllocate - mListSize.load(std::memory_order_relaxed);
   }


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds. It attempts to pop a node from the free list. If
   // the free list is empty then the queue is full and it exits. The value
   // is to be written is stored in the new node. The new node is then attached
   // to the queue tail node and the tail index is updated.

   bool tryWrite(Element aValue)
   {
      // Try to allocate a node from the free list.
      // Exit if it is empty.
      int tNodeIndex;
      if (!listPop(&tNodeIndex)) return false;

      // Initialize the node with the value.
      mValue[tNodeIndex] = aValue;
      mQueueNext[tNodeIndex].store(LFIndex(cInvalid, 0), std::memory_order_relaxed);

      // Attach the node to the queue tail.
      LFIndex tTail, tNext;

      int tLoopCount = 0;
      while (true)
      {
         tTail = mQueueTail.load(std::memory_order_relaxed);
         tNext = mQueueNext[tTail.mIndex].load(std::memory_order_acquire);

         if (tTail == mQueueTail.load(std::memory_order_relaxed))
         {
            if (tNext.mIndex == cInvalid)
            {
               if (mQueueNext[tTail.mIndex].compare_exchange_strong(tNext, LFIndex(tNodeIndex, tNext.mCount + 1), std::memory_order_release, std::memory_order_relaxed)) break;
            }
            else
            {
               mQueueTail.compare_exchange_weak(tTail, LFIndex(tNext.mIndex, tTail.mCount + 1), std::memory_order_release, std::memory_order_relaxed);
            }
         }

         if (++tLoopCount == 10000) throw 101;
      }

      mQueueTail.compare_exchange_strong(tTail, LFIndex(tNodeIndex, tTail.mCount + 1), std::memory_order_release, std::memory_order_relaxed);

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

   bool tryRead(Element* aValue)
   {
      LFIndex tHead, tTail, tNext;

      int tLoopCount = 0;
      while (true)
      {
         tHead = mQueueHead.load(std::memory_order_relaxed);
         tTail = mQueueTail.load(std::memory_order_acquire);
         tNext = mQueueNext[tHead.mIndex].load(std::memory_order_relaxed);

         if (tHead == mQueueHead.load(std::memory_order_acquire))
         {
            if (tHead.mIndex == tTail.mIndex)
            {
               if (tNext.mIndex == cInvalid) return false;
               mQueueTail.compare_exchange_strong(tTail, LFIndex(tNext.mIndex, tTail.mCount + 1), std::memory_order_release, std::memory_order_relaxed);
            }
            else
            {
               *aValue = mValue[tNext.mIndex];
               if (mQueueHead.compare_exchange_strong(tHead, LFIndex(tNext.mIndex, tHead.mCount + 1), std::memory_order_acquire, std::memory_order_relaxed))break;
            }
         }

         if (++tLoopCount == 10000) throw 102;
      }

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
      // Store the head node in a temp.
      // This is the node that will be detached.
      LFIndex tHead = mListHead.load(std::memory_order_relaxed);

      int tLoopCount = 0;
      while (true)
      {
         // Exit if the list is empty.
         if (tHead.mIndex == cInvalid) return false;

         // Set the head node to be the node that is after the head node.
         if (mListHead.compare_exchange_weak(tHead, LFIndex(mListNext[tHead.mIndex].load(std::memory_order_relaxed).mIndex, tHead.mCount + 1), std::memory_order_acquire, std::memory_order_relaxed)) break;

         if (++tLoopCount == 10000) throw 103;
      }

      // Return the detached original head node.
      *aNode = tHead.mIndex;

      // Done.
      mListSize.fetch_sub(1, std::memory_order_relaxed);
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list before the list head node.

   bool listPush(int aNode)
   {
      // Store the head node in a temp.
      LFIndex tHead = mListHead.load(std::memory_order_relaxed);

      int tLoopCount = 0;
      while (true)
      {
         // Attach the head node to the pushed node.
         mListNext[aNode].store(tHead, std::memory_order_relaxed);

         // The pushed node is the new head node.
         if ((*mListHeadIndexPtr).compare_exchange_weak(tHead.mIndex, aNode, std::memory_order_release, std::memory_order_relaxed)) break;
         if (++tLoopCount == 10000) throw 103;
      }

      // Done.
      mListSize.fetch_add(1, std::memory_order_relaxed);
      return true;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
#endif


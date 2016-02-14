#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "my_functions.h"
#include "prnPrint.h"

#include "LFIndex.h"
#include "LFBackoff.h"
#include "LFIntQueueMSCP.h"

using namespace std;

namespace LFIntQueueMSCP
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Support

   static const int cInvalid = 0x80000000;

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

   int size(){ return mListAllocate - mListSize.load(memory_order_relaxed); }

   void show()
   {
      char tString[40];
      Prn::print(0,"LFIntQueueMSCP------------------");
      Prn::print(0,"WriteRetry         %16s",my_stringLLU(tString,mWriteRetry));
      Prn::print(0,"ReadRetry          %16s",my_stringLLU(tString,mReadRetry));
      Prn::print(0,"PopRetry           %16s",my_stringLLU(tString,mPopRetry));
      Prn::print(0,"PushRetry          %16s",my_stringLLU(tString,mPushRetry));
      Prn::print(0,"LFIntQueueMSCP------------------");
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
      mQueueNext[tNode.mIndex].store(LFIndex(cInvalid,0),memory_order_relaxed);

      // Attach the node to the queue tail.
      LFIndex tTail,tNext;

      int tLoopCount=0;
      while (true)
      {
         tTail = mQueueTail.load();
         tNext = mQueueNext[tTail.mIndex].load(memory_order_acquire);

         if (tNext.mIndex != cInvalid)
         {
            mQueueTail.compare_exchange_weak(tTail, LFIndex(tNext.mIndex, tTail.mCount+1),memory_order_release,memory_order_relaxed);
         }
         else
         {
            if (mQueueNext[tTail.mIndex].compare_exchange_strong(tNext, LFIndex(tNode.mIndex, tNext.mCount + 1), memory_order_release, memory_order_relaxed)) break;
         }

         if (++tLoopCount==10000) my_halt("tryWrite");
      }
      if (tLoopCount) mWriteRetry.fetch_add(1,memory_order_relaxed);

      mQueueTail.compare_exchange_strong(tTail, LFIndex(tNode.mIndex, tTail.mCount+1),memory_order_release,memory_order_relaxed);

      // Done
      return true;
   }
#if 0
        bool enqueue( value_type& val )
        {
            node_type * pNew = node_traits::to_node_ptr( val );
            link_checker::is_empty( pNew );

            typename gc::Guard guard;
            back_off bkoff;

            node_type * t;
            while ( true ) {
                t = guard.protect( m_pTail, []( node_type * p ) -> value_type * { return node_traits::to_value_ptr( p );});

                node_type * pNext = t->m_pNext.load(memory_model::memory_order_acquire);
                if ( pNext != nullptr ) {
                    // Tail is misplaced, advance it
                    m_pTail.compare_exchange_weak( t, pNext, memory_model::memory_order_release, atomics::memory_order_relaxed );
                    m_Stat.onBadTail();
                    continue;
                }

                node_type * tmp = nullptr;
                if ( t->m_pNext.compare_exchange_strong( tmp, pNew, memory_model::memory_order_release, atomics::memory_order_relaxed ))
                    break;

                m_Stat.onEnqueueRace();
                bkoff();
            }
            ++m_ItemCounter;
            m_Stat.onEnqueue();

            if ( !m_pTail.compare_exchange_strong( t, pNew, memory_model::memory_order_release, atomics::memory_order_relaxed ))
                m_Stat.onAdvanceTailFailed();
            return true;
        }
#endif
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
         tHead = mQueueHead.load(memory_order_acquire);
         tNext = mQueueNext[tHead.mIndex].load(memory_order_relaxed);

         if (tHead != mQueueHead.load(memory_order_acquire))
         {
            continue;
         }

         if (tNext.mIndex == cInvalid) return false;

         tTail = mQueueTail.load(memory_order_acquire);

         if (tHead.mIndex == tTail.mIndex)
         {
            mQueueTail.compare_exchange_strong(tTail, LFIndex(tNext.mIndex, tTail.mCount+1),memory_order_release,memory_order_relaxed);
            continue;
         }

         *aValue = mValue[tNext.mIndex];
         if (mQueueHead.compare_exchange_strong(tHead, LFIndex(tNext.mIndex, tHead.mCount+1),memory_order_acquire,memory_order_relaxed))break;

         if (++tLoopCount==10000) my_halt("tryRead");
      }
      if (tLoopCount) mReadRetry.fetch_add(1,memory_order_relaxed);

      listPush(tHead.mIndex);

      // Done.
      return true;
   }
#if 0
        bool do_dequeue( dequeue_result& res )
        {
            node_type * pNext;
            back_off bkoff;

            node_type * h;
            while ( true ) {
                h = res.guards.protect( 0, m_pHead, []( node_type * p ) -> value_type * { return node_traits::to_value_ptr( p );});
                pNext = res.guards.protect( 1, h->m_pNext, []( node_type * p ) -> value_type * { return node_traits::to_value_ptr( p );});
                if ( m_pHead.load(memory_model::memory_order_acquire) != h )
                    continue;

                if ( pNext == nullptr ) {
                    m_Stat.onEmptyDequeue();
                    return false;    // empty queue
                }

                node_type * t = m_pTail.load(memory_model::memory_order_acquire);
                if ( h == t ) {
                    // It is needed to help enqueue
                    m_pTail.compare_exchange_strong( t, pNext, memory_model::memory_order_release, atomics::memory_order_relaxed );
                    m_Stat.onBadTail();
                    continue;
                }

                if ( m_pHead.compare_exchange_strong( h, pNext, memory_model::memory_order_acquire, atomics::memory_order_relaxed ))
                    break;

                m_Stat.onDequeueRace();
                bkoff();
            }

            --m_ItemCounter;
            m_Stat.onDequeue();

            res.pHead = h;
            res.pNext = pNext;
            return true;
        }
#endif
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the head node.

   bool listPop(int* aNode)
   {
      // Store the head node in a temp.
      // This is the node that will be detached.
      LFIndex tHead = mListHead.load(memory_order_relaxed);

      int tLoopCount=0;
      while (true)
      {
         // Exit if the list is empty.
         if (tHead.mIndex == cInvalid) return false;

         // Set the head node to be the node that is after the head node.
         if (mListHead.compare_exchange_weak(tHead, LFIndex(mListNext[tHead.mIndex].load(memory_order_relaxed).mIndex,tHead.mCount+1),memory_order_acquire,memory_order_relaxed)) break;

         if (++tLoopCount==10000) my_halt("listPop");
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
      // Store the head node in a temp.
      LFIndex tHead = mListHead.load(memory_order_relaxed);

      int tLoopCount=0;
      while (true)
      {
         // Attach the head node to the pushed node.
         mListNext[aNode].store(tHead,memory_order_relaxed);

         // The pushed node is the new head node.
         if ((*mListHeadIndexPtr).compare_exchange_weak(tHead.mIndex, aNode,memory_order_release,memory_order_relaxed)) break;
         if (++tLoopCount == 10000) my_halt("listPush");
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

==============================================================================*/


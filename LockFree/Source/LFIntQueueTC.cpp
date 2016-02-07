#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "my_functions.h"
#include "prnPrint.h"

#include "LFIndex.h"
#include "LFBackoff.h"
#include "LFIntQueueTC.h"

using namespace std;

namespace LFIntQueueTC
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Support

   static const unsigned cFree0   = 0;
   static const unsigned cFree1   = 1;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue Members

   static atomic<unsigned>* mArray;

   static atomic<unsigned> mHead;
   static atomic<unsigned> mTail;
   static atomic<int> mItemCounter;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Number of blocks allocated
   static unsigned mAllocate = 0;
   static unsigned mModulo = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Metrics Members

   atomic<unsigned long long> mWriteRetry;
   atomic<unsigned long long> mReadRetry;

   unsigned long long writeRetry() { return mWriteRetry.load(); }
   unsigned long long readRetry()  { return mReadRetry.load(); }
   unsigned long long popRetry()   { return 0; }
   unsigned long long pushRetry()  { return 0; }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize(int aAllocate)
   {
      finalize();

      mAllocate = (unsigned)(aAllocate);
      mModulo   = mAllocate - 1;

      mArray = new atomic<unsigned>[mAllocate];

      for (unsigned i = 0; i < mAllocate; i++)
      {
         mArray[i].store(0);
      }

      mHead.store(0);
      mTail.store(1);
      mItemCounter.store(0);

      mWriteRetry = 0;
      mReadRetry = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize

   void finalize()
   {
      if (mArray)     free(mArray);
      mArray = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show

   int listSize(){ return mItemCounter.load(); }

   void show()
   {
      char tString[40];
      Prn::print(0, "LFIntQueueTC------------------");
      Prn::print(0, "WriteRetry         %16s", my_stringLLU(tString, mWriteRetry));
      Prn::print(0, "ReadRetry          %16s", my_stringLLU(tString, mReadRetry));
      Prn::print(0, "LFIntQueueTC------------------");
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   bool is_free(unsigned aIndex){ return (aIndex & 0xFFFFFFFE) == 0; }

   bool tryWrite(int aValue)
   {
      unsigned tValue = (((unsigned)aValue)<<1) | 0x80000000;

      int tLoopCount=0;
      while (true)
      {
         unsigned te = mTail.load(memory_order_acquire);
         unsigned ate = te;
         unsigned tt = mArray[ ate ].load(memory_order_relaxed);
         unsigned temp = ( ate + 1 ) & mModulo ;    // next item after tail

         // Looking for actual tail
         while ( !is_free( tt ) )
         {
            if (te != mTail.load(memory_order_relaxed))    // check the tail consistency
            {
               goto TryAgain;
            }
            if (temp == mHead.load(memory_order_acquire))    // queue full?
            {
               break;
            }
            tt = mArray[ temp ].load(memory_order_relaxed);
            ate = temp;
            temp = (temp + 1) & mModulo;
         }

         if (te != mTail.load(memory_order_acquire))
         {
            continue;
         }

         // Check whether queue is full
         if ( temp == mHead.load(memory_order_acquire) )
         {
            ate = ( temp + 1 ) & mModulo;
            tt = mArray[ ate ].load(memory_order_relaxed);
            if ( !is_free( tt ) )
            {
               return false;   // Queue is full
            }

            // Help the dequeue to update head
            mHead.compare_exchange_strong( temp, ate, memory_order_release, memory_order_relaxed );
            continue;
         }

         if (tt == cFree1)
         {
            tValue |= 1;
         }
         if (te != mTail.load(memory_order_acquire))
         {
            continue;
         }

         // Get actual tail and try to enqueue new node
         if ( mArray[ate].compare_exchange_strong( tt, tValue, memory_order_release, memory_order_relaxed ) )
         {
            if (temp % 2 == 0)
            {
               mTail.compare_exchange_strong(te, temp, memory_order_release, memory_order_relaxed);
            }
            ++mItemCounter;
            return true;
         }
      TryAgain:;
         if (++tLoopCount==10000) throw 101;
      }

      // No control path reaches this line!
      return false;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryRead(int* aValue)
   {
      int tLoopCount=0;
      while(true)
      {
         unsigned th = mHead.load(memory_order_acquire);
         unsigned temp = ( th + 1 ) & mModulo;
         unsigned tt = mArray[ temp ].load(memory_order_relaxed);
         unsigned pNull=0;

         // find the actual head after this loop
         while ( is_free( tt ) )
         {
            if (th != mHead.load(memory_order_relaxed))
            {
               goto TryAgain;
            }

            // two consecutive nullptr means the queue is empty
            if (temp == mTail.load(memory_order_acquire))
            {
               return false;
            }

            temp = ( temp + 1 ) & mModulo;
            tt = mArray[ temp ].load(memory_order_relaxed);
         }

         if (th != mHead.load(memory_order_relaxed))
         {
            continue;
         }

         // check whether the queue is empty
         if ( temp == mTail.load(memory_order_acquire) )
         {
            // help the enqueue to update end
            mTail.compare_exchange_weak( temp, (temp + 1) & mModulo, memory_order_release, memory_order_relaxed );
            continue;
         }

         pNull = tt & 1 ? cFree0 : cFree1;

         if (th != mHead.load(memory_order_relaxed))
         {
            continue;
         }

         // Get the actual head, null means empty
         if ( mArray[temp].compare_exchange_weak( tt, pNull, memory_order_acquire, memory_order_relaxed ))
         {
            if (temp % 2 == 0)
            {
               mHead.compare_exchange_weak(th, temp, memory_order_release, memory_order_relaxed);
            }
            --mItemCounter;
            *aValue = (int)((tt&0x7FFFFFFF)>>1);
            return true;
         }

      TryAgain:;
         if (++tLoopCount==10000) throw 101;
      }

      // Done.
      return false;
   }

}//namespace

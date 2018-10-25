#pragma once

/*==============================================================================

Single Reader Multiple Writer Value Queue class template. 

It is multiple writer single reader thread safe.
It lockes with critcal sections for mutual exclusion, blocking.
It is shared memory safe.

This implements a queue of fixed size objects, where the queue provides the
memory allocation for the objects (memory for the objects is contained
within the queue). The queue is thread safe. It uses mutexes to guard
against concurrency contentions.

It is thread safe for separate multiple writer and single reader threads.

It is based on the single writer single reader queue with mutual
exclusion critical sections added.

==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <new>

#include "ccDefs.h"
#include "cc_functions.h"
#include "ccMemoryPtr.h"
#include "ccCriticalSection.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element>
class LCValueQueue
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Array of queue values, storage for the values.
   // NumElements is Size + 1.
   // Index range is 0..Size.
   Element* mElement;

   // Number of elements allocated.
   int mNumElements;

   // Queue array indices.
   int mPutIndex;
   int mGetIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Critical section.
   void* mCriticalSection;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   LCValueQueue()
   {
      mElement = 0;
      mNumElements = 0;
      mPutIndex = 0;
      mGetIndex = 0;
      mCriticalSection = createCriticalSection();
   }

   ~LCValueQueue()
   {
      finalize();
      destroyCriticalSection(mCriticalSection);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   void initialize(int aSize)
   {
      // Deallocate memory, if any exists.
      finalize();

      // Allocate for one extra dummy element.
      mNumElements = aSize + 1;
      mPutIndex = 0;
      mGetIndex = 0;

      // Allocate memory for the array.
      mElement = new Element[mNumElements];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize.

   void finalize()
   {
      if (mElement == 0) return;
      delete mElement;
      mElement = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This is the current size of the queue. It is the difference between the 
   // mPutIndex and the mGetIndex.

   int size()
   {
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = mNumElements + tSize;
      return tSize;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds.
   // 
   // This tests if put operations are allowed. Puts are allowed if the 
   // current size is less than or equal to Allocate - 2. If the size is equal
   // to Allocate - 2 then the next put operation would put the size to
   // mNumElements - 1, which is the max number of elements. This is the same
   // as "is not full".
   // 
   // This puts an element to the queue and advances the put index. It does a 
   // copy from a source element into the queue array element at the put index.
   // It uses a temp index variable so that writing to the index is atomic.

   bool tryWrite (Element aElement)
   {
      // Lock.
      enterCriticalSection(mCriticalSection);

      // Test if the queue is full.
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = mNumElements + tSize;
      if (tSize > mNumElements - 2)
      {
         // Unlock.
         leaveCriticalSection(mCriticalSection);
         return false;
      }

      // Local put index.
      int tPutIndex = mPutIndex;
      // Copy the source element into the element at the queue put index
      mElement[tPutIndex] = aElement;
      // Advance the put index.
      if(++tPutIndex == mNumElements) tPutIndex = 0;
      mPutIndex = tPutIndex;

      // Unlock.
      leaveCriticalSection(mCriticalSection);
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to read a value to the queue. If the queue is not empty
   // then it succeeds.
   //
   // This gets an element from the queue and advances the get index. It does a 
   // copy from the queue array element at the get index into a destination
   // element. It uses a temp index variable so that writing to the index is
   // atomic. Note that the destination element must be of element size.
  
   bool tryRead(Element* aValue)
   {
      // Test if the queue is empty.
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = mNumElements + tSize;
      if (tSize == 0) return false;

      // Local index
      int tGetIndex = mGetIndex;
      // Copy the queue array element at the get index
      *aValue = mElement[tGetIndex];
      // Advance the get index
      if(++tGetIndex == mNumElements) tGetIndex = 0;
      mGetIndex = tGetIndex;

      // Done.
      return true;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


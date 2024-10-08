#pragma once

/*==============================================================================

Single reader single writer object queue class template.

It is single writer single reader thread safe.
It is lock free and non blocking.
It is shared memory safe.

This implements an object queue.

It is thread safe for separate single writer and single reader threads.

==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element,int NumElements>
class SRSWObjectQueue
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Element access indices.
   int mPutIndex;
   int mGetIndex;

   // Array of elements. The number of occupied elements varies
   // 0..NumElements-1
   Element mElement[NumElements];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   void reset()
   {
      // Initialize variables.
      mPutIndex = 0;
      mGetIndex = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This is the current size of the queue. It is the number of occupied
   // elements.

   int size()
   {
      int tOccupied = mPutIndex - mGetIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      return tOccupied;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds.
   // 
   // The queue is full when it has NumElements-1 occupied elements. 
   // Note: this is NumElements-1, not NumElements. The queue only uses
   // at most NumElements-1. It reserves one element to act as a buffer
   // between puts and gets, so that concurrent puts and gets on the same
   // element are avoided.
   // 
   // This tests if put operations are allowed, if the queue is not full.
   // Puts are allowed if the  current number of occupied elements is less
   // than NumElements-1. If puts are allowed then it returns a pointer
   // to the element to put to.
   // 

   Element* startPut()
   {
      // Local put index.
      int tPutIndex = mPutIndex;
      // Test if the queue is full.
      int tOccupied = tPutIndex - mGetIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied >= NumElements - 1) return false;

      // Return a pointer to the element at the put index.
      return &mElement[tPutIndex];
   }

   void finishPut()
   {
      // Local put index.
      int tPutIndex = mPutIndex;
      // Advance the put index.
      if (++tPutIndex == NumElements) tPutIndex = 0;
      mPutIndex = tPutIndex;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to read a value to the queue. If the queue is not empty
   // then it succeeds. The queue is not empty if the put index is not equal
   // to the get index.
   //
   // If the queue is empty, return a null pointer. 
   // If the queue is not empty, return a pointer to the element to get from.
  
   Element* startGet()
   {
      // Local index.
      int tGetIndex = mGetIndex;
      // Test if the queue is empty.
      int tOccupied = mPutIndex - tGetIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == 0) return 0;

      // Return a pointer to the element at the get index.
      return &mElement[mGetIndex];
   }

   void finishGet()
   {
      // Local index.
      int tGetIndex = mGetIndex;
      // Advance the get index.
      if (++tGetIndex == NumElements) tGetIndex = 0;
      mGetIndex = tGetIndex;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


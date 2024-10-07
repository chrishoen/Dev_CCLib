#pragma once

/*==============================================================================

Single reader single writer value queue class template. 

It is single writer single reader thread safe.
It is lock free and non blocking.
It is shared memory safe.

This implements a value queue. 

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
class SRSWValueQueue
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
   // than NumElements-1. If puts are allowed then it copies the new
   // element to the array and increments the put index.
   // 

   bool tryWrite (Element aElement)
   {
      // Local put index.
      int tPutIndex = mPutIndex;
      // Test if the queue is full.
      int tOccupied = tPutIndex - mGetIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied >= NumElements - 1) return false;

      // Copy the source element into the element at the queue put index.
      mElement[tPutIndex] = aElement;
      // Advance the put index.
      if(++tPutIndex == NumElements) tPutIndex = 0;
      mPutIndex = tPutIndex;
      // Done.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to read a value to the queue. If the queue is not empty
   // then it succeeds. The queue is not empty if the put index is not equal
   // to the get index.
   //
   // This gets an element from the queue and advances the get index. It does a 
   // copy from the queue array element at the get index into a destination
   // element.
  
   bool tryRead(Element* aValue)
   {
      // Local index.
      int tGetIndex = mGetIndex;
      // Test if the queue is empty.
      int tOccupied = mPutIndex - tGetIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == 0) return false;

      // Copy the queue array element at the get index.
      *aValue = mElement[tGetIndex];
      // Advance the get index.
      if(++tGetIndex == NumElements) tGetIndex = 0;
      mGetIndex = tGetIndex;

      // Done.
      return true;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


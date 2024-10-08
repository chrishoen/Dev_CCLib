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

   // Element access indices. They vary as 0..NumElements-1. 
   int mPutIndex;
   int mGetIndex;

   // Array of elements.
   Element mElement[NumElements];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   void reset()
   {
      mPutIndex = 0;
      mGetIndex = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Return the current size of the queue. It is the number of occupied
   // elements. It varies as 0..NumElements-1. This is not thread safe
   // and should only be used for display purposes.

   int size()
   {
      int tOccupied = mPutIndex - mGetIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      return tOccupied;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to put a value to the queue. If the queue is not full then
   // copy the element to the queue array at the index, increment the index,
   // and return true. If the queue is full then return false.
   // 
   // The queue is full when it has NumElements-1 occupied elements. 
   // Note: The queue only stores at most NumElements-1 elements. It reserves
   // one element to act as a buffer between puts and gets, so that concurrent
   // puts and gets on the same element are avoided.

   bool tryPut (Element aElement)
   {
      // Get local indices.
      int tPutIndex = mPutIndex;
      int tGetIndex = mGetIndex;

      // Test if the queue is full.
      int tOccupied = tPutIndex - tGetIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == NumElements - 1) return false;

      // Copy the source element into the array at the put index.
      mElement[tPutIndex] = aElement;
      // Advance the put index.
      if(++tPutIndex == NumElements) tPutIndex = 0;
      mPutIndex = tPutIndex;

      // Success.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to get a value from the queue. If the queue is not empty
   // then copy the element at the get index, increment the get index, and
   // return true. If the queue is empty then return false. 
   // 
   // The queue is not empty if the put index is not equal to the get index.
   // Or, the queue is not empty when the number of occupied elements is
   // greater than zero.

   bool tryGet(Element* aValue)
   {
      // Get local indices.
      int tPutIndex = mPutIndex;
      int tGetIndex = mGetIndex;

      // Test if the queue is empty.
      int tOccupied = tPutIndex - tGetIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == 0) return false;

      // Copy the queue array element at the get index.
      *aValue = mElement[tGetIndex];
      // Advance the get index.
      if(++tGetIndex == NumElements) tGetIndex = 0;
      mGetIndex = tGetIndex;

      // Success.
      return true;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


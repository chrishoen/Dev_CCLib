#pragma once

/*==============================================================================

Fixed delay memory class template. 

It is not thread safe.
It is not shared memory safe.

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
// This template implements a memory structure that provides a fixed
// delay. It can be used for digital filters.

template <class T,int N>
class NDelay
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Index of the next element to put to. This increments indefinitely 
   // with every put operation. 
   int mPutIndex;

   // If true then the queue is full and get operations can commence.
   bool mFullFlag;

   // Array of elements.
   T mElement[N];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   NDelay()
   {
      reset();
   }

   void reset()
   {
      mPutIndex = 0;
      mFullFlag = false;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This writes an element to the head of the queue.

   bool doPut (T& aValue)
   {
      // Copy the value into the element at the queue put index.
      mElement[mPutIndex % N] = aValue;

      // Advance the put index.
      ++mPutIndex;

      // Set the full flag.
      return mFullFlag = mPutIndex >= N;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This reads an element from the tail. This is only valid if 
   // the queue is full. The tail is always a fixed length from the
   // put index.
   
   T& doGet()
   {
      // Calculate the get index.
      int tGetIndex = mPutIndex + N;

      // Return the element at the get index.
      return mElement[tGetIndex % N];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns a pointer to an element that is relative
   // to the first gettable element.

   T& elementAt(int aIndex)
   {
      // Calculate the get index.
      int tGetIndex = (mPutIndex - 1 - aIndex);

      // Return the element at the get index.
      return mElement[tGetIndex % N];
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

#if 0

    Z^-3   Z^-2  Z^-1  1
    k-3    k-2   k-1   k

k   0      1     2     3

#endif
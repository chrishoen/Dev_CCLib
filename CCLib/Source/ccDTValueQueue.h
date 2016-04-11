#ifndef _CC_DTVALUEQUEUE_H_
#define _CC_DTVALUEQUEUE_H_

/*==============================================================================

Template for queue of values

==============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class template for a queue of values, as opposed to blocks.

template <class Element>
class DTValueQueue
{
public:

   //***************************************************************************
   // Members

   int mNumElements;
   int mPutIndex;
   int mGetIndex;

   Element* mElement;
   
   //***************************************************************************
   // Constructor, initialize members for an empty queue of size zero 

   DTValueQueue()
   {
      // All null
      mNumElements = 0;
      mPutIndex = 0;
      mGetIndex = 0;
      mElement  = 0;
   }

   //***************************************************************************
   // Destructor, deallocate the queue array

  ~DTValueQueue()
   {
     // Deallocate the array
     if (mElement) delete mElement;
   }

   //***************************************************************************
   // This initializes the queue to a fixed size. It initializes member
   // variables and allocates heap storage for the queue array. The queue has
   // a specified maximum number of elements and it allocates memory for the
   // maximum number of elements plus one, there is an extra element allocated.

   void initialize(int aNumOfElements)
   {
      // Initialize variables
      mPutIndex = 0;
      mGetIndex = 0;
      // Allocate memory for the array to have an extra element
      mNumElements = aNumOfElements + 1;

      // Allocate memory for the array
      mElement = new Element[mNumElements];
   }

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
      // Test if the queue is full.
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = mNumElements + tSize;
      if (tSize > mNumElements - 2) return false;

      // Local put index
      int tPutIndex = mPutIndex;
      // Copy the source element into the element at the queue put index
      mElement[tPutIndex] = aElement;
      // Advance the put index
      if(++tPutIndex == mNumElements) tPutIndex = 0;
      mPutIndex = tPutIndex;
      // Done
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

}//namespace
#endif
   //***************************************************************************

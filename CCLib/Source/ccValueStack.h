#ifndef _VALUESTACK_H_
#define _VALUESTACK_H_
/*==============================================================================

This defines a stack of values. It can be used by specialized heaps
and pools as an allocator.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a stack of values. The values can be int or pointer
// types. It is assumed that zero is used for a null value.
 
template <class Element>
class ValueStack
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // Array of values, dynamically allocated by initialize.
   Element* mElement;
   
   // Index into the array.
   int mIndex;

   // Size of the array, number of pointers allocated.
   int mAllocate;

   // Count of allocated elements. This is incremented by pop operations and
   // decremented by push operations. This is a usage counter that is used
   // to track usage of the stack.
   int mCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor, initialize members for an empty queue of size zero 

   ValueStack()
   {
      // All null
      mAllocate = 0;
      mPutIndex = 0;
      mGetIndex = 0;
      mElement = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Destructor, deallocate the queue array

  ~ValueStack()
   {
     // Deallocate the array
     if (mElement) delete mElement;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This initializes the queue to a fixed size. It initializes member
   // variables and allocates heap storage for the queue array. The queue has
   // a specified maximum number of elements and it allocates memory for the
   // maximum number of elements plus one, there is an extra element allocated.

   void initialize(int aMaxNumOfElements)
   {
      // Initialize variables
      mIndex = 0;
      mAllocate = aMaxNumOfElements;
      // Allocate memory for the array
      mElement = new Element[mAllocate];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Push a value onto the stack. Return false if the stack is full.

   bool push(Element aValue);
   {
      // Guard
      if (mIndex == mAllocate) return false;


      //Copy the source element to the element at the stack index
      mElement[mIndex] = aValue;
      // Increment the index
      ++mIndex;
      // Increment the usage counter
      mCount++;

      // Done
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Pop a value off of the stack. Return null if the stack is empty.

   Element pop();
   {
      // Guard
      if (mIndex == 0) return 0;

      // Pop the element above the stack index into a temp pointer
      Element tValue = mArray[mIndex - 1];
      // Decrement the index
      --mIndex;
      // Decrement the usage counter
      mCount--;

      // Return the temp pointer
      return tValue;
   }
};

//******************************************************************************

}//namespace
#endif


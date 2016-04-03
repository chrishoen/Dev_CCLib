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

   // Array of elements, dynamically allocated by initialize.
   Element* mElement;
   
   // Index into the array.
   int mIndex;

   // Size of the array, number of elements allocated.
   int mNumElements;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor, initialize members for an empty queue of size zero 

   ValueStack()
   {
      // All null
      mElement     = 0;
      mNumElements = 0;
      mIndex       = 0;
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

   void initialize(int aNumElements)
   {
      finalize();
      // Initialize variables
      mIndex = 0;
      mNumElements = aNumElements;
      // Allocate memory for the array
      mElement = new Element[mNumElements];
   }

   void finalize()
   {
      // Deallocate the array
      if (mElement)
      {
         delete mElement;
         mElement = 0;
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Push a value onto the stack. Return false if the stack is full.

   bool push(Element aValue)
   {
      // Guard for stack full
      if (mIndex == mNumElements) return false;


      // Copy the source element to the element at the stack index
      mElement[mIndex] = aValue;
      // Increment the index
      mIndex++;

      // Done
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Pop a value off of the stack. Return false if the stack is empty.

   bool pop(Element* aValue)
   {
      // Guard
      if (mIndex == 0) return false;

      // Copy the element below the stack index to the destination element
      *aValue = mElement[mIndex - 1];
      // Decrement the index
      mIndex--;

      // Return success
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Return size.

   int size() {return mIndex;}

};

//******************************************************************************

}//namespace
#endif


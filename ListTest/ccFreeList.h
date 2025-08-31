#pragma once

/*==============================================================================

Free list class template.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This template establishes a free list of elements. It contains a fixed
// size array of elements and a stack array of pointers into the element
// array. It provides allocate and deallocate methods that pop and push
// element pointers from the stack.

template <class Element,int NumElements>
class FreeList
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Array of elements.
   Element mElementArray[NumElements];

   // Array of elements pointers.
   Element* mPointerStackArray[NumElements];

   // Pointer stack index.
   int mStackIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   FreeList()
   {
      reset();
   }

   void reset()
   {
      mStackIndex = 0;
      for (int i = 0; i < NumElements; i++)
      {
         mPointerStackArray[i] = &mElementArray[i];
      }
      mStackIndex = NumElements - 1;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Allocate an element from the free list by popping an element pointer
   // from the pointer stack.
   Element* doAllocate()
   {
      if (mStackIndex == -1) return 0;
      return mPointerStackArray[mStackIndex--];
   }

   // Free an element to the free list by pushing an element pointer to
   // the pointer stack. 
   void doFree(Element* aPointer)
   {
      if (mStackIndex == NumElements - 1) return;
      mPointerStackArray[++mStackIndex] = aPointer;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


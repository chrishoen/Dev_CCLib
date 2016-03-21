#ifndef _CCLFREELIST_H_
#define _CCFREELIST_H_
/*==============================================================================

Free List Class Template. 

This implements a free list of fixed size blocks.
The free list is not thread safe.

==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element>
class FreeList
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   Element*  mElementArray;  // Array of elements
   Element** mPointerStack;  // Array of pointers that point at the elements.
   int mStackIndex;          // Stack index
   int mAllocate;            // Number of elemnts allocated

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Methods

   // Constructor
   FreeList()
   {
      // All null
      mElementArray = 0;
      mPointerStack = 0;
      mStackIndex = 0;
      mAllocate = 0;
   }

   ~FreeList()
   {
      // Deallocate memory
      finalize();
   }

   //***************************************************************************
   // Allocate memory for the free list arrays and initialize the free list
   // member variables. aAllocate is the number of blocks to allocate
   // memory for.

   void initialize(int aAllocate)
   {
      finalize();

      // Allocate memory for the arrays.
      mElementArray = new Element [aAllocate];
      mPointerStack = new Element*[aAllocate];

      // Initialize the pointer stack to point at the elements.
      for (int i = 0; i < aAllocate; i++)
      {
         mPointerStack[i] = &mElementArray[i];
      }

      // Initialize the stack index for a full stack.
      mStackIndex = aAllocate-1;
      mAllocate = aAllocate;
   }

   //***************************************************************************
   // Deallocate memory.

   void finalize()
   {
      if (mElementArray)
      {
         delete[] mElementArray;
         mElementArray=0;
      }
      if (mPointerStack)
      {
         delete[] mPointerStack;
         mPointerStack=0;
      }
   }

   //***************************************************************************
   // Return size, which is the number of elements available.

   int size() {return mStackIndex;}

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Pop an element from the free list. Return null if the list is empty.

   Element* listPop()
   {
      // If the free list is empty then return null.
      if (mStackIndex == 0)
      {
         return 0;
      }

      // Pop a pointer from the stack
      return mPointerStack[mStackIndex--];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Push an elemnt to the free list.

   bool listPush (Element* aElement)
   {
      // Guard against no initialization.
      if (mStackIndex==0)
      {
         return false;
      }

      // If the free list is full then return.
      if (mStackIndex==cAllocate-1) return false;

      // Push the pointer to the stack
      mPointerStack[++mStackIndex] = aElement;
   }
};

//******************************************************************************

}//namespace
#endif


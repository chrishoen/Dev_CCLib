#ifndef _CCLFFREELIST_H_
#define _CCLFFREELIST_H_
/*==============================================================================

Free List Stack of Indices. 

This implements a fixed size free list stack of indices. The free list is 
not thread safe.

==============================================================================*/
#include <atomic>
#include "ccLFIndex.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class FreeListStack
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Constructor
   FreeListStack();
  ~FreeListStack();

   // This initializes the stack to a fixed size. It initializes member
   // variables and allocates system memory for the stack array.
   // The stack is initialized to full.
   void initialize(int aNumElements);

   // Deallocate memory.
   void finalize();

   // Pop a value off of the stack. Return false if the stack is empty.
   bool pop(int* aValue);

   // Push a value onto the stack. Return false if the stack is full.
   bool push(int aValue);

   // Return size.
   int size();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // Array of elements, dynamically allocated by initialize.
   int* mElement;
   
   // Index into the array.
   int mIndex;

   // Size of the array, number of elements allocated.
   int mNumElements;

};

//******************************************************************************

}//namespace
#endif


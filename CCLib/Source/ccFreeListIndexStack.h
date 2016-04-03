#ifndef _CCLFFREELIST_H_
#define _CCLFFREELIST_H_
/*==============================================================================

Free List Stack of Indices. 

This implements a free list stack of indices. It is not thread safe.

==============================================================================*/
#include <atomic>
#include "ccLFIndex.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This encapsulates a stack of indices to be used with containers that 
// implement free lists of blocks.

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class FreeListIndexStack
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Constructor
   FreeListIndexStack();
  ~FreeListIndexStack();

   // Initialize the stack for a fixed size. Initialize member variables and
   // allocate system memory for the stack array.
   // Initialize the stack to full. Push the indices of the blocks for which 
   // this will be used onto the stack.
   // For aAllocate==10 this will push 0,1,2,3,4,5,6,7,8,9
   void initialize(int aNumElements);

   // Deallocate memory.
   void finalize();

   // Pop a value off of the stack. Return false if the stack is empty.
   bool pop(int* aValue);

   // Push a value onto the stack. Return false if the stack is full.
   bool push(int aValue);

   // Return size, the number of elements that have been pushed onto the stack.
   int size();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // Array of indices, dynamically allocated by initialize.
   int* mElement;
   
   // Index into the array.
   int mIndex;

   // Size of the array, number of elements allocated.
   int mNumElements;
};

//******************************************************************************

}//namespace
#endif


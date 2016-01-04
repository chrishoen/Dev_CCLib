#ifndef _INTEGERSTACK_H_
#define _INTEGERSTACK_H_
/*==============================================================================

This defines a stack of void* Integers. It can be used by specialized heaps
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
// This class encapsulates a Integer stack. It maintains an array of Integers
// that are dynamically allocated at initialization. Access to the array is 
// done is a stack manner, with pushes and pops.

class IntegerStack
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   IntegerStack();
  ~IntegerStack();

   // Allocate memory for the stack array and initialize the stack index. 
   // aAllocate is the number of Integers to allocate, the size of the array.
   void initialize(int aAllocate);

   // Push a Integer onto the stack. Return false if the stack is full.
   bool  push(void* aInteger);

   // Pop a Integer off of the stack. Return null if the stack is empty.
   void* pop();

   //---------------------------------------------------------------------------
   // Members

   // Array of Integers, dynamically allocated by initialize.
   void** mArray;

   // Index into the array.
   int mIndex;

   // Size of the array, number of Integers allocated.
   int mAllocate;

   // Count of allocated elements. This is incremented by pop operations and
   // decremented by push operations. This is a usage counter that is used
   // to track usage of the stack.
   int mCount;
};

//******************************************************************************

}//namespace
#endif


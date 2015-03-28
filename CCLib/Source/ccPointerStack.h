#ifndef _POINTERSTACK_H_
#define _POINTERSTACK_H_
/*==============================================================================

This defines a stack of void* pointers. It can be used by specialized heaps
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
// This class encapsulates a pointer stack. It maintains an array of pointers
// that are dynamically allocated at initialization. Access to the array is 
// done is a stack manner, with pushes and pops.

class PointerStack
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   PointerStack();
  ~PointerStack();

   // Allocate memory for the stack array and initialize the stack index. 
   // aAllocate is the number of pointers to allocate, the size of the array.
   void initialize(int aAllocate);

   // Push a pointer onto the stack. Return false if the stack is full.
   bool  push(void* aPointer);

   // Pop a pointer off of the stack. Return null if the stack is empty.
   void* pop();

   //---------------------------------------------------------------------------
   // Members

   // Array of pointers, dynamically allocated by initialize.
   void** mArray;

   // Index into the array.
   int mIndex;

   // Size of the array, number of pointers allocated.
   int mAllocate;
};

//******************************************************************************

}//namespace
#endif


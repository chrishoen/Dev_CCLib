#ifndef _TOKENSTACK_H_
#define _TOKENSTACK_H_
/*==============================================================================

This defines a stack of Tokens. It can be used by specialized heaps
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
// This class encapsulates a Token stack. It maintains an array of Tokens
// that are dynamically allocated at initialization. Access to the array is 
// done is a stack manner, with pushes and pops.

class TokenStack
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   TokenStack();
  ~TokenStack();

   // Allocate memory for the stack array and initialize the stack index. 
   // aAllocate is the number of Tokens to allocate, the size of the array.
   void initialize(int aCapacity);

   // Push a Token onto the stack. Return false if the stack is full.
   bool tryPush(int aToken);

   // Pop a Token off of the stack. Return null if the stack is empty.
   bool tryPop(int* aToken);

   //---------------------------------------------------------------------------
   // Members

   // Array of Tokens, dynamically allocated by initialize.
   int* mArray;

   // Index into the array.
   int mIndex;

   // Size of the array, number of Tokens allocated.
   int mCapacity;
};

//******************************************************************************

}//namespace
#endif


#ifndef _TOKENSTACK_H_
#define _TOKENSTACK_H_
/*==============================================================================

This defines a stack of Tokens. It can be used by specialized heaps
and pools as an allocator.

==============================================================================*/
#include <windows.h>

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
   void initialize(LONG aCapacity);

   // Push a Token onto the stack. Return false if the stack is full.
   BOOLEAN push(LONG aToken);

   // Pop a Token off of the stack. Return null if the stack is empty.
   BOOLEAN pop(LONG* aToken);

   //---------------------------------------------------------------------------
   // Members

   // Array of Tokens, dynamically allocated by initialize.
   LONG* mArray;

   // Index into the array.
   LONG mIndex;

   // Size of the array, number of Tokens allocated.
   LONG mCapacity;
};

//******************************************************************************

}//namespace
#endif


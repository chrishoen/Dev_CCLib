/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>

#include "ccFreeListStack.h"

using namespace std;

namespace CC
{
//***************************************************************************
//***************************************************************************
//***************************************************************************
// Constructor, initialize members for an empty stack of size zero 

FreeListStack::FreeListStack()
{
   // All null.
   mElement     = 0;
   mNumElements = 0;
   mIndex       = 0;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Destructor, deallocate the array

FreeListStack::~FreeListStack()
{
   finalize();
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// This initializes the stack to a fixed size. It initializes member
// variables and allocates system memory for the stack array.

void FreeListStack::initialize(int aNumElements)
{
   finalize();
   // Initialize variables.
   mIndex = 0;
   mNumElements = aNumElements;
   // Allocate memory for the array.
   mElement = new int[mNumElements];

   // Push the indices of the blocks in the array onto the index stack.
   // For aAllocate==10 this will push 9,8,7,6,5,4,3,2,1,0
   for (int i = mNumElements-1; i >= 0; i--)
   {
      push(i);
   }
}

void FreeListStack::finalize()
{
   // Deallocate the array.
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

bool FreeListStack::push(int aValue)
{
   // Guard for stack full.
   if (mIndex == mNumElements) return false;


   // Copy the source element to the element at the stack index.
   mElement[mIndex] = aValue;
   // Increment the index.
   mIndex++;

   // Done
   return true;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Pop a value off of the stack. Return false if the stack is empty.

bool FreeListStack::pop(int* aValue)
{
   // Guard
   if (mIndex == 0) return false;

   // Copy the element below the stack index to the destination element.
   *aValue = mElement[mIndex - 1];
   // Decrement the index.
   mIndex--;

   // Return success.
   return true;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Return size.

int FreeListStack::size()
{
   return mIndex;
}

}//namespace
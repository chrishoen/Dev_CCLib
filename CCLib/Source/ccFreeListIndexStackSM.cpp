/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>

#include "ccFreeListIndexStackSM.h"

using namespace std;

namespace CC
{

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Constructor, initialize members for an empty stack of size zero 

FreeListIndexStackSMState::FreeListIndexStackSMState()
{
   // All null.
   mNumElements = 0;
   mIndex       = 0;
}

void FreeListIndexStackSMState::initialize(int aNumElements)
{
   // Initialize variables.
   mIndex = 0;
   mNumElements = aNumElements;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Constructor, initialize members for an empty stack of size zero 

FreeListIndexStackSM::FreeListIndexStackSM()
{
   // All null.
   mX = 0;
   mElement = 0;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Destructor, deallocate the array

FreeListIndexStackSM::~FreeListIndexStackSM()
{
   finalize();
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// This initializes the stack to a fixed size. It initializes member
// variables and allocates system memory for the stack array.

void FreeListIndexStackSM::initialize(int aNumElements)
{
   finalize();
   // Initialize variables.
   mX = new FreeListIndexStackSMState;
   mX->initialize(aNumElements);
   // Allocate memory for the array.
   mElement = new int[mX->mNumElements];

   // Push the indices of the blocks in the array onto the index stack.
   // For aAllocate==10 this will push 0,1,2,3,4,5,6,7,8,9
   for (int i=0; i<mX->mNumElements; i++)
   {
      push(i);
   }
}

void FreeListIndexStackSM::finalize()
{
   // Deallocate the state.
   if (mX)
   {
      delete mX;
      mX = 0;
   }

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

bool FreeListIndexStackSM::push(int aValue)
{
   // Guard for stack full.
   if (mX->mIndex == mX->mNumElements) return false;


   // Copy the source element to the element at the stack index.
   mElement[mX->mIndex] = aValue;
   // Increment the index.
   mX->mIndex++;

   // Done
   return true;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Pop a value off of the stack. Return false if the stack is empty.

bool FreeListIndexStackSM::pop(int* aValue)
{
   // Guard
   if (mX->mIndex == 0) return false;

   // Copy the element below the stack index to the destination element.
   *aValue = mElement[mX->mIndex - 1];
   // Decrement the index.
   mX->mIndex--;

   // Return success.
   return true;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Return size.

int FreeListIndexStackSM::size()
{
   return mX->mIndex;
}

}//namespace
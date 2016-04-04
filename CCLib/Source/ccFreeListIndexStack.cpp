/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "cc_functions.h"
#include "ccFreeListIndexStack.h"

using namespace std;

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

FreeListIndexStackState::FreeListIndexStackState()
{
   // All null.
   mNumElements = 0;
   mIndex       = 0;
}

void FreeListIndexStackState::initialize(int aNumElements)
{
   // Initialize variables.
   mIndex = 0;
   mNumElements = aNumElements;
}

int FreeListIndexStackState::getMemorySize()
{
   return cc_round_upto16(sizeof(FreeListIndexStackState));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

FreeListIndexStack::FreeListIndexStack()
{
   // All null.
   mX = 0;
   mElement = 0;
   mExternalMemoryFlag = false;
   mMemory = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destructor, deallocate the array

FreeListIndexStack::~FreeListIndexStack()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the stack to a fixed size. It initializes member
// variables and and the stack array, given external memory.

void FreeListIndexStack::initialize(int aNumElements,void* aMemory)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize memory.

   // Deallocate memory, if any exists.
   finalize();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mMemory = malloc(FreeListIndexStack::getMemorySize(aNumElements));
      mExternalMemoryFlag = false;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mExternalMemoryFlag = true;
   }

   // Calculate memory sizes.
   int tStateSize = FreeListIndexStackState::getMemorySize();
   int tArraySize = aNumElements*sizeof(int);

   // Calculate memory addresses.
   char* tStateMemory = (char*)mMemory;
   char* tArrayMemory = tStateMemory + tStateSize;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Initialize state.
   mX = new(tStateMemory) FreeListIndexStackState;
   mX->initialize(aNumElements);

   // Initialize the element array.
   mElement = new(tArrayMemory) int[mX->mNumElements];

   // Push the indices of the blocks in the array onto the index stack.
   // For aAllocate==10 this will push 9,8,8,6,5,4,3,2,1,0
   for (int i = mX->mNumElements-1; i >= 0; i--)
   {
      push(i);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FreeListIndexStack::finalize()
{
   if (!mExternalMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
      mMemory = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int FreeListIndexStack::getMemorySize(int aNumElements)
{
   int tStateSize = FreeListIndexStackState::getMemorySize();
   int tArraySize = cc_round_upto16(aNumElements*sizeof(int));
   int tMemorySize = tStateSize + tArraySize;
   return tMemorySize;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Push a value onto the stack. Return false if the stack is full.

bool FreeListIndexStack::push(int aValue)
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Pop a value off of the stack. Return false if the stack is empty.

bool FreeListIndexStack::pop(int* aValue)
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return size.

int FreeListIndexStack::size()
{
   return mX->mIndex;
}

}//namespace
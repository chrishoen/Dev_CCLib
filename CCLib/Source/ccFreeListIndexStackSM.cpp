/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <new>

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

int FreeListIndexStackSMState::getSharedMemorySize()
{
   return sizeof(FreeListIndexStackSMState);
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
   mExternalMemoryFlag = false;
   mMemory = 0;
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
// variables and and the stack array, given external memory.

void FreeListIndexStackSM::initialize(int aNumElements,void* aMemory)
{
   // Deallocate memory, if any exists.
   finalize();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mMemory = malloc(FreeListIndexStackSM::getSharedMemorySize(aNumElements));
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
   int tStateSize = FreeListIndexStackSMState::getSharedMemorySize();
   int tElementArraySize = aNumElements*sizeof(int);

   // Calculate memory addresses.
   char* tStateMemory   = (char*)mMemory;
   char* tElementMemory = tStateMemory + tStateSize;

   // Initialize state.
   mX = new(tStateMemory) FreeListIndexStackSMState;
   mX->initialize(aNumElements);

   // Initialize the element array.
   mElement = new(tElementMemory) int[mX->mNumElements];

   // Push the indices of the blocks in the array onto the index stack.
   // For aAllocate==10 this will push 0,1,2,3,4,5,6,7,8,9
   for (int i=0; i<mX->mNumElements; i++)
   {
      push(i);
   }
}

//***************************************************************************
//***************************************************************************
//***************************************************************************

void FreeListIndexStackSM::finalize()
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

//***************************************************************************
//***************************************************************************
//***************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int FreeListIndexStackSM::getSharedMemorySize(int aNumElements)
{
   int tStateSize = FreeListIndexStackSMState::getSharedMemorySize();
   int tElementArraySize = aNumElements*sizeof(int);
   int tSharedMemorySize = tStateSize + tElementArraySize;
   return tSharedMemorySize;
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
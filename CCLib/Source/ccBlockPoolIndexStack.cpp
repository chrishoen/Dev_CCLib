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
#include "ccDefs.h"
#include "ccMemoryPtr.h"
#include "ccBlockPoolIndexStack.h"

using namespace std;

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero. 

int BlockPoolIndexStackState::getMemorySize()
{
   return cc_round_upto16(sizeof(BlockPoolIndexStackState));
}

BlockPoolIndexStackState::BlockPoolIndexStackState()
{
   // All null.
   mNumElements = 0;
   mIndex       = 0;
}

void BlockPoolIndexStackState::initialize(BlockPoolParms* aParms)
{
   // Do not initialize, if already initialized.
   if (!aParms->mConstructorFlag) return;

   // Initialize variables.
   mIndex = 0;
   mNumElements = aParms->mNumBlocks;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This local class calculates and stores the memory sizes needed by the class.

class BlockPoolIndexStack::MemorySize
{
public:
   // Members.
   int mStateSize;
   int mArraySize;
   int mMemorySize;

   // Calculate and store memory sizes.
   MemorySize::MemorySize(BlockPoolParms* aParms)
   {
      mStateSize = BlockPoolIndexStackState::getMemorySize();
      mArraySize = cc_round_upto16(cNewArrayExtraMemory + aParms->mNumBlocks*sizeof(int));
      mMemorySize = mStateSize + mArraySize;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockPoolIndexStack::getMemorySize(BlockPoolParms* aParms)
{
   MemorySize tMemorySize(aParms);
   return tMemorySize.mMemorySize;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

BlockPoolIndexStack::BlockPoolIndexStack()
{
   // All null.
   mX = 0;
   mElement = 0;
   mOwnMemoryFlag = false;
   mMemory = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destructor, deallocate the array

BlockPoolIndexStack::~BlockPoolIndexStack()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the stack to a fixed size. It initializes member
// variables and and the stack array, given external memory.

void BlockPoolIndexStack::initialize(BlockPoolParms* aParms,void* aMemory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize memory.

   // Deallocate memory, if any exists.
   finalize();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mMemory = malloc(BlockPoolIndexStack::getMemorySize(aParms));
      mOwnMemoryFlag = true;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mOwnMemoryFlag = false;
   }

   // Calculate memory sizes.
   MemorySize tMemorySize(aParms);

   // Calculate memory addresses.
   MemoryPtr tMemoryPtr(mMemory);

   char* tStateMemory = tMemoryPtr.cfetch_add(tMemorySize.mStateSize);
   char* tArrayMemory = tMemoryPtr.cfetch_add(tMemorySize.mArraySize);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize variables.

   // Construct the state.
   if (aParms->mConstructorFlag)
   {
      // Call the constructor.
      mX = new(tStateMemory)BlockPoolIndexStackState;
   }
   else
   {
      // The constructor has already been called.
      mX = (BlockPoolIndexStackState*)tStateMemory;
   }
   // Initialize the state.
   mX->initialize(aParms);

   // Construct the element array.
   if (aParms->mConstructorFlag)
   {
      // Call the constructor.
      mElement = new(tArrayMemory) int[mX->mNumElements];
   }
   else
   {
      // The constructor has already been called.
      mElement = (int*)tArrayMemory;
   }

   // Initialize the element array, if it has not already been initialized.
   if (aParms->mConstructorFlag)
   {
      // Push the indices of the blocks in the array onto the index stack.
      // For aAllocate==10 this will push 9,7,8,6,5,4,3,2,1,0
      for (int i = mX->mNumElements - 1; i >= 0; i--)
      {
         push(i);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Deallocate memory for the stack.

void BlockPoolIndexStack::finalize()
{
   if (mOwnMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
   }
   mMemory = 0;
   mOwnMemoryFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Push a value onto the stack. Return false if the stack is full.

bool BlockPoolIndexStack::push(int aValue)
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

bool BlockPoolIndexStack::pop(int* aValue)
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

int BlockPoolIndexStack::size()
{
   return mX->mIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
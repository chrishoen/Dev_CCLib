/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "ccBlockPool.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockPool::BlockPool()
{
}

BlockPool::~BlockPool()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a pool of persistent memory blocks. At 
// initialization, it allocates an array of blocks and it allocates a stack
// of pointers into the blocks. To allocate a block from the pool, a pointer is 
// popped from the stack. To free a block, a pointer is pushed back onto the
// stack. This is thread safe because it the stack accesses use critical
// sections. 

void BlockPool::initializeShortTerm(int aAllocate, int aBlockSize)
{
   // Set the block pool type
   mBlockPoolType = BlockPoolType_ShortTerm;

   // Allocate memory for the block array
   mBlocks.initialize(aAllocate,aBlockSize);

   // Initialize the pointer circular array
   mShortTermPointerCircular.initialize(aAllocate);

   // Push the addresses of the blocks in the array onto the pointer stack.
   for (int i = 0; i < aAllocate; i++)
   {
      mShortTermPointerCircular.put(mBlocks.e(i));
   }
}

void BlockPool::initializeLongTerm(int aAllocate, int aBlockSize)
{
   // Set the block pool type
   mBlockPoolType = BlockPoolType_LongTerm;

   // Allocate memory for the block array
   mBlocks.initialize(aAllocate,aBlockSize);

   // Initialize the pointer stack
   mLongTermPointerStack.initialize(aAllocate);

   // Push the addresses of the blocks in the array onto the pointer stack.
   for (int i = 0; i < aAllocate; i++)
   {
      mLongTermPointerStack.push(mBlocks.e(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, this allocates a block. It pops a pointer
// from the pointer stack.

void* BlockPool::get()
{
   if (mBlockPoolType == BlockPoolType_ShortTerm)
   {
      return mShortTermPointerCircular.get();
   }
   else if (mBlockPoolType == BlockPoolType_LongTerm)
   {
      return mLongTermPointerStack.pop();
   }
   else
   {
      return 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block. It pushes a 
// pointer onto the pointer stack.

void BlockPool::put(void* aBlockPointer)
{
   if (mBlockPoolType == BlockPoolType_ShortTerm)
   {
   }
   else if (mBlockPoolType == BlockPoolType_LongTerm)
   {
      mLongTermPointerStack.push(aBlockPointer);
   }
}
}//namespace
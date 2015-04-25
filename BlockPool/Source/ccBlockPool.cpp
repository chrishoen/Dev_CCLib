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
// This initializes the block pool for short term blocks. It allocates memory
// for the block array and initializes the circular pointer array. It is
// passed the number of blocks to allocate and the size of the blocks.

void BlockPool::initializeShortTerm(int aAllocate, int aBlockSize)
{
   // Set the block pool type
   mBlockPoolType = BlockPoolType_ShortTerm;

   // Allocate memory for the block array
   mBlocks.initialize(aAllocate,aBlockSize);

   // Initialize the pointer circular array
   mShortTermPointerCircular.initialize(aAllocate);

   // Push the addresses of the blocks in the array onto the pointer 
   // circular array.
   for (int i = 0; i < aAllocate; i++)
   {
      mShortTermPointerCircular.put(mBlocks.e(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the block pool for long term blocks. It allocates memory
// for the block array and initializes the pointer stack. It is passed the
// number of blocks to allocate and the size of the blocks.

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
// Get a block from the pool, this allocates a block. If the block pool is 
// short term, it gets a pointer from the circular array of pointers and 
// advances the index into the array. If the block pool is long term, it 
// pops a pointer from the pointer stack.

void* BlockPool::get()
{
   // If this pool is short term
   if (mBlockPoolType == BlockPoolType_ShortTerm)
   {
      // Get a block from the circular pointer array
      return mShortTermPointerCircular.get();
   }
   // Else if this pool is long term
   else if (mBlockPoolType == BlockPoolType_LongTerm)
   {
      // Get a block from the pointer stack
      return mLongTermPointerStack.pop();
   }
   // Else error
   else
   {
      return 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block. If the block pool
// is short term, it does nothing. If the block pool is long term, it pushes
// the pointer back onto the pointer stack.

void BlockPool::put(void* aBlockPointer)
{
   // If this pool is short term
   if (mBlockPoolType == BlockPoolType_ShortTerm)
   {
      //Do nothing, the block is simply reused
   }
   // Else if this pool is long term
   else if (mBlockPoolType == BlockPoolType_LongTerm)
   {
      // Push the block back onto the stack
      mLongTermPointerStack.push(aBlockPointer);
   }
}
}//namespace
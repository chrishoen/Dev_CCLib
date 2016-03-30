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

#include "ccMemLongTermBlockPool.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

LongTermBlockPool::LongTermBlockPool()
{
}

LongTermBlockPool::~LongTermBlockPool()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the block pool for long term blocks. It allocates memory
// for the block array and initializes the index stack. It is passed the
// number of blocks to allocate and the size of the blocks. Memory for one
// dummy block is allocated because index zero is reserved to indicate a
// null block.
//
// For aAllocate==10 blocks will range 0,1,2,3,4,5,6,7,8,9,10
// An index of zero is reserved for null index, so block 0 is unused.
// So usable blocks will range 1,2,3,4,5,6,7,8,9,10
//
// An index stack is used to manage free list access to the blocks
// The stack is initialized for a free list by pushing indices onto it.
// For aAllocate==10 this will push 10,9,8,7,6,5,4,3,2,1

void LongTermBlockPool::initialize(int aNumBlocks,int aBlockSize,int aMemPoolIndex)
{
   // Allocate memory for the block array.
   // For aNumBlocks==10 blocks will range 0,1,2,3,4,5,6,7,8,9,10
   // An index of zero is reserved for null index, so block 0 is unused.
   // So usable blocks will range 1,2,3,4,5,6,7,8,9,10
   BaseClass::initialize(aNumBlocks + 1,aBlockSize,aMemPoolIndex);

   // Initialize the pointer stack
   mIndexStack.initialize(aNumBlocks);

   // Push the indices of the blocks in the array onto the index stack.
   // For aAllocate==10 this will push 10,9,8,7,6,5,4,3,2,1
   for (int i = aNumBlocks; i >= 1; i--)
   {
      mIndexStack.push(i);
   }
}

// Deallocate memory for the block array.
void LongTermBlockPool::finalize()
{
   BaseClass::finalize();
   mIndexStack.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, this allocates a block. If the block pool is 
// short term, it gets a pointer from the circular array of pointers and 
// advances the index into the array. If the block pool is long term, it 
// pops a pointer from the pointer stack.

HasMemHandle* LongTermBlockPool::get()
{
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block. If the block pool
// is short term, it does nothing. If the block pool is long term, it pushes
// the pointer back onto the pointer stack.

void LongTermBlockPool::put(HasMemHandle* aBlockPointer)
{
}


}//namespace
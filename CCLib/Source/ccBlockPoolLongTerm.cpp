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

#include "ccBlockPoolLongTerm.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockPoolLongTerm::BlockPoolLongTerm()
{
}

BlockPoolLongTerm::~BlockPoolLongTerm()
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
// For aNumBlocks==10 blocks will range 0,1,2,3,4,5,6,7,8,9,10
// An index of zero is reserved for null index, so block 0 is unused.
// So usable blocks will range 1,2,3,4,5,6,7,8,9,10
//
// An index stack is used to manage free list access to the blocks
// The stack is initialized for a free list by pushing indices onto it.
// For aAllocate==10 this will push 10,9,8,7,6,5,4,3,2,1
//
// When a block is allocated, an index is popped off of the stack.
// When a block is deallocated, its index is pushed back onto the stack.
//

void BlockPoolLongTerm::initialize(int aNumBlocks,int aBlockSize,int aPoolIndex)
{
   // Allocate memory for the block array.
   // For aNumBlocks==10 blocks will range 0,1,2,3,4,5,6,7,8,9,10
   // An index of zero is reserved for null index, so block 0 is unused.
   // So usable blocks will range 1,2,3,4,5,6,7,8,9,10
   BaseClass::initialize(aNumBlocks + 1,aBlockSize,aPoolIndex);

   // Initialize the pointer stack
   mBlockIndexStack.initialize(aNumBlocks);

   // Push the indices of the blocks in the array onto the index stack.
   // For aAllocate==10 this will push 10,9,8,7,6,5,4,3,2,1
   for (int i = aNumBlocks; i >= 1; i--)
   {
      mBlockIndexStack.push(i);
   }
}

// Deallocate memory for the block array.
void BlockPoolLongTerm::finalize()
{
   BaseClass::finalize();
   mBlockIndexStack.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, this allocates a block. If the block pool is 
// short term, it gets a pointer from the circular array of pointers and 
// advances the index into the array. If the block pool is long term, it 
// pops a pointer from the pointer stack.

void BlockPoolLongTerm::allocate(void** aBlockPointer,BlockHandle* aBlockHandle)
{
   // Pop a block index from the index stack, as a free list.
   int tBlockIndex = mBlockIndexStack.pop();
    
   // Guard for stack empty.
   if (tBlockIndex == 0)
   {
      printf("BlockPoolLongTerm STACK EMPTY %d\n",BaseClass::mPoolIndex);
      return;
   }

   // Return a pointer to the block at that index.
   if (aBlockPointer)
   {
      *aBlockPointer = mBlocks.block(tBlockIndex);
   }

   // Return the memory handle for the block.
   if (aBlockHandle)
   {
      aBlockHandle->set(BaseClass::mPoolIndex, tBlockIndex);
//    printf("BlockPoolLongTerm::allocate %d %d\n",aBlockHandle->mPoolIndex,aBlockHandle->mBlockIndex);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block. If the block pool
// is short term, it does nothing. If the block pool is long term, it pushes
// the pointer back onto the pointer stack.

void BlockPoolLongTerm::deallocate(BlockHandle aBlockHandle)
{
   // Push the block index back onto the stack
   mBlockIndexStack.push(aBlockHandle.mBlockIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a block, given its memory handle.

void* BlockPoolLongTerm::getBlockPtr(BlockHandle aBlockHandle)
{
   return mBlocks.block(aBlockHandle.mBlockIndex);
}

}//namespace
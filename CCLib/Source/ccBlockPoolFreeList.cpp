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

#include "ccBlockPoolFreeList.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockPoolFreeList::BlockPoolFreeList()
{
}

BlockPoolFreeList::~BlockPoolFreeList()
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
// For aNumBlocks==10 blocks will range 0,1,2,3,4,5,6,7,8,9
// A block index of cInvalid indicates an invalid block.
//
// An index stack is used to manage free list access to the blocks
// The stack is initialized for a free list by pushing indices onto it.
// For aAllocate==10 this will push 9,8,7,6,5,4,3,2,1,0
//
// When a block is allocated, an index is popped off of the stack.
// When a block is deallocated, its index is pushed back onto the stack.
//

void BlockPoolFreeList::initialize(BlockPoolParms* aParms)
{
   // Allocate memory for the block array.
   // For aNumBlocks==10 blocks will range 0,1,2,3,4,5,6,7,8,9
   BaseClass::initialize(aParms);

   // Initialize the index stack.
   // For aAllocate==10 this will push 9,8,7,6,5,4,3,2,1,0
   mBlockIndexStack.initialize(aParms->mNumBlocks);
}

// Deallocate memory for the block array.
void BlockPoolFreeList::finalize()
{
   BaseClass::finalize();
   mBlockIndexStack.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, this allocates a block.

void BlockPoolFreeList::allocate(void** aBlockPointer,BlockHandle* aBlockHandle)
{
   int tBlockIndex = 0;
      
   // Pop a block index from the index stack, as a free list.
   if(!mBlockIndexStack.pop(&tBlockIndex))
   {
      // If empty stack return.
      *aBlockPointer = 0;
      aBlockHandle->setNull();
      printf("BlockPoolFreeList STACK EMPTY %d\n",BaseClass::mPoolIndex);
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
//    printf("BlockPoolFreeList::allocate %d %d\n",aBlockHandle->mPoolIndex,aBlockHandle->mBlockIndex);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block. If the block pool
// is short term, it does nothing. If the block pool is long term, it pushes
// the pointer back onto the pointer stack.

void BlockPoolFreeList::deallocate(BlockHandle aBlockHandle)
{
   // Push the block index back onto the stack
   mBlockIndexStack.push(aBlockHandle.mBlockIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a block, given its memory handle.

void* BlockPoolFreeList::getBlockPtr(BlockHandle aBlockHandle)
{
   return mBlocks.block(aBlockHandle.mBlockIndex);
}

}//namespace
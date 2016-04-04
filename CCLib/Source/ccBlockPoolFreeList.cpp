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
   // All null.
   mExternalMemoryFlag = false;
   mMemory = 0;
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
// For aAllocate==10 this will push 0,1,2,3,4,5,6,7,8,9
//
// When a block is allocated, an index is popped off of the stack.
// When a block is deallocated, its index is pushed back onto the stack.
//

void BlockPoolFreeList::initialize(BlockPoolParms* aParms)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize memory.

   // Deallocate memory, if any exists.
   finalize();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aParms->mMemory == 0)
   {
      mMemory = malloc(BlockPoolFreeList::getMemorySize(aParms));
      mExternalMemoryFlag = false;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aParms->mMemory;
      mExternalMemoryFlag = true;
   }

   // Calculate memory sizes.
   int tBaseClassSize = BlockPoolBase::getMemorySize(aParms);
   int tStackSize     = FreeListIndexStack::getMemorySize(aParms->mNumBlocks);

   // Calculate memory addresses.
   char* tBaseClassMemory = (char*)mMemory;
   char* tStackMemory = tBaseClassMemory + tBaseClassSize;

   // Initialize the base class variables.
   BaseClass::initializeBase(aParms,tBaseClassMemory);

   // Initialize the index stack.
   // For aAllocate==10 this will push 0,1,2,3,4,5,6,7,8,9
   mBlockIndexStack.initialize(aParms->mNumBlocks,tStackMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Deallocate memory for the block array.

void BlockPoolFreeList::finalize()
{
   mBlockIndexStack.finalize();
   BaseClass::finalizeBase();

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

int BlockPoolFreeList::getMemorySize(BlockPoolParms* aParms)
{
   int tBaseClassSize = BlockPoolBase::getMemorySize(aParms);
   int tStackSize     = FreeListIndexStack::getMemorySize(aParms->mNumBlocks);
   int tMemorySize = tBaseClassSize + tStackSize;
   return tMemorySize;
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
      printf("BlockPoolFreeList STACK EMPTY %d\n",BaseClass::mParms->mPoolIndex);
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
      aBlockHandle->set(BaseClass::mParms->mPoolIndex, tBlockIndex);
//    printf("BlockPoolFreeList::allocate %d %d\n",aBlockHandle->mPoolIndex,aBlockHandle->mBlockIndex);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block.

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
   // Return the address of the block within the block array.
   return mBlocks.block(aBlockHandle.mBlockIndex);
}

}//namespace
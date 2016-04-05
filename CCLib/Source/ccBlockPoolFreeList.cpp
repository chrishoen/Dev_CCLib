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

#include "ccBlockPoolIndexStack.h"
#include "ccBlockPoolLFIndexStack.h"
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
   mFreeMemoryFlag = false;
   mMemory = 0;
   mBlockIndexStack = 0;
}

BlockPoolFreeList::~BlockPoolFreeList()
{
   return;
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
      mMemory = malloc(BlockPoolFreeList::getMemorySize(aParms)+ 1024);
      mFreeMemoryFlag = true;
      printf("BlockPoolFreeList::malloc %p\n",mMemory);
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aParms->mMemory;
      mFreeMemoryFlag = false;
   }

   // Calculate memory sizes.
   int tBaseClassSize = BlockPoolBase::getMemorySize(aParms);

   int tStackSize = 0;
   switch (aParms->mBlockPoolType)
   {
   case cBlockPoolType_FreeList   : tStackSize = BlockPoolIndexStack::getMemorySize(aParms->mNumBlocks); break;
   case cBlockPoolType_LFFreeList : tStackSize = BlockPoolLFIndexStack::getMemorySize(aParms->mNumBlocks); break;
   }

   // Calculate memory addresses.
   char* tBaseClassMemory = (char*)mMemory;
   char* tStackMemory = tBaseClassMemory + tBaseClassSize;

   // Initialize the base class variables.
   BaseClass::initializeBase(aParms,tBaseClassMemory);

   // Create the index stack.
   switch (aParms->mBlockPoolType)
   {
   case cBlockPoolType_FreeList   : mBlockIndexStack = new BlockPoolIndexStack; break;
   case cBlockPoolType_LFFreeList : mBlockIndexStack = new BlockPoolLFIndexStack; break;
   }

   // Initialize the index stack.
   mBlockIndexStack->initialize(aParms->mNumBlocks,tStackMemory);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Deallocate memory for the block array.

void BlockPoolFreeList::finalize()
{
   BaseClass::finalizeBase();

   if (mBlockIndexStack)
   {
      mBlockIndexStack->finalize();
      delete mBlockIndexStack;
      mBlockIndexStack = 0;
   }

   if (mFreeMemoryFlag)
   {
      if (mMemory)
      {
         printf("BlockPoolFreeList::free   %p\n",mMemory);
         free(mMemory);
      }
   }
   mMemory = 0;
   mFreeMemoryFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockPoolFreeList::getMemorySize(BlockPoolParms* aParms)
{
   int tBaseClassSize = BlockPoolBase::getMemorySize(aParms);

   int tStackSize     = 0;
   switch (aParms->mBlockPoolType)
   {
   case cBlockPoolType_FreeList   : tStackSize = BlockPoolIndexStack::getMemorySize(aParms->mNumBlocks); break;
   case cBlockPoolType_LFFreeList : tStackSize = BlockPoolLFIndexStack::getMemorySize(aParms->mNumBlocks); break;
   }

   int tMemorySize = tBaseClassSize + tStackSize;
   return tMemorySize;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Size, the number of blocks that are available to be allocated.

int BlockPoolFreeList::size()
{ 
   if (mBlockIndexStack==0) return 0;
   return mBlockIndexStack->size();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, this allocates a block.

void BlockPoolFreeList::allocate(void** aBlockPointer,BlockHandle* aBlockHandle)
{
   int tBlockIndex = 0;
      
   // Pop a block index from the index stack, as a free list.
   if(!mBlockIndexStack->pop(&tBlockIndex))
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
   mBlockIndexStack->push(aBlockHandle.mBlockIndex);
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
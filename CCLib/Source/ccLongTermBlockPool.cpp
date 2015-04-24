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

#include "ccLongTermBlockPool.h"

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

void LongTermBlockPool::initialize(int aAllocate, int aBlockSize)
{
   // Allocate memory for the block array
   mBlocks.initialize(aAllocate,aBlockSize);

   // Initialize the pointer stack
   mPointerStack.initialize(aAllocate);

   // Push the addresses of the blocks in the array onto the pointer stack.
   for (int i = 0; i < aAllocate; i++)
   {
      mPointerStack.push(mBlocks.e(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, this allocates a block. It pops a pointer
// from the pointer stack.

void* LongTermBlockPool::get()
{
   return mPointerStack.pop();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block. It pushes a 
// pointer onto the pointer stack.

void LongTermBlockPool::put(void* aBlockPointer)
{
   mPointerStack.push(aBlockPointer);
}
}//namespace
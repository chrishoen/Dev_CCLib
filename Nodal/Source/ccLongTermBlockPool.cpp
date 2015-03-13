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

LongTermBlockPool::LongTermBlockPool()
{
}

LongTermBlockPool::~LongTermBlockPool()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Store member variables and dynamically allocate memory for the block array.

void LongTermBlockPool::initialize(int aAllocate, int aBlockSize)
{
   // Allocate memory for the block array
   mBlocks.initialize(aAllocate,aBlockSize);

   // Push the addresses of the blocks in the array onto the pointer stack.
   for (int i = 0; i < aAllocate; i++)
   {
      mPointerStack.push(mBlocks.e(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, allocate

void* LongTermBlockPool::get()
{
   return mPointerStack.pop();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, free
void LongTermBlockPool::put(void* aBlockPointer)
{
   mPointerStack.push(aBlockPointer);
}
}//namespace
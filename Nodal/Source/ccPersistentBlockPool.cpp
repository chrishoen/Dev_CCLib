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

#include "ccPersistentBlockPool.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

PersistentBlockPool::PersistentBlockPool()
{
}

PersistentBlockPool::~PersistentBlockPool()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Store member variables and dynamically allocate memory for the block array.

void PersistentBlockPool::initialize(int aAllocate, int aBlockSize)
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

void* PersistentBlockPool::get()
{
   return mPointerStack.pop();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, free
void PersistentBlockPool::put(void* aBlockPointer)
{
   mPointerStack.push(aBlockPointer);
}
}//namespace
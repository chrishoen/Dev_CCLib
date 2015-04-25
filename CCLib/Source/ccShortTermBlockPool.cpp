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

#include "ccShortTermBlockPool.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

ShortTermBlockPool::ShortTermBlockPool()
{
   printf("ShortTermBlockPool::ShortTermBlockPool\n");
}

ShortTermBlockPool::~ShortTermBlockPool()
{
   printf("ShortTermBlockPool::~ShortTermBlockPool\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Store member variables and dynamically allocate memory for the block array.

void ShortTermBlockPool::initialize(int aAllocate, int aBlockSize)
{
   // Allocate memory for the block array
   mBlocks.initialize(aAllocate,aBlockSize);

   // Initialize the pointer circular array
   mPointerCircular.initialize(aAllocate);

   // Push the addresses of the blocks in the array onto the pointer stack.
   for (int i = 0; i < aAllocate; i++)
   {
      mPointerCircular.put(mBlocks.e(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, allocate

void* ShortTermBlockPool::get()
{
   return mPointerCircular.get();
}

}//namespace
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
// Allocate memory for the block array. It is passed the number of blocks to
// allocate, the size of the block body, and the memory pool index for the
// block aarray.

void LongTermBlockPool::initialize(int aNumBlocks,int aBlockBodySize)
{}

// Deallocate memory for the block array.
void LongTermBlockPool::finalize()
{
   BaseClass::finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, this allocates a block. If the block pool is 
// short term, it gets a pointer from the circular array of pointers and 
// advances the index into the array. If the block pool is long term, it 
// pops a pointer from the pointer stack.

void* LongTermBlockPool::get()
{
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block. If the block pool
// is short term, it does nothing. If the block pool is long term, it pushes
// the pointer back onto the pointer stack.

void LongTermBlockPool::put(void* aBlockPointer)
{
}


}//namespace
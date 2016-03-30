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

#include "ccMemBaseBlockPool.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

MemBaseBlockPool::MemBaseBlockPool()
{
   // All null.
   mNumBlocks=0;
   mBlockSize=0;
   mMemPoolIndex=0;
   mCount=0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate memory for the block array. It is passed the number of blocks to
// allocate, the size of the block body, and the memory pool index for the
// block aarray.

void MemBaseBlockPool::initialize(int aNumBlocks, int aBlockSize, int aMemPoolIndex)
{
   // Store.
   mNumBlocks    = aNumBlocks; 
   mBlockSize     = aBlockSize; 
   mMemPoolIndex = aMemPoolIndex;
   mCount=0;
   // Initialize.
   mBlocks.initialize(aNumBlocks,aBlockSize,aMemPoolIndex);
}

   // Deallocate memory for the block array.
void MemBaseBlockPool::finalize()
{
   mBlocks.finalize();
   mCount=0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers

void MemBaseBlockPool::show()
{
   printf("MemBlockPool Count %d\n", mCount);
}






}//namespace
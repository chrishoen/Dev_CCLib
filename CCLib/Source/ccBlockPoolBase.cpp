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

#include "ccBlockPoolBase.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockPoolBase::BlockPoolBase()
{
   // All null.
   mNumBlocks=0;
   mBlockSize=0;
   mPoolIndex=0;
   mCount=0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate memory for the block array. It is passed the number of blocks to
// allocate, the size of the block body, and the memory pool index for the
// block aarray.

void BlockPoolBase::initialize(BlockPoolParms* aParms)
{
   // Store parameters.
   mNumBlocks = aParms->mNumBlocks; 
   mBlockSize = aParms->mBlockSize; 
   mPoolIndex = aParms->mPoolIndex;
   mCount=0;
   // Initialize the block box array.
   mBlocks.initialize(mNumBlocks,mBlockSize,mPoolIndex);
}

   // Deallocate memory for the block array.
void BlockPoolBase::finalize()
{
   mBlocks.finalize();
   mCount=0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers

void BlockPoolBase::show()
{
   printf("MemBlockPool size %d\n", size());
}






}//namespace
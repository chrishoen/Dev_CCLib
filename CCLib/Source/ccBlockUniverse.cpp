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

#include "ccBlockUniverse.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockUniverse::BlockUniverse()
{
}

BlockUniverse::~BlockUniverse()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Store member variables and dynamically allocate memory for the block array.

void BlockUniverse::initialize(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks,
      int aBlockSize)
{
   // Initialize the short term block pool
   mShortTermBlockPool.initialize(aAllocateShortTermBlocks,aBlockSize);

   // Initialize the long term block pool
   mLongTermBlockPool.initialize(aAllocateLongTermBlocks,aBlockSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void BlockUniverse::show(char* aLabel)
{
   printf("%s %d %d\n", 
      aLabel, 
      mLongTermBlockPool.mPointerStack.mIndex,
      mShortTermBlockPool.mPointerCircular.mGetIndex);
}
}//namespace
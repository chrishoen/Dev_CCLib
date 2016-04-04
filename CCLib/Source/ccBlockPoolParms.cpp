/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>

#include "cc_functions.h"
#include "ccBlockPoolCentral.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Block pool parameters. These are passed to the create block pool call.

BlockPoolParms::BlockPoolParms()
{
   reset();
}

void BlockPoolParms::reset()
{
   // All null
   mValidFlag = false;
   mPoolIndex = 0;
   mNumBlocks = 0;
   mBlockSize = 0;
   mMemory    = 0;

   // Defaults
   mBlockPoolType = cBlockPoolType_FreeList;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockPoolParms::getMemorySize()
{
   return cc_round_upto16(sizeof(BlockPoolParms));
}

} //namespace


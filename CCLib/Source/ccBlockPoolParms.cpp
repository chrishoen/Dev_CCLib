/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "ccBlockPoolBase.h"
#include "ccBlockPoolFreeList.h"

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

   // Defaults
   mBlockPoolType = cBlockPoolType_FreeList;
}

} //namespace


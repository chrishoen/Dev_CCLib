#pragma once

/*==============================================================================
Block header class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "ccBlockPool.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a header that is placed at the start of every block that is 
// allocated from the block array.

typedef struct BlockHeader
{
   // Unique memory handle for a block.
   BlockHandle mBlockHandle;
} BlockHeader;

// This structure must not take up more than sixteen bytes.
static const int cBlockHeaderSize = 16;

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

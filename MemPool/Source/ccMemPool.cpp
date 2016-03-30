/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "ccMemBaseBlockPool.h"
#include "ccMemLongTermBlockPool.h"

#include "ccMemPool.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Regional variables

static MemBaseBlockPool* mBlockPool=0;

//****************************************************************************
//****************************************************************************
//****************************************************************************

void resetMemPool()
{
   mBlockPool = new LongTermBlockPool;
}

void addBlockPool(int aNumBlocks, int aBlockSize, int aMemPoolIndex)
{
   mBlockPool->initialize(aNumBlocks,aBlockSize,aMemPoolIndex);
}

void initializeMemPool()
{}

void finalizeMemPool()
{}

//****************************************************************************
//****************************************************************************
//****************************************************************************

HasMemHandle* getMemPoolBlock(int aMemPoolIndex)
{
   return mBlockPool->get();
}

void putMemPoolBlock(int aMemPoolIndex,HasMemHandle* aBlockPointer)
{
   mBlockPool->put(aBlockPointer);
}

void showMemPool(int aMemPoolIndex)
{
   mBlockPool->show();
}

} //namespace


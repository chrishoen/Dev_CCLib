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

static const int cMaxNumBlockPools=100;
static MemBaseBlockPool* mBlockPool[cMaxNumBlockPools];

//****************************************************************************
//****************************************************************************
//****************************************************************************

void resetMemPool()
{
   for (int i = 0; i < cMaxNumBlockPools; i++)
   {
      mBlockPool[i]=0;
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void addBlockPool(int aNumBlocks, int aBlockSize, int aMemPoolIndex)
{
   // Guard
   if (aMemPoolIndex<1) return;
   if (aMemPoolIndex>=cMaxNumBlockPools) return;
   if (mBlockPool[aMemPoolIndex])
   {
      printf("ERROR BlockPool already exists %d", aMemPoolIndex);
      return;
   }
   // Create and initialize block pool
   mBlockPool[aMemPoolIndex] = new LongTermBlockPool;
   mBlockPool[aMemPoolIndex]->initialize(aNumBlocks,aBlockSize,aMemPoolIndex);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void initializeMemPool()
{
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void finalizeMemPool()
{
   for (int i = 0; i < cMaxNumBlockPools; i++)
   {
      if (mBlockPool[i])
      {
         mBlockPool[i]->finalize();
         delete mBlockPool[i];
      }
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void allocateMemPoolBlock(int aMemPoolIndex,void** aBlockPointer,MemHandle* aMemHandle)
{
   // Guard
   if (aMemPoolIndex<1) return;
   if (aMemPoolIndex>=cMaxNumBlockPools) return;
   if (mBlockPool[aMemPoolIndex]==0)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aMemPoolIndex);
      return;
   }
   // Get block from specific pool.
   mBlockPool[aMemPoolIndex]->allocate(aBlockPointer,aMemHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void deallocateMemPoolBlock(MemHandle aMemHandle)
{
// printf("deallocateMemPoolBlock %d %d\n", aMemHandle.mPoolIndex,aMemHandle.mBlockIndex);
   mBlockPool[aMemHandle.mPoolIndex]->deallocate(aMemHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void showMemPool(int aMemPoolIndex)
{
   // Guard
   if (aMemPoolIndex<1) return;
   if (aMemPoolIndex>=cMaxNumBlockPools) return;
   if (mBlockPool[aMemPoolIndex]==0)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aMemPoolIndex);
      return;
   }
   mBlockPool[aMemPoolIndex]->show();
}

} //namespace


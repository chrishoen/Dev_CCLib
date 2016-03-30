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
#include "ccBlockPoolLongTerm.h"

#include "ccBlockPool.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Regional variables

static const int cMaxNumBlockPools=100;
static BlockPoolBase* mBlockPool[cMaxNumBlockPools];

//****************************************************************************
//****************************************************************************
//****************************************************************************

void resetBlockPool()
{
   for (int i = 0; i < cMaxNumBlockPools; i++)
   {
      mBlockPool[i]=0;
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void addBlockPool(int aNumBlocks, int aBlockSize, int aPoolIndex)
{
   // Guard
   if (aPoolIndex<1) return;
   if (aPoolIndex>=cMaxNumBlockPools) return;
   if (mBlockPool[aPoolIndex])
   {
      printf("ERROR BlockPool already exists %d", aPoolIndex);
      return;
   }
   // Create and initialize block pool
   mBlockPool[aPoolIndex] = new BlockPoolLongTerm;
   mBlockPool[aPoolIndex]->initialize(aNumBlocks,aBlockSize,aPoolIndex);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void initializeBlockPool()
{
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void finalizeBlockPool()
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

void allocateBlockPoolBlock(int aPoolIndex,void** aBlockPointer,BlockHandle* aBlockHandle)
{
   // Guard
   if (aPoolIndex<1) return;
   if (aPoolIndex>=cMaxNumBlockPools) return;
   if (mBlockPool[aPoolIndex]==0)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aPoolIndex);
      return;
   }
   // Get block from specific pool.
   mBlockPool[aPoolIndex]->allocate(aBlockPointer,aBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void deallocateBlockPoolBlock(BlockHandle aBlockHandle)
{
// printf("deallocateBlockPoolBlock %d %d\n", aBlockHandle.mPoolIndex,aBlockHandle.mBlockIndex);
   mBlockPool[aBlockHandle.mPoolIndex]->deallocate(aBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void* getBlockPoolBlockPtr(BlockHandle aBlockHandle)
{
   return mBlockPool[aBlockHandle.mPoolIndex]->getBlockPtr(aBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void showBlockPool(int aPoolIndex)
{
   // Guard
   if (aPoolIndex<1) return;
   if (aPoolIndex>=cMaxNumBlockPools) return;
   if (mBlockPool[aPoolIndex]==0)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aPoolIndex);
      return;
   }
   mBlockPool[aPoolIndex]->show();
}

} //namespace


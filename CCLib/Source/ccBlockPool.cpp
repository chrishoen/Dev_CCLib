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

#include "ccBlockPool.h"

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
   mPoolIndex = 0;
   mBlockPoolType = 0;
   mNumBlocks = 0;
   mBlockSize = 0;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Regional variables.

static const int cMaxNumBlockPools=100;
static BlockPoolBase* mBlockPool[cMaxNumBlockPools];

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This initializes the block pool facility. It is called at program
// initialization, before any block pools are created.

void initializeBlockPoolFacility()
{
   for (int i = 0; i < cMaxNumBlockPools; i++)
   {
      mBlockPool[i]=0;
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This creates a block pool and places a pointer to it into the block
// pool array. It is passed a set of parameters.

void createBlockPool(BlockPoolParms* aParms)
{
   // Guard
   if (aParms->mPoolIndex<1) return;
   if (aParms->mPoolIndex>=cMaxNumBlockPools) return;
   if (mBlockPool[aParms->mPoolIndex])
   {
      printf("ERROR BlockPool already exists %d", aParms->mPoolIndex);
      return;
   }
   // Create and initialize block pool
   mBlockPool[aParms->mPoolIndex] = new BlockPoolFreeList;
   mBlockPool[aParms->mPoolIndex]->initialize(aParms->mNumBlocks,aParms->mBlockSize,aParms->mPoolIndex);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This finalizes the block pool facility. It is called at program
// termination. It destroys all block pools that were created.

void finalizeBlockPoolFacility()
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
// This allocates a block from a block pool. It is passes a pool index and 
// it returns a pointer to the block and a handle for the block.

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
// This deallocates a block from a block pool. It is passed a handle to the
// block, which contains the pool index of the block pool to deallocate the 
// block from.

void deallocateBlockPoolBlock(BlockHandle aBlockHandle)
{
// printf("deallocateBlockPoolBlock %d %d\n", aBlockHandle.mPoolIndex,aBlockHandle.mBlockIndex);
   mBlockPool[aBlockHandle.mPoolIndex]->deallocate(aBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This returns a pointer to a block, given a block handle.

void* getBlockPoolBlockPtr(BlockHandle aBlockHandle)
{
   // Guard
   if (aBlockHandle.mPoolIndex==0)  return 0;
   if (aBlockHandle.mBlockIndex==0) return 0;
   // Return pointer to block.
   return mBlockPool[aBlockHandle.mPoolIndex]->getBlockPtr(aBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This shows block pool info.

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


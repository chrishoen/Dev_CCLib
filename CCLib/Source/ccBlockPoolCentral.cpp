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

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Regional variables.

static const int cMaxNumBlockPools=100;
static BlockPoolBase* mBlockPool[cMaxNumBlockPools];
static BlockPoolParms mBlockPoolParms[cMaxNumBlockPools];

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Initialize the block pool facility. It is called at program
// initialization, before any block pools are created and used.

void initializeBlockPoolCentral()
{
   for (int i = 0; i < cMaxNumBlockPools; i++)
   {
      mBlockPool[i]=0;
      mBlockPoolParms[i].reset();
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Finalize the block pool facility. It is called at program
// termination. It destroys all block pools that were created.

void finalizeBlockPoolCentral()
{
   // For each block pool that was created
   for (int i = 0; i < cMaxNumBlockPools; i++)
   {
      if (mBlockPoolParms[i].mValidFlag)
      {
         // Finalize and delete the block pool.
         mBlockPool[i]->finalize();
         delete mBlockPool[i];
         mBlockPool[i]=0;
         // Mark it invalid.
         mBlockPoolParms[i].mValidFlag = false;
      }
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Create a block pool and place a pointer to it into the block
// pool array. It is passed a set of parameters.

void createBlockPool(BlockPoolParms* aParms)
{
   // Temp
   int tPoolIndex = aParms->mPoolIndex;

   // Guard.
   if (tPoolIndex<1) return;
   if (tPoolIndex>=cMaxNumBlockPools) return;
   if (mBlockPool[tPoolIndex])
   {
      printf("ERROR BlockPool already exists %d", aParms->mPoolIndex);
      return;
   }

   // Create and initialize the block pool.
   switch (aParms->mBlockPoolType)
   {
      // Create and initialize the block pool.
      case cBlockPoolType_FreeList :
      case cBlockPoolType_LFFreeList :
      {
         mBlockPool[tPoolIndex] = new BlockPoolFreeList;
         mBlockPool[tPoolIndex]->initialize(aParms);
      }
      break;
      // Error.
      default :
      {
         printf("ERROR BlockPoolType BAD", aParms->mBlockPoolType);
         return;
      }
      break;
   }

   // Mark it valid.
   aParms->mValidFlag = true;

   // Store parameters.
   mBlockPoolParms[tPoolIndex] = *aParms;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Test code.

void testBlockPool(int aPoolIndex)
{
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Allocate a block from a block pool. It is passes a pool index and 
// it returns a pointer to the block and a handle for the block.
// It returns true if successful, false if the block pool is empty.

bool allocateBlockPoolBlock(int aPoolIndex,void** aBlockPointer,BlockHandle* aBlockHandle)
{
   // Guard
   if (aPoolIndex==0) return false;
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aPoolIndex);
      return false;
   }
   // Get block from specific pool.
   return mBlockPool[aPoolIndex]->allocate(aBlockPointer,aBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Deallocates a block from a block pool. It is passed a handle to the
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
// Get a pointer to a block, given a block handle.

void* getBlockPoolBlockPtr(BlockHandle aBlockHandle)
{
   // Guard
   if (aBlockHandle.isNull())  return 0;
   // Return pointer to block.
   return mBlockPool[aBlockHandle.mPoolIndex]->getBlockPtr(aBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Show block pool info.

void showBlockPool(int aPoolIndex)
{
   // Guard
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aPoolIndex);
      return;
   }
   mBlockPool[aPoolIndex]->show();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Get the size of a block pool.

int getBlockPoolSize(int aPoolIndex)
{
   // Guard
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aPoolIndex);
      return 0;
   }
   return mBlockPool[aPoolIndex]->size();
}

} //namespace


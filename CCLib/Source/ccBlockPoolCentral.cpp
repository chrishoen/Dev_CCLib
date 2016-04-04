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
// This initializes the block pool facility. It is called at program
// initialization, before any block pools are created.

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
// This creates a block pool and places a pointer to it into the block
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
// This finalizes the block pool facility. It is called at program
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
// This shows block pool info.

void testBlockPool(int aPoolIndex)
{
   printf("testBlockPool BEGIN %d\n", aPoolIndex);
   // Guard
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aPoolIndex);
      return;
   }
   mBlockPool[aPoolIndex]->show();
   mBlockPool[aPoolIndex]->finalize();
   printf("testBlockPool END   %d\n", aPoolIndex);
   delete mBlockPool[aPoolIndex];
   return;

   mBlockPool[aPoolIndex]=0;
   mBlockPoolParms[aPoolIndex].mValidFlag = false;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This allocates a block from a block pool. It is passes a pool index and 
// it returns a pointer to the block and a handle for the block.

void allocateBlockPoolBlock(int aPoolIndex,void** aBlockPointer,BlockHandle* aBlockHandle)
{
   // Guard
   if (aPoolIndex==0) return;
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
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
   if (aBlockHandle.isNull())  return 0;
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
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
   {
      printf("ERROR BlockPool doesn't exists %d\n", aPoolIndex);
      return;
   }
   mBlockPool[aPoolIndex]->show();
}

} //namespace


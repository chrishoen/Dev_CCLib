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
#include "ccBlockPoolShortTerm.h"

#include "ccBlockPoolCentral.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Regional variables.

static const int cMaxNumBlockPools=100;
static BlockPoolBase* mBlockPool[cMaxNumBlockPools];
static BlockPoolParms mBlockPoolParms[cMaxNumBlockPools];

//******************************************************************************
//******************************************************************************
//******************************************************************************
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create and initialize a block pool and place a pointer to it into the
// block pool array. It is passed a set of parameters. Store these parameters
// in persistent storage. They will be used throughout the lifetime of the 
// block pool.

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

   // Store parameters. These are used throughout the lifetime of the block pool.
   mBlockPoolParms[tPoolIndex] = *aParms;
   // Range check parameters.
   mBlockPoolParms[tPoolIndex].makeConsistent();

   // Local pointer.
   BlockPoolParms* tParms = &mBlockPoolParms[tPoolIndex];

   // Block pool type lookup table.
   switch (aParms->mBlockPoolType)
   {
      // Create and initialize the block pool.
      case cBlockPoolType_FreeList :
      {
         mBlockPool[tPoolIndex] = new BlockPoolFreeList;
         mBlockPool[tPoolIndex]->initialize(tParms);
      }
      break;
      // Create and initialize the block pool.
      case cBlockPoolType_ShortTerm :
      {
         mBlockPool[tPoolIndex] = new BlockPoolShortTerm;
         mBlockPool[tPoolIndex]->initialize(tParms);
      }
      break;
      // Error.
      default :
      {
         printf("ERROR BlockPoolType BAD", tParms->mBlockPoolType);
         return;
      }
      break;
   }

   if (!tParms->mValidFlag)
   {
      printf("ERROR BlockPool Initialization FAIL", tParms->mBlockPoolType);
      return;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate a block from a block pool. It is passes a pool index and 
// it returns a pointer to the block and a handle for the block.
// It returns true if successful, false if the block pool is empty.

bool allocateBlockPoolBlock(int aPoolIndex,void** aBlockPointer,BlockHandle* aBlockHandle)
{
   // Guard
   if (aPoolIndex==0) return false;
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
   {
      printf("ERROR allocate BlockPool doesn't exist %d\n", aPoolIndex);
      return false;
   }
   // Get block from specific pool.
   bool tSuccess = mBlockPool[aPoolIndex]->allocate(aBlockPointer,aBlockHandle);

   // Check result.
   if (tSuccess) return true;
   if (!mBlockPoolParms[aPoolIndex].mNoThrowFlag)
   {
      printf("ERROR allocate BlockPool EMPTY %d\n", aPoolIndex);
      throw 101;
   }
   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Deallocate a block from a block pool. It is passed a handle to the
// block, which contains the pool index of the block pool to deallocate the 
// block from. This is used for intrusive blocks, those that contain a block
// handle member variable.

void deallocateBlockPoolBlock(BlockHandle aBlockHandle)
{
// printf("deallocateBlockPoolBlock %d %d\n", aBlockHandle.mPoolIndex,aBlockHandle.mBlockIndex);
   // Deallocate the block.
   mBlockPool[aBlockHandle.mPoolIndex]->deallocate(aBlockHandle);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Deallocate a block from a block pool. It is passed a pointer to the
// block. It uses the pointer to lookup the block handle, which contains 
// the pool index of the block pool to deallocate the block from. This is
// used for nonintrusive blocks, those that do not contain a block handle
// member variable

void deallocateBlockPoolBlock(void* aBlockPtr)
{
   //Guard.
   if (aBlockPtr==0) return;
   // Get the block handle.
   BlockHandle tBlockHandle = BlockBoxArray::getBlockHandle(aBlockPtr);
   //Guard.
   if (tBlockHandle==BlockHandle::nullH) return;
   // Deallocate the block.
   mBlockPool[tBlockHandle.mPoolIndex]->deallocate(tBlockHandle);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a pointer to a block, given a block handle.

void* getBlockPoolBlockPtr(BlockHandle aBlockHandle)
{
   // Guard
   if (aBlockHandle.isNull())  return 0;
#if 1
   // Calculate block address from stored parameters and block pool.handle
   BlockPoolParms* tParms = &mBlockPoolParms[aBlockHandle.mPoolIndex];
   char*  tBlockBox = &tParms->mBlockBoxPtr[tParms->mBlockBoxSize*aBlockHandle.mBlockIndex];
   char*  tBlock = tBlockBox + cBlockHeaderSize;
   // Return pointer to block.
   return tBlock;
#endif
   // Return pointer to block.
   return mBlockPool[aBlockHandle.mPoolIndex]->getBlockPtr(aBlockHandle);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the handle of a block, given its address.

BlockHandle getBlockPoolBlockHandle(void* aBlockPtr)
{
#if 1
   BlockHandle tBlockHandle;
   if (aBlockPtr==0) return tBlockHandle;

   char*  tBlock = (char*)aBlockPtr;
   BlockHeader* tHeader = (BlockHeader*)(tBlock - cBlockHeaderSize);

   tBlockHandle = tHeader->mBlockHandle;
   return tBlockHandle;
#endif
   return BlockBoxArray::getBlockHandle(aBlockPtr);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show block pool info.

void showBlockPool(int aPoolIndex)
{
   // Guard
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
   {
      printf("ERROR show BlockPool doesn't exist %d\n", aPoolIndex);
      return;
   }
   mBlockPool[aPoolIndex]->show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the size of a block pool.

int getBlockPoolSize(int aPoolIndex)
{
   // Guard
   if (!mBlockPoolParms[aPoolIndex].mValidFlag)
   {
      printf("ERROR size BlockPool doesn't exist %d\n", aPoolIndex);
      return 0;
   }
   return mBlockPool[aPoolIndex]->size();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return true if memory for a block is long term and false if it is short 
// term. If it is long term then allocated blocks must be deallocated. If it
// is short term then allocated blocks do not have to be deallocated, they
// are simply reused.

bool isBlockPoolMemoryLongTerm(BlockHandle aBlockHandle)
{
   // Block pool type lookup table.
   switch (mBlockPoolParms[aBlockHandle.mPoolIndex].mBlockPoolType)
   {
      // Create and initialize the block pool.
      case cBlockPoolType_FreeList   : return true;
      case cBlockPoolType_ShortTerm  : return false;
   }
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test code.

void testBlockPool(int aPoolIndex)
{
   BlockPoolParms* tParms = &mBlockPoolParms[aPoolIndex];

   printf("mBlockBoxPtr    %p\n", tParms->mBlockBoxPtr);
   printf("mBlockBoxSize   %d\n", tParms->mBlockBoxSize);
   printf("mBlockHeaderSize%d\n", tParms->mBlockHeaderSize);

   mBlockPool[aPoolIndex]->show();
}

} //namespace


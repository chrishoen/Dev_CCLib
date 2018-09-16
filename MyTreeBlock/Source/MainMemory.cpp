#include "stdafx.h"

#include "ccBlockPool.h"
#include "ccBlockPoolIndex.h"
#include "ccTreeNode.h"

#include "someBlockPoolIndex.h"
#include "someMyTreeBlock.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program memory.

void main_memory_initialize()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize block pools.

   // Initialize block pool central facility.
   CC::initializeBlockPoolCentral();

   // Block pool parameters.
   CC::BlockPoolParms tBlockPoolParms;

   // Create block pool.
   tBlockPoolParms.reset();
   tBlockPoolParms.mPoolIndex     = CC::cBlockPoolIndex_TreeNode;
   tBlockPoolParms.mBlockPoolType = CC::cBlockPoolType_FreeList;
   tBlockPoolParms.mNumBlocks     = 1000;
   tBlockPoolParms.mBlockSize     = sizeof(CC::TreeNode);
   CC::createBlockPool(&tBlockPoolParms);

   // Create block pool.
   tBlockPoolParms.reset();
   tBlockPoolParms.mPoolIndex     = Some::cBlockPoolIndex_MyTreeBlock;
   tBlockPoolParms.mBlockPoolType = CC::cBlockPoolType_Faster;
   tBlockPoolParms.mNumBlocks     = 1000;
   tBlockPoolParms.mBlockSize     = sizeof(Some::MyTreeBlock);
   CC::createBlockPool(&tBlockPoolParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program memory.

void main_memory_finalize()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize block pools.

   // Finalize block pool central facility.
   // This destroys all created block pools.
   CC::finalizeBlockPoolCentral();
}



#include "stdafx.h"

#include "GSettings.h"
#include "ccSharedMemory.h"
#include "ccSharedSynch.h"
#include "ccBlockPool.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockA.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program memory.

void main_memory_initialize()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize shared memory.

   // Locals
   int  tNumBytes = 1024*1024;
   bool tConstructorFlag = true;

   // Initialize shared memory.
   tConstructorFlag = CC::gSharedMemory.initialize(tNumBytes);

   Prn::print(0, "ConstuctionFlag  %d",tConstructorFlag);

   // Initialize shared channel.
   CC::gSharedSynch.initialize(tConstructorFlag,CC::gSharedMemory.mSynchMemory);

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
   tBlockPoolParms.mPoolIndex       = Some::cBlockPoolIndex_MyBlockA;
   tBlockPoolParms.mBlockPoolType   = CC::cBlockPoolType_FreeList;
   tBlockPoolParms.mNumBlocks       = 1000;
   tBlockPoolParms.mBlockSize       = sizeof(Some::MyBlockA);
   tBlockPoolParms.mMemory          = CC::gSharedMemory.mBlockPoolMemory;
   tBlockPoolParms.mConstructorFlag = tConstructorFlag;
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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize shared memory.

   CC::gSharedSynch.finalize();
   CC::gSharedMemory.finalize();
}


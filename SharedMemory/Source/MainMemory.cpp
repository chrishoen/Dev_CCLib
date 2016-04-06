
#include "prnPrint.h"
#include "GSettings.h"
#include "ccSharedMemory.h"
#include "ccBlockPoolCentral.h"
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

   bool tConstructorFlag = true;
   if (gGSettings.isServer())
   {
      CC::gSharedMemory.initializeForServer(1024 * 1024);
      tConstructorFlag = true;
   }
   else
   {
      CC::gSharedMemory.initializeForClient();
      tConstructorFlag = false;
   }

   Prn::print(0, "SharedMemory %p",CC::gSharedMemory.mMemory);

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
   tBlockPoolParms.mMemory          = CC::gSharedMemory.mMemory;
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

   CC::gSharedMemory.finalize();
}


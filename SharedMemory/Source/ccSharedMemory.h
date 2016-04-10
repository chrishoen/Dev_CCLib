#ifndef _CCSHAREDMEMORY_H_
#define _CCSHAREDMEMORY_H_

/*==============================================================================
Shared Memory class, global object.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "ccBlockHandle.h"
#include "ccBlockPoolCentral.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This creates or opens a region of shared memory.

class SharedMemory
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SharedMemory();

   // Create the shared memory and calculate addresses.
   void initializeForServer(int aNumBytes);
   
   // Open the shared memory and calculate addresses.
   void initializeForClient();

   // Close the shared memory.
   void finalize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   void* mMemory;
   void* mSynchMemory;
   void* mBlockPoolMemory;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // More.

   static const int cSynchMemorySize = 65536;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // pimpl idiom.

protected:
   class Specific;
   Specific* mSpecific;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _CCSHAREDMEMORY_CPP_
          SharedMemory gSharedMemory;
#else
   extern SharedMemory gSharedMemory;
#endif

}//namespace

#endif

#ifndef _CCSHAREDMEMORY_H_
#define _CCSHAREDMEMORY_H_

/*==============================================================================
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

class SharedMemory
{
public:

   SharedMemory();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   void initializeForServer(int aNumBytes);
   void initializeForClient();
   void finalize();

   // Synchronization objects
   bool putSemaphore     (void);
   bool getSemaphore     (void);
   bool putMutex         (void);
   bool getMutex         (void);

   int mNumBytes;
   bool mFreeMemoryFlag;
   void* mMemory1;
   void* mMemory2;

   static const int cMemorySize1 = 65536;

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


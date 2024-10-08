#pragma once

/*==============================================================================
Shared memory region.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <atomic>

#include "someTestRing.h"


//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// The following rules are for shared memory regions that are shared between
// different processes (who therefore have different address spaces):
// 
// 1) No constructors.
// 2) No pointers.
// 3) No dynamic memory, this means no std::vector, ...
// 4) No vtables, this means no virtual functions.
//
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a set of variables that live in a shared memory
// region that is concurrently accessed by cproc, touchscreen, and web gui
// code.

class Share
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Resource count. Incremented each time that a process attaches to the
   // shared memory region. Decremented each time that a process deattaches.
   int mResourceCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   Some::TestRing mTestRing;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize, there's no constructor. This is called by the process who
   // first creates the shared memory.
   void initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   void show(int aPrintFilter = 0);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance initialize and finalize.

// Create a shared memory region for the global instance and call placement
// new with the shared memory address. If this is the first process to access
// the region (it was created created, not opened) then initialize the global
// instance. Otherwise, do not initialize it, because the first process
// already did.
void initializeShare();

// Close the shared memory region for the global instance.
void finalizeShare();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SMSHARE_CPP_
          Share* gShare = 0;
#else
   extern Share* gShare;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


#pragma once

/*==============================================================================
Shared memory region.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccSRSWValueQueue.h"
#include "ccSRSWObjectQueue.h"
#include "someClass1.h"
#include "someStateSX.h"

#include "someTestRing.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// ALSO, DON'T FORGET:
// The following rules are for shared memory, regions that are shared between
// different processes(who therefore have different address spaces) :
//
// 1) No constructors.
// 2) No pointers.
// 3) No dynamic memory, this means no std::vector, ...
// 4) No vtables, this means no virtual functions.
// 5) Be careful with your loads and stores.
//
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a set of variables that live in a shared memory
// region that is concurrently accessed by cproc, touchscreen, and web gui
// code.

class alignas(16) Share
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Shared memory sync words.
   int mCpuSync1;
   int mRpuSync1;

   // Resource count. Incremented each time that a process attaches to the
   // shared memory region. Decremented each time that a process deattaches.
   int mResourceCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Queues for cpu testing.
   CC::SRSWValueQueue<int, 101> mValQueue;
   CC::SRSWObjectQueue<Some::Class1, 101> mObjQueue;

   // Queues for uplink testing.
   CC::SRSWValueQueue<int, 101> mUpValQueue;
   CC::SRSWObjectQueue<Some::Class1, 101> mUpObjQueue;

   // Queues for downlink testing.
   CC::SRSWValueQueue<int, 101> mDownValQueue;
   CC::SRSWObjectQueue<Some::Class1, 101> mDownObjQueue;

   // Ring buffer for cpu testing.
   Some::TestRing mTestRing;

   // Ring buffer for uplink testing.
   Some::TestRing mUpRing;

   // Ring buffer for downlink testing.
   Some::TestRing mDownRing;

   // State.
   Some::State mSX;

   // Test class instances.
   Some::Class1 mClass1[10];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Shared memory sync words.
   int mCpuSync2;
   int mRpuSync2;

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

   void show();
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
void initializeShare(bool aInitVars);


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


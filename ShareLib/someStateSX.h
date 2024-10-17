#pragma once

/*==============================================================================
State variables.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************


namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a general purpose shared storage object. It contains
// status counters and flags.

class alignas(16) State
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue members:

   // Queue variables.
   volatile int mQueueSelect;

   // Test variables.
   volatile int mCpuWriteCount;
   volatile int mCpuWritePassCount;
   volatile int mCpuWriteFullCount;

   volatile int mCpuReadCount;
   volatile int mCpuReadPassCount;
   volatile int mCpuReadEmptyCount;
   volatile int mCpuReadErrorCount;

   // Test variables.
   volatile int mRpuWriteCount;
   volatile int mRpuWritePassCount;
   volatile int mRpuWriteFullCount;

   volatile int mRpuReadCount;
   volatile int mRpuReadPassCount;
   volatile int mRpuReadEmptyCount;
   volatile int mRpuReadErrorCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Ring buffer members:

   alignas(16) volatile long long mRpuRingLastReadIndex;
   volatile int mRpuRingReadCount;
   volatile int mRpuRingAvailable;
   volatile int mRpuRingNotReadyCount1;
   volatile int mRpuRingNotReadyCount2;
   volatile int mRpuRingNotReadyCount3;
   volatile int mRpuRingMissCount;
   volatile int mRpuRingMaxDeltaRead;
   volatile int mRpuRingOverwriteCount;
   volatile int mRpuRingTestPassCount;
   volatile int mRpuRingTestFailCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // No constructor.
   void reset();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


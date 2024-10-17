/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"


#include "someStateSX.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// No constructor

void State::reset()
{
   mQueueSelect = 0;

   mCpuWriteCount = 0;
   mCpuWritePassCount = 0;
   mCpuWriteFullCount = 0;
   mCpuReadCount = 0;
   mCpuReadPassCount = 0;
   mCpuReadEmptyCount = 0;
   mCpuReadErrorCount = 0;

   mRpuWriteCount = 0;
   mRpuWritePassCount = 0;
   mRpuWriteFullCount = 0;
   mRpuReadCount = 0;
   mRpuReadPassCount = 0;
   mRpuReadEmptyCount = 0;
   mRpuReadErrorCount = 0;

   mRpuRingLastReadIndex = 0;
   mRpuRingReadCount = 0;
   mRpuRingAvailable = 0;
   mRpuRingNotReadyCount1 = 0;
   mRpuRingNotReadyCount2 = 0;
   mRpuRingNotReadyCount3 = 0;
   mRpuRingMissCount = 0;
   mRpuRingMaxDeltaRead = 0;
   mRpuRingOverwriteCount = 0;
   mRpuRingTestPassCount = 0;
   mRpuRingTestFailCount = 0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

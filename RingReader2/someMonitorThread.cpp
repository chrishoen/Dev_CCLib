/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <time.h>

#include "risProgramTime.h"
#include "risThreadsPriorities.h"

#include "smShare.h"

#include "someRingParms.h"
#include "someRingReaderThread.h"

#define  _SOMEMONITORTHREAD_CPP_
#include "someMonitorThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MonitorThread::MonitorThread()
{
   // Set base class variables.
   BaseClass::setThreadName("Monitor");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mMonitor);
   BaseClass::mTimerPeriod = gRingParms.mMonitorThreadPeriod;

   // Set member variables.
   mShowCode = 1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void MonitorThread::executeOnTimer(int aTimeCount)
{
   if (mShowCode == 1)
   {
      Prn::print(Prn::Show1, "%1d$   %3lld %3lld  %3d NRDY %d %d %d DROP %d %d OVER %d TEST %d %d",
         gRingReaderThread->mThreadCurrentProcessor,
         SM::gShare->mTestRingBuffer.mNextWriteIndex.load(std::memory_order_relaxed),
         gRingReaderThread->mRingReader.mLastReadIndex,
         gRingReaderThread->mRingReader.available(),
         gRingReaderThread->mRingReader.mNotReadyCount1,
         gRingReaderThread->mRingReader.mNotReadyCount2,
         gRingReaderThread->mRingReader.mNotReadyCount3,
         gRingReaderThread->mRingReader.mDropCount,
         gRingReaderThread->mRingReader.mMaxDeltaRead,
         gRingReaderThread->mRingReader.mOverwriteCount,
         gRingReaderThread->mRingReader.mTestPassCount,
         gRingReaderThread->mRingReader.mTestFailCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
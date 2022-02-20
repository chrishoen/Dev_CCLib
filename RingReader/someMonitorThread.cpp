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
      Prn::print(Prn::Show1, "%1d$   %3lld %3lld NRDY %d %d %d DROP %d %d TEST %d %d",
         gRingReaderThread->mThreadCurrentProcessor,
         SM::gShare->mTestRingBuffer.mWriteIndex.load(std::memory_order_relaxed),
         gRingReaderThread->mRingReader.mReadIndex,
         gRingReaderThread->mRingReader.mNotReadyCount1,
         gRingReaderThread->mRingReader.mNotReadyCount2,
         gRingReaderThread->mRingReader.mNotReadyCount3,
         gRingReaderThread->mRingReader.mDropCount1,
         gRingReaderThread->mRingReader.mDropCount2,
         gRingReaderThread->mRingReader.mTestPassCount,
         gRingReaderThread->mRingReader.mTestFailCount);

   }

   else if (mShowCode == 2)
   {
      if (gRingReaderThread->mStatPollFlag)
      {
         gRingReaderThread->mStatPollFlag = false;
         Prn::print(Prn::Show1, "Timer1 %5d %2d $$ %10.1f %10.1f %10.1f %10.1f $$ %10.1f",
            gRingReaderThread->mStatCount,
            gRingReaderThread->mThreadCurrentProcessor,
            gRingReaderThread->mStatJitterMean,
            gRingReaderThread->mStatJitterStdDev,
            gRingReaderThread->mStatJitterMin,
            gRingReaderThread->mStatJitterMax,
            gRingReaderThread->mStatJitterMaxMax);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
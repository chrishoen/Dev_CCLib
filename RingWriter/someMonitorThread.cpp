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
#include "someRingWriterThread.h"

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
      Prn::print(Prn::Show1, "%3d %2d $$ %3lld",
         aTimeCount,
         gRingWriterThread->mThreadCurrentProcessor,
         SM::gShare->mTestRingBuffer.mWriteIndex.load(std::memory_order_relaxed));
   }
   else if (mShowCode == 2)
   {
      if (gRingWriterThread->mStatPollFlag)
      {
         gRingWriterThread->mStatPollFlag = false;
         Prn::print(Prn::Show1, "Timer1 %5d %2d $$ %10.1f %10.1f %10.1f %10.1f $$ %10.1f",
            gRingWriterThread->mStatCount,
            gRingWriterThread->mThreadCurrentProcessor,
            gRingWriterThread->mStatJitterMean,
            gRingWriterThread->mStatJitterStdDev,
            gRingWriterThread->mStatJitterMin,
            gRingWriterThread->mStatJitterMax,
            gRingWriterThread->mStatJitterMaxMax);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
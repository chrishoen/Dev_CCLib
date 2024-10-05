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
   mShowCode = 0;

   // Bind member variables.
   mMon_NextWriteIndex.bind((long long*)&SM::gShare->mTestRing.mNextWriteIndex);
}

// Update status variables.
void MonitorThread::update()
{
   mMon_NextWriteIndex.update();
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void MonitorThread::executeOnTimer(int aTimeCount)
{
   update();

   if (mShowCode == 1)
   {
      Prn::print(Prn::Show1, "NextWriteIndex           %-10lld  %lld",
         mMon_NextWriteIndex.mValue, mMon_NextWriteIndex.mDelta);
   }
   else if (mShowCode == 2)
   {
      Prn::print(Prn::Show1, "%1d$   %3lld",
         gRingWriterThread->mThreadCurrentProcessor,
         SM::gShare->mTestRing.mNextWriteIndex);
   }
   else if (mShowCode == 3)
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
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

   // Set base class variables.
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mMonitor);

   // Set timer period.
   BaseClass::mTimerPeriod = gRingParms.mMonitorThreadPeriod;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void MonitorThread::executeOnTimer(int aTimeCount)
{
   if (gRingWriterThread->mStatPollFlag)
   {
      gRingWriterThread->mStatPollFlag = false;
      Prn::print(0, "Timer1 %5d %2d $$ %10.1f %10.1f %10.1f %10.1f $$ %10.1f",
         gRingWriterThread->mStatCount,
         gRingWriterThread->mThreadCurrentProcessor,
         gRingWriterThread->mStatJitterMean,
         gRingWriterThread->mStatJitterStdDev,
         gRingWriterThread->mStatJitterMin,
         gRingWriterThread->mStatJitterMax,
         gRingWriterThread->mStatJitterMaxMax);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
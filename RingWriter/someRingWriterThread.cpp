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

#define  _SOMERINGWRITERTHREAD_CPP_
#include "someRingWriterThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

RingWriterThread::RingWriterThread()
{
   // Set base class variables.
   BaseClass::setThreadName("TimerTest");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mTimerTest);
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gRingParms.mTestThreadProcessor,
         gRingParms.mTestThreadPriority));

   BaseClass::mPollProcessor = gRingParms.mPollProcessor;
   BaseClass::mTimerPeriodUs1 = gRingParms.mRandomThreadPeriodUs1;
   BaseClass::mTimerPeriodUs2 = gRingParms.mRandomThreadPeriodUs2;
   BaseClass::mStatPeriod = gRingParms.mStatPeriod;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RingWriterThread::executeOnTimer(int aTimeCount)
{
   if (aTimeCount == 0)
   {
      BaseClass::showThreadFullInfo();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
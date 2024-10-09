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

#include "someQueueParms.h"
#include "someQueueTester.h"
#include "smShare.h"

#define  _SOMERINGREADERTHREAD1_CPP_
#include "someQueueReaderThread1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constuctor.

QueueReaderThread1::QueueReaderThread1()
{
   // Set base class variables.
   BaseClass::setThreadName("Reader");
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gQueueParms.mReaderThreadProcessor,
         gQueueParms.mReaderThreadPriority));

   BaseClass::mPollProcessor = gQueueParms.mPollProcessor;
   BaseClass::mStatPeriod = gQueueParms.mStatPeriod;
   BaseClass::mIntervalMeanMs = gQueueParms.mReaderThreadMeanMs;
   BaseClass::mIntervalRandomUs = gQueueParms.mReaderThreadRandomUs;
   BaseClass::mPollProcessor = true;

   // Set member variables.
   mTPFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immedidately 
// after the thread starts running. It creates and launches the 
// child SerialMsgThread.

void QueueReaderThread1::threadInitFunction()
{
   SM::gShare->show(0);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immedidately
// before the thread is terminated. It shuts down the child SerialMsgThread.

void QueueReaderThread1::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void QueueReaderThread1::executeOnTimer(int aTimerCount)
{
   // Guard.
   if (!mTPFlag) return;

   // Read from the queue.
   Some::doReadTest();


}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
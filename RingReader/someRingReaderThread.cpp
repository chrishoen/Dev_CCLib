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
#include "smShare.h"

#define  _SOMERINGREADERTHREAD_CPP_
#include "someRingReaderThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constuctor.

RingReaderThread::RingReaderThread()
{
   // Set base class variables.
   BaseClass::setThreadName("TimerTest");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mTimerTest);
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gRingParms.mReaderThreadProcessor,
         gRingParms.mReaderThreadPriority));

   BaseClass::mPollProcessor = gRingParms.mPollProcessor;
   BaseClass::mStatPeriod = gRingParms.mStatPeriod;
   BaseClass::mTimerPeriodUs1 = gRingParms.mReaderThreadPeriodUs1;
   BaseClass::mTimerPeriodUs2 = gRingParms.mReaderThreadPeriodUs2;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immedidately 
// after the thread starts running. It creates and launches the 
// child SerialMsgThread.

void RingReaderThread::threadInitFunction()
{
   SM::gShare->show(0);
      
   // Initialize the writer.
   mRingReader.initialize(
      &SM::gShare->mTestRingBuffer,
      &SM::gShare->mTestRingBuffer.mElementArrayMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immedidately
// before the thread is terminated. It shuts down the child SerialMsgThread.

void RingReaderThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void RingReaderThread::executeOnTimer(int aTimerCount)
{
   // Read a test record to the ring buffer.
   Some::TestRecord tRecord;
   mRingReader.doRead((void*)&tRecord);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
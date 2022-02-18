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

#define  _SOMERINGWRITERTHREAD_CPP_
#include "someRingWriterThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constuctor.

RingWriterThread::RingWriterThread()
{
   // Set base class variables.
   BaseClass::setThreadName("TimerTest");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mTimerTest);
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gRingParms.mWriterThreadProcessor,
         gRingParms.mWriterThreadPriority));

   BaseClass::mPollProcessor = gRingParms.mPollProcessor;
   BaseClass::mStatPeriod = gRingParms.mStatPeriod;
   BaseClass::mTimerPeriodUs1 = gRingParms.mWriterThreadPeriodUs1;
   BaseClass::mTimerPeriodUs2 = gRingParms.mWriterThreadPeriodUs2;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immedidately 
// after the thread starts running. It creates and launches the 
// child SerialMsgThread.

void RingWriterThread::threadInitFunction()
{
   // Initialize the tester.
   mRingTester.reset();

   // Initialize the writer.
   mRingWriter.initialize(&SM::gShare->mTestRingBuffer);

   // Initialize the writer test function pointer.
   mRingWriter.mTestFunction = std::bind(
      &Some::TestTester::doWriteTest, &mRingTester,
      std::placeholders::_1, std::placeholders::_2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immedidately
// before the thread is terminated. It shuts down the child SerialMsgThread.

void RingWriterThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void RingWriterThread::executeOnTimer(int aTimerCount)
{
   // Write a test record to the ring buffer.
   Some::TestRecord tRecord;
   mRingWriter.doWrite((void*)&tRecord);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
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

#define  _SOMERINGREADERTHREAD1_CPP_
#include "someRingReaderThread1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constuctor.

RingReaderThread1::RingReaderThread1()
{
   // Set base class variables.
   BaseClass::setThreadName("Reader");
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gRingParms.mReaderThreadProcessor,
         gRingParms.mReaderThreadPriority));

   BaseClass::mPollProcessor = gRingParms.mPollProcessor;
   BaseClass::mStatPeriod = gRingParms.mStatPeriod;
   BaseClass::mIntervalMeanMs = gRingParms.mReaderThreadMeanMs;
   BaseClass::mIntervalRandomUs = gRingParms.mReaderThreadRandomUs;
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

void RingReaderThread1::threadInitFunction()
{
   SM::gShare->show(0);
      
   // Initialize the reader.
   mRingReader.initialize(
      &SM::gShare->mTestRing,
      &SM::gShare->mTestRing.mElementArrayMemory);

   //mRingReader.doRestartAtMin();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immedidately
// before the thread is terminated. It shuts down the child SerialMsgThread.

void RingReaderThread1::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void RingReaderThread1::executeOnTimer(int aTimerCount)
{
   // Guard.
   if (!mTPFlag) return;

   // Read a test record to the ring buffer.
   Some::TestRecord tRecord;
   mRingReader.doRead((void*)&tRecord);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
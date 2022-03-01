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
   BaseClass::setThreadName("Reader");
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gRingParms.mReaderThreadProcessor,
         gRingParms.mReaderThreadPriority));

   BaseClass::mPollProcessor = gRingParms.mPollProcessor;
   BaseClass::mStatPeriod = gRingParms.mStatPeriod;
   BaseClass::mTimerPeriodUs1 = gRingParms.mReaderThreadPeriodUs1;
   BaseClass::mTimerPeriodUs2 = gRingParms.mReaderThreadPeriodUs2;
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
   // Guard.
   if (!mTPFlag) return;

   // Read a test record to the ring buffer.
   Some::TestRecord tRecord;
   mRingReader.doRead((void*)&tRecord);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void RingReaderThread::show()
{
   Prn::print(0, "");
   Prn::print(0, "mNextWriteIndex            %16lld", SM::gShare->mTestRingBuffer.mNextWriteIndex.load(std::memory_order_relaxed));
   Prn::print(0, "Reader.mLastReadIndex      %16lld", mRingReader.mLastReadIndex);

   Prn::print(0, "");
   Prn::print(0, "Reader.NotReadyCount1      %16d", mRingReader.mNotReadyCount1);
   Prn::print(0, "Reader.NotReadyCount2      %16d", mRingReader.mNotReadyCount2);
   Prn::print(0, "Reader.NotReadyCount3      %16d", mRingReader.mNotReadyCount3);
   Prn::print(0, "Reader.ErrorCount          %16d", mRingReader.mErrorCount);
   Prn::print(0, "Reader.DropCount           %16d", mRingReader.mDropCount);
   Prn::print(0, "Reader.mMaxDeltaRead       %16d", mRingReader.mMaxDeltaRead);
   Prn::print(0, "Reader.OverwriteCount      %16d", mRingReader.mOverwriteCount);

   Prn::print(0, "");
   Prn::print(0, "Reader.mFirstReadIndex     %16lld", mRingReader.mFirstReadIndex);
   Prn::print(0, "Reader.TestPassCount       %16d", mRingReader.mTestPassCount);
   Prn::print(0, "Reader.TestFailCount       %16d", mRingReader.mTestFailCount);

   int tSum1 = mRingReader.mTestPassCount + mRingReader.mDropCount;
   int tSum2 = tSum1 + (int)mRingReader.mFirstReadIndex;
   Prn::print(0, "");
   Prn::print(0, "Reader Sum1                %16d", tSum1);
   Prn::print(0, "Reader Sum2                %16d", tSum2);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
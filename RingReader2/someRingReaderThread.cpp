/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "risProgramTime.h"
#include "risThreadsPriorities.h"

#include "someRingParms.h"
#include "smShare.h"

#define  _SOMERINGREADERTHREAD_CPP_
#include "someRingReaderThread.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

RingReaderThread::RingReaderThread()
{
   // Set base class variables.
   BaseClass::setThreadName("Reader");
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gRingParms.mReaderThreadProcessor,
         gRingParms.mReaderThreadPriority));

   // Set member variables.
   mTPFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately
// after the thread starts running. It initializes the serial port.

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
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It is close the serial port.

void RingReaderThread::threadExitFunction()
{
   printf("someRingReaderThread::threadExitFunction\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This is called out of the context of
// this thread. It aborts the serial port receive and waits for the
// thread to terminate after execution of the thread exit function.

void RingReaderThread::shutdownThread()
{
   printf("someRingReaderThread::shutdownThread\n");
   // Wait for thread to terminate.
   BaseClass::shutdownThread();
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
// Thread run function. This is called by the base class immediately
// after the thread init function. It runs a loop that blocks on 
// serial port receives and then processes them. The loop terminates
// when the serial port receive is aborted.

void RingReaderThread::threadRunFunction()
{
   // Guard.

   while (true)
   {
      if (BaseClass::mTerminateFlag) return;
      if (!mTPFlag)
      {
         Ris::sleepUs(gRingParms.mSleepAfterNotReadyUs);
         continue;
      }

      Some::TestRecord tRecord;
      mRingReader.doRead((void*)&tRecord);
      if (mRingReader.mNotReadyFlag) Ris::sleepUs(gRingParms.mSleepAfterNotReadyUs);
      if (mRingReader.mOverwriteFlag) Ris::sleepUs(gRingParms.mSleepAfterOverwriteUs);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
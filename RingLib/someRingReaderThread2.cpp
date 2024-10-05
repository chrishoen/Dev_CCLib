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

#define  _SOMERINGREADERTHREAD2_CPP_
#include "someRingReaderThread2.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

RingReaderThread2::RingReaderThread2()
{
   // Set base class variables.
   BaseClass::setThreadName("Reader");
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gRingParms.mReaderThreadProcessor,
         gRingParms.mReaderThreadPriority));

   // Set member variables.
   mTPFlag = true;
   mStopFlag = false;

   // Seed random generator and random sleep.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());
   mRandomDistribution = std::uniform_int_distribution<>(0, gRingParms.mSuspendRandom);
   mSuspendSleep.initialize(gRingParms.mSuspendSleepMeanMs, gRingParms.mSuspendSleepRandomMs * 1000);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately
// after the thread starts running. It initializes the serial port.

void RingReaderThread2::threadInitFunction()
{
   SM::gShare->show(0);

   // Initialize the reader.
   mRingReader.initialize(
      &SM::gShare->mTestRing,
      &SM::gShare->mTestRing.mElementArrayMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It is close the serial port.

void RingReaderThread2::threadExitFunction()
{
   printf("someRingReaderThread2::threadExitFunction\n");
   show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This is called out of the context of
// this thread. It aborts the serial port receive and waits for the
// thread to terminate after execution of the thread exit function.

void RingReaderThread2::shutdownThread()
{
   printf("someRingReaderThread2::shutdownThread\n");
   // Wait for thread to terminate.
   BaseClass::shutdownThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void RingReaderThread2::show()
{
   Prn::print(0, "");
   Prn::print(0, "mNextWriteIndex            %16lld", SM::gShare->mTestRing.mNextWriteIndex);
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

   Prn::print(0, "Reader.TestFailReadIndex   %16d", mRingReader.mTestFailReadIndex);
#if 0
   Prn::print(0, "");
   for (int i = 0; i < 7; i++)
   {
   Prn::print(0, "Reader.mTestFailCode[%1d]    %16d", i, mRingReader.mTestFailCode[i]);
   }
#endif
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

void RingReaderThread2::threadRunFunction()
{
   if (gRingParms.mReadTestMode == 1)
   {
      doTest1();
   }
   else if (gRingParms.mReadTestMode == 2)
   {
      doTest2();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test.

void RingReaderThread2::doTest1()
{
   int tCount = 0;
   while (true)
   {
      // Process thread execution variables.
      if (BaseClass::mTerminateFlag) return;
      if (tCount % 5000 == 0)
      {
         BaseClass::getThreadProcessorNumber();
      }
      if (!mTPFlag)
      {
         Ris::sleepUs(gRingParms.mSleepAfterNotReadyUs);
         continue;
      }

      // Read a record.
      Some::TestRecord tRecord;
      mRingReader.doRead((void*)&tRecord);
      if (mRingReader.mNotReadyFlag) Ris::sleepUs(gRingParms.mSleepAfterNotReadyUs);
      if (mRingReader.mOverwriteFlag) Ris::sleepUs(gRingParms.mSleepAfterOverwriteUs);
      tCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test.

void RingReaderThread2::doTest2()
{
   int tCount = 0;
   while (true)
   {
      // Process thread execution variables.
      if (BaseClass::mTerminateFlag) return;
      if (tCount % 5000 == 0)
      {
         BaseClass::getThreadProcessorNumber();
      }
      if (!mTPFlag)
      {
         Ris::sleepUs(gRingParms.mSleepAfterNotReadyUs);
         continue;
      }

      if (mRandomDistribution(mRandomGenerator) == 0)
      {
         printf("RD SUSPEND\n");
         mSuspendSleep.doSleep();
      }

      // Read a record.
      Some::TestRecord tRecord;
      mRingReader.doRead((void*)&tRecord);
      if (mRingReader.mNotReadyFlag) Ris::sleepUs(gRingParms.mSleepAfterNotReadyUs);
      if (mRingReader.mOverwriteFlag) Ris::sleepUs(gRingParms.mSleepAfterOverwriteUs);
      tCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
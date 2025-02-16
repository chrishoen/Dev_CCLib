/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "risProgramTime.h"
#include "cmnPriorities.h"

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
   BaseClass::setThreadPriority(Cmn::gPriorities.mRingReader);

   // Set member variables.
   mTPFlag = true;

   // Seed random generator.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());
   mRandomDistribution = std::uniform_int_distribution<>(0, gRingParms.mReadSuspendRandom);

   // Random sleeps.
   mReadSleep.initialize(gRingParms.mReadSleepMeanMs, gRingParms.mReadSleepRandomUs);
   mSuspendSleep.initialize(gRingParms.mSuspendSleepMeanMs, gRingParms.mSuspendSleepRandomMs * 1000);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately
// after the thread init function. It runs a loop that attempts to
// read a record from the ring buffer. If success, then the record is
// processed, else a random sleep. The loop terminates on the terminate
// flag.

void RingReaderThread::threadInitFunction()
{
   // Initialize the reader.
   if (gRingParms.mScope == 1)
   {
      mRingReader.initialize(
         &SM::gShare->mTestRing,
         &SM::gShare->mTestRing.mElementArrayMemory[0]);
   }
   else
   {
      mRingReader.initialize(
         &SM::gShare->mDownRing,
         &SM::gShare->mDownRing.mElementArrayMemory[0]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated.

void RingReaderThread::threadExitFunction()
{
   printf("someRingReaderThread::threadExitFunction\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This is called out of the context of
// this thread. It sets the termination flag and waits for the
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
// Thread run function. This is called by the base class immediately
// after the thread init function. It runs a loop that attempts to
// read a record from the ring buffer. If success, then the record is
// processed, else a random sleep. The loop terminates on the terminate
// flag.

void RingReaderThread::threadRunFunction()
{
   if (gRingParms.mReadTestMode == 1)
   {
      doTestLoop1();
   }
   else if (gRingParms.mReadTestMode == 2)
   {
      doTestLoop2();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test.

void RingReaderThread::doTestLoop1()
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
      // If not running then just sleep.
      if (!mTPFlag)
      {
         Ris::sleepMs(100);
         continue;
      }

      // Try to read a record.
      Some::TestRecord tRecord;
      if (!mRingReader.doRead(&tRecord))
      {
         // If not success then random sleep.
         mReadSleep.doSleep();
      }
      tCount++;

   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test.

void RingReaderThread::doTestLoop2()
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
      // If not running then just sleep.
      if (!mTPFlag)
      {
         Ris::sleepMs(100);
         continue;
      }

      // Randomly sleep to simulate thread preemption.
      if (mRandomDistribution(mRandomGenerator) == 0)
      {
         printf("RD SUSPEND\n");
         mSuspendSleep.doSleep();
      }

      // Try to read a record.
      Some::TestRecord tRecord;
      if (!mRingReader.doRead(&tRecord))
      {
         // If not success then random sleep.
         mReadSleep.doSleep();
      }
      tCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
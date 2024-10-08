/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "risProgramTime.h"
#include "risThreadsPriorities.h"

#include "someQueueParms.h"
#include "smShare.h"

#define  _SOMERINGREADERTHREAD2_CPP_
#include "someQueueReaderThread2.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

QueueReaderThread2::QueueReaderThread2()
{
   // Set base class variables.
   BaseClass::setThreadName("Reader");
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gQueueParms.mReaderThreadProcessor,
         gQueueParms.mReaderThreadPriority));

   // Set member variables.
   mTPFlag = true;
   mStopFlag = false;

   // Seed random generator and random sleep.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());
   mRandomDistribution = std::uniform_int_distribution<>(0, gQueueParms.mSuspendRandom);
   mSuspendSleep.initialize(gQueueParms.mSuspendSleepMeanMs, gQueueParms.mSuspendSleepRandomMs * 1000);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately
// after the thread starts running. It initializes the serial port.

void QueueReaderThread2::threadInitFunction()
{
   SM::gShare->show(0);

   // Initialize the reader.
   mQueueReader.initialize(
      &SM::gShare->mTestQueue,
      &SM::gShare->mTestQueue.mElementArrayMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It is close the serial port.

void QueueReaderThread2::threadExitFunction()
{
   printf("someQueueReaderThread2::threadExitFunction\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This is called out of the context of
// this thread. It aborts the serial port receive and waits for the
// thread to terminate after execution of the thread exit function.

void QueueReaderThread2::shutdownThread()
{
   printf("someQueueReaderThread2::shutdownThread\n");
   // Wait for thread to terminate.
   BaseClass::shutdownThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately
// after the thread init function. It runs a loop that blocks on 
// serial port receives and then processes them. The loop terminates
// when the serial port receive is aborted.

void QueueReaderThread2::threadRunFunction()
{
   if (gQueueParms.mReadTestMode == 1)
   {
      doTest1();
   }
   else if (gQueueParms.mReadTestMode == 2)
   {
      doTest2();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test.

void QueueReaderThread2::doTest1()
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
         Ris::sleepUs(gQueueParms.mSleepAfterNotReadyUs);
         continue;
      }

      // Read a record.
      Some::TestRecord tRecord;
      mQueueReader.doRead((void*)&tRecord);
      if (mQueueReader.mNotReadyFlag) Ris::sleepUs(gQueueParms.mSleepAfterNotReadyUs);
      if (mQueueReader.mOverwriteFlag) Ris::sleepUs(gQueueParms.mSleepAfterOverwriteUs);
      tCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test.

void QueueReaderThread2::doTest2()
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
         Ris::sleepUs(gQueueParms.mSleepAfterNotReadyUs);
         continue;
      }

      if (mRandomDistribution(mRandomGenerator) == 0)
      {
         printf("RD SUSPEND\n");
         mSuspendSleep.doSleep();
      }

      // Read a record.
      Some::TestRecord tRecord;
      mQueueReader.doRead((void*)&tRecord);
      if (mQueueReader.mNotReadyFlag) Ris::sleepUs(gQueueParms.mSleepAfterNotReadyUs);
      if (mQueueReader.mOverwriteFlag) Ris::sleepUs(gQueueParms.mSleepAfterOverwriteUs);
      tCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
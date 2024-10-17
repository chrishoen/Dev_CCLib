/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "risProgramTime.h"
#include "risThreadsPriorities.h"

#include "someQueueParms.h"
#include "someQueueTester.h"
#include "smShare.h"

#define  _SOMERINGREADERTHREAD2_CPP_
#include "someQueueReaderThread.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

QueueReaderThread::QueueReaderThread()
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
   mRandomDistribution = std::uniform_int_distribution<>(0, gQueueParms.mReadSuspendRandom);

   // Random sleeps.
   mReadSleep.initialize(gQueueParms.mReadSleepMeanMs, gQueueParms.mReadSleepRandomUs);
   mSuspendSleep.initialize(gQueueParms.mSuspendSleepMeanMs, gQueueParms.mSuspendSleepRandomMs * 1000);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately
// after the thread starts running.

void QueueReaderThread::threadInitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated.

void QueueReaderThread::threadExitFunction()
{
   printf("someQueueReaderThread::threadExitFunction\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This is called out of the context of
// this thread. It sets the termination flag and waits for the
// thread to terminate after execution of the thread exit function.

void QueueReaderThread::shutdownThread()
{
   printf("someQueueReaderThread::shutdownThread\n");
   // Wait for thread to terminate.
   BaseClass::shutdownThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately
// after the thread init function. It runs a loop that reads from
// the queue. The loop terminates on the termination flag.

void QueueReaderThread::threadRunFunction()
{
   switch (gQueueParms.mReadTestMode)
   {
   case 1: doTestLoop1(); break;
   case 2: doTestLoop2(); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test.

void QueueReaderThread::doTestLoop1()
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
         Ris::sleepUs(100);
         continue;
      }

      // Try to read a record from the queue.
      if (!doReadTest())
      {
         // If the queue was empty then random sleep.
         mReadSleep.doSleep();
      }
      tCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test.

void QueueReaderThread::doTestLoop2()
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
         Ris::sleepUs(100);
         continue;
      }

      // Randomly sleep to simulate thread preemption.
      if (mRandomDistribution(mRandomGenerator) == 0)
      {
         printf("RD SUSPEND\n");
         mSuspendSleep.doSleep();
      }

      // Try to read a record from the queue.
      if (!doReadTest())
      {
         // If the queue was empty then random sleep.
         mReadSleep.doSleep();
      }
      tCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
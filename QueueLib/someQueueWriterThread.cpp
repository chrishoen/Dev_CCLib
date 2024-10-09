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

#define  _SOMERINGWRITERTHREAD_CPP_
#include "someQueueWriterThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constuctor.

QueueWriterThread::QueueWriterThread()
{
   // Set base class variables.
   BaseClass::setThreadName("Writer");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mTimerTest);
   BaseClass::setThreadPriority(
      Ris::Threads::Priority(
         gQueueParms.mWriterThreadProcessor,
         gQueueParms.mWriterThreadPriority));

   BaseClass::mPollProcessor = gQueueParms.mPollProcessor;
   BaseClass::mStatPeriod = gQueueParms.mStatPeriod;
   BaseClass::mIntervalMeanMs = gQueueParms.mWriterThreadMeanMs;
   BaseClass::mIntervalRandomUs = gQueueParms.mWriterThreadRandomUs;

   // Set member variables.
   mTPFlag = false;

   // Seed random generator and random sleep.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());
   mRandomDistribution = std::uniform_int_distribution<>(0, gQueueParms.mWriteSuspendRandom);
   mSuspendSleep.initialize(gQueueParms.mSuspendSleepMeanMs, gQueueParms.mSuspendSleepRandomMs * 1000);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immedidately 
// after the thread starts running. It creates and launches the 
// child SerialMsgThread.

void QueueWriterThread::threadInitFunction()
{
   SM::gShare->show(0);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immedidately
// before the thread is terminated. It shuts down the child SerialMsgThread.

void QueueWriterThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void QueueWriterThread::executeOnTimer(int aTimerCount)
{
   if (gQueueParms.mWriteTestMode == 1)
   {
      doTest1();
   }
   else if(gQueueParms.mWriteTestMode == 2)
   {
      doTest2();
   }
   else if (gQueueParms.mWriteTestMode == 3)
   {
      doTest3();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void QueueWriterThread::doTest1()
{
   // Guard.
   if (!mTPFlag) return;

   // Write some test records to the queue buffer.
   for (int i = 0; i < gQueueParms.mNumWrites; i++)
   {
      // Write to the queue.
      doWriteTest();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void QueueWriterThread::doTest2()
{
   // Guard.
   if (!mTPFlag) return;

   if (mRandomDistribution(mRandomGenerator) == 0)
   {
      printf("WR SUSPEND\n");
      mSuspendSleep.doSleep();
   }

   // Write some test records to the queue buffer.
   for (int i = 0; i < gQueueParms.mNumWrites; i++)
   {
      // Write to the queue.
      doWriteTest();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void QueueWriterThread::doTest3()
{
   // Guard.
   if (!mTPFlag) return;

   // Write some test records to the queue buffer.
   for (int i = 0; i < gQueueParms.mNumWrites; i++)
   {
      // Write to the queue.
      doWriteTest();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace




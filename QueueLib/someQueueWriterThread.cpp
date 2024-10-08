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
   mRandomDistribution = std::uniform_int_distribution<>(0, gQueueParms.mSuspendRandom);
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
      
   // Initialize the writer.
   mQueueWriter.initialize(
      &SM::gShare->mTestQueue, 
      &SM::gShare->mTestQueue.mElementArrayMemory);
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
      Some::TestRecord tRecord;
      mQueueWriter.doWrite((void*)&tRecord);
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

   // Write some test records to the queue buffer.
   for (int i = 0; i < gQueueParms.mNumWrites; i++)
   {
      if (mRandomDistribution(mRandomGenerator) == 0)
      {
         printf("WR SUSPEND\n");
         mSuspendSleep.doSleep();
      }

      Some::TestRecord tRecord;
      mQueueWriter.doWrite((void*)&tRecord);
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
      // Start a write and set the next record to a dummy value.
      Some::TestRecord* tPtr = (Some::TestRecord*)mQueueWriter.startWrite();
      tPtr->doSet(102);

      // Get the write index of the element that lags behind the write index 
      // by the read gap. This is  the last element that can safely be written to.
      long long tLaggingWriteIndex = mQueueWriter.getNextWriteIndex() - mQueueWriter.mReadGap;

      // Test that the entire read gap has been written to. 
      if (tLaggingWriteIndex >= 0)
      {
         // Get the corresponding element pointer.
         Some::TestRecord* tLaggingPtr = (Some::TestRecord*)mQueueWriter.elementAt(tLaggingWriteIndex);

         // Set the value for test3, for which the value is not automatically set 
         // by the test function.
         tLaggingPtr->doSet(tLaggingWriteIndex);
      }

      // Finish the write.
      mQueueWriter.finishWrite();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace




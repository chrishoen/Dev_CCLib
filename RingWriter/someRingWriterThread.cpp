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

   // Set member variables.
   mTPFlag = true;

   // Seed random generator and random sleep.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());
   mRandomDistribution = std::uniform_int_distribution<>(0, gRingParms.mSuspendRandom);
   mSuspendSleep.initialize(gRingParms.mSuspendSleepMs1, gRingParms.mSuspendSleepMs2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immedidately 
// after the thread starts running. It creates and launches the 
// child SerialMsgThread.

void RingWriterThread::threadInitFunction()
{
   SM::gShare->show(0);
      
   // Initialize the writer.
   mRingWriter.initialize(
      &SM::gShare->mTestRingBuffer, 
      &SM::gShare->mTestRingBuffer.mElementArrayMemory);
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
   if (gRingParms.mWriteTestMode == 1)
   {
      doTest1();
   }
   else if(gRingParms.mWriteTestMode == 2)
   {
      doTest2();
   }
   else if (gRingParms.mWriteTestMode == 3)
   {
      doTest3();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void RingWriterThread::doTest1()
{
   // Guard.
   if (!mTPFlag) return;

   // Write some test records to the ring buffer.
   for (int i = 0; i < gRingParms.mNumWrites; i++)
   {
      Some::TestRecord tRecord;
      mRingWriter.doWrite((void*)&tRecord);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void RingWriterThread::doTest2()
{
   // Guard.
   if (!mTPFlag) return;

   // Write some test records to the ring buffer.
   for (int i = 0; i < gRingParms.mNumWrites; i++)
   {
      if (mRandomDistribution(mRandomGenerator) == 0)
      {
         printf("SUSPEND\n");
         mSuspendSleep.doSleep();
      }

      Some::TestRecord tRecord;
      mRingWriter.doWrite((void*)&tRecord);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void RingWriterThread::doTest3()
{
   // Guard.
   if (!mTPFlag) return;

   // Write some test records to the ring buffer.
   for (int i = 0; i < gRingParms.mNumWrites; i++)
   {
      // Start a write and set the next record to a dummy value.
      Some::TestRecord* tPtr = (Some::TestRecord*)mRingWriter.startWrite();
      tPtr->doSet(102);

      // Get the write index of the element that lags behind the write index 
      // by the read gap. This is  the last element that can safely be written to.
      long long tLaggingWriteIndex = mRingWriter.getNextWriteIndex() - mRingWriter.mReadGap;

      // Test that the entire read gap has been written to. 
      if (tLaggingWriteIndex >= 0)
      {
         // Get the corresponding element pointer.
         Some::TestRecord* tLaggingPtr = (Some::TestRecord*)mRingWriter.elementAt(tLaggingWriteIndex);

         // Set the value for test3, for which the value is not automatically set 
         // by the test function.
         tLaggingPtr->doSet(tLaggingWriteIndex);
      }

      // Finish the write.
      mRingWriter.finishWrite();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace




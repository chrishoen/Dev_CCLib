/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <time.h>

#include "risProgramTime.h"
#include "cmnPriorities.h"

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
   BaseClass::setThreadName("Writer");
   BaseClass::setThreadPriority(Cmn::gPriorities.mRingWriter);

   // Set member variables.
   mTPFlag = false;

   // Seed random generator and random sleep.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());
   mRandomDistribution = std::uniform_int_distribution<>(0, gRingParms.mWriteSuspendRandom);

   // Random sleep.
   mWriteSleep.initialize(gRingParms.mWriteSleepMeanMs, gRingParms.mWriteSleepRandomUs);
   mSuspendSleep.initialize(gRingParms.mSuspendSleepMeanMs, gRingParms.mSuspendSleepRandomMs * 1000);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately
// after the thread starts running. It initializes the the ring writer,
// attaching it to the ring buffer.

void RingWriterThread::threadInitFunction()
{
   // Initialize the reader.
   if (gRingParms.mScope == 1)
   {
      // Initialize the writer, attach to the cpu ring buffer.
      mRingWriter.initialize(
         &SM::gShare->mTestRing,
         &SM::gShare->mTestRing.mElementArrayMemory[0]);
   }
   else
   {
      // Initialize the writer, attach to the uplink ring buffer.
      mRingWriter.initialize(
         &SM::gShare->mUpRing,
         &SM::gShare->mUpRing.mElementArrayMemory[0]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immedidately
// before the thread is terminated.

void RingWriterThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This is called out of the context of
// this thread. It sets the termination flag and waits for the
// thread to terminate after execution of the thread exit function.

void RingWriterThread::shutdownThread()
{
   printf("someRingWriterThread::shutdownThread\n");
   // Wait for thread to terminate.
   BaseClass::shutdownThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately
// after the thread init function. It runs a loop that writes a record
// to the ring buffer and sleeps for a semi-random time./ The loop
// terminates on the terminate flag.

void RingWriterThread::threadRunFunction()
{
   // Loop until thread termination.
   while (!BaseThread::mTerminateFlag)
   {
      // Execute test.
      if (mTPFlag)
      {
         switch (gRingParms.mWriteTestMode)
         {
         case 1: doTest1(); break;
         case 2: doTest2(); break;
         case 3: doTest3(); break;
         }
      }
      // Semi-random sleep.
      mWriteSleep.doSleep();
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
      tRecord.reset();
      mRingWriter.doWrite(&tRecord);
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

   // Randomly sleep to simulate thread preemption.
   if (mRandomDistribution(mRandomGenerator) == 0)
   {
      printf("WR SUSPEND\n");
      mSuspendSleep.doSleep();
   }

   // Write some test records to the ring buffer.
   for (int i = 0; i < gRingParms.mNumWrites; i++)
   {
      // Write a record to the ring buffer.
      Some::TestRecord tRecord;
      tRecord.reset();
      mRingWriter.doWrite(&tRecord);
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
      Some::TestRecord* tPtr = mRingWriter.startWrite();
      tPtr->doSet(102);

      // Get the write index of the element that lags behind the write index 
      // by the read gap. This is  the last element that can safely be written to.
      long long tLaggingWriteIndex = mRingWriter.getNextWriteIndex() - cTestRing_ReadGap;

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




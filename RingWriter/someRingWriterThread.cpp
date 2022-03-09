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
   // Guard.
   if (!mTPFlag) return;

   // Write some test records to the ring buffer.
   for (int i = 0; i < gRingParms.mNumWrites; i++)
   {
      Some::TestRecord tRecord;
      tRecord.doSet1(11);
      mRingWriter.doWrite((void*)&tRecord);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



#if 0
// Index of the last element that was written to.
long long tWriteIndex = SM::gShare->mTestRingBuffer.mWriteIndex.load(std::memory_order_relaxed);

// Advance the index to the next element to write to.
if (tWriteIndex < 0)
{
   tWriteIndex = 0;
}
else
{
   tWriteIndex++;
}

// Update the global state. This should be the only place that this
// happens.
SM::gShare->mTestRingBuffer.mWriteIndex.store(tWriteIndex, std::memory_order_relaxed);
return;
#endif


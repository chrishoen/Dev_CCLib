#pragma once

/*==============================================================================
Ring buffer writer thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>
#include "risSleep.h"
#include "risThreadsThreads.h"

#include "someTestRing.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a thread that writes records to a ring buffer. It executes
// semi-periodically according to a random time interval specified by
// a mean and a variation. Upon execution, it writes a record to the 
// ring buffer.

class RingWriterThread : public Ris::Threads::BaseThread
{
public:
   typedef Ris::Threads::BaseThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Ring buffer writer.
   TestRingWriter mRingWriter;

   // If true then perform timer processing.
   bool mTPFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Random numbers.
   std::mt19937 mRandomGenerator;
   std::uniform_int_distribution<> mRandomDistribution;

   // Random sleep.
   Ris::RandomSleepMs mWriteSleep;
   Ris::RandomSleepMs mSuspendSleep;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RingWriterThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Thread base class overloads.

   // Thread init function. This is called by the base class immediately
   // after the thread starts running. It initializes the the ring writer,
   // attaching it to the ring buffer.
   void threadInitFunction() override;

   // Thread run function. This is called by the base class immediately
   // after the thread init function. It runs a loop that writes a record
   // to the ring buffer and sleeps for a semi-random time./ The loop
   // terminates on the terminate flag.
   void threadRunFunction() override;

   // Thread exit function. This is called by the base class immedidately
   // before the thread is terminated.
   void threadExitFunction() override;
   
   // Thread shutdown function. This is called out of the context of
   // this thread. It sets the termination flag and waits for the
   // thread to terminate after execution of the thread exit function.
   void shutdownThread() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Tests.
   void doTest1();
   void doTest2();
   void doTest3();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _SOMERINGWRITERTHREAD_CPP_
          RingWriterThread* gRingWriterThread = 0;
#else
   extern RingWriterThread* gRingWriterThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



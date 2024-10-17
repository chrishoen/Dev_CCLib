#pragma once

/*==============================================================================
Ring buffer reader thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>
#include "risSleep.h"
#include "risThreadsThreads.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a thread that read records from a queue. It runs a loop
// that attempts to read a record from the queue. If the read is
// successful then it processes the record. If the read is not successful
// then it sleeps for a random time.

class QueueReaderThread : public Ris::Threads::BaseThread
{
private:
   typedef Ris::Threads::BaseThread BaseClass;
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true then perform timer processing.
   bool mTPFlag;

   // If true then stop.
   bool mStopFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Random numbers.
   std::mt19937 mRandomGenerator;
   std::uniform_int_distribution<> mRandomDistribution;

   // Random sleep.
   Ris::RandomSleepMs mReadSleep;
   Ris::RandomSleepMs mSuspendSleep;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   QueueReaderThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Base class overloads.

   // Thread init function. This is called by the base class immediately
   // after the thread starts running.
   void threadInitFunction() override;

   // Thread run function. This is called by the base class immediately
   // after the thread init function. It runs a loop that reads from
   // the queue. The loop terminates on the termination flag.
   void threadRunFunction() override;

   // Thread exit function. This is called by the base class immediately
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
   void doTestLoop1();
   void doTestLoop2();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SOMERINGREADERTHREAD2_CPP_
QueueReaderThread* gQueueReaderThread = 0;
#else
extern  QueueReaderThread* gQueueReaderThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


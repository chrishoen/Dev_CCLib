#pragma once

/*==============================================================================
Queue buffer writer thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>
#include "risSleep.h"
#include "risThreadsRandomThread.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class QueueWriterThread : public Ris::Threads::BaseRandomThread
{
public:
   typedef Ris::Threads::BaseRandomThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

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
   Ris::RandomSleepMs mSuspendSleep;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   QueueWriterThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Thread base class overloads.

   // Thread init function. This is called by the base class immedidately 
   // after the thread starts running. It creates and launches the 
   // child SerialMsgThread.
   void threadInitFunction() override;

   // Thread exit function. This is called by the base class immedidately
   // before the thread is terminated. It shuts down the child SerialMsgThread.
   void threadExitFunction() override;

   // Execute periodically. This is called by the base class timer.
   void executeOnTimer(int aTimerCount) override;

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
          QueueWriterThread* gQueueWriterThread = 0;
#else
   extern QueueWriterThread* gQueueWriterThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


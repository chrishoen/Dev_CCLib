#pragma once

/*==============================================================================
Serial test thread that contains a serial port.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsThreads.h"
#include "someTestRingBuffer.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a thread that uses a serial port. It initializes and configures
// the port based on a parms file and then loops on port receives.

class RingReaderThread : public Ris::Threads::BaseThread
{
private:
   typedef Ris::Threads::BaseThread BaseClass;
public:

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Members.

   // Ring buffer reader.
   TestRingReader mRingReader;

   // If true then perform timer processing.
   bool mTPFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RingReaderThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Base class overloads.

   // Thread init function. This is called by the base class immediately
   // after the thread starts running. It initializes the serial port.
   void threadInitFunction() override;

   // Thread run function. This is called by the base class immediately
   // after the thread init function. It runs a loop that blocks on 
   // serial port receives and then processes them. The loop terminates
   // when the serial port receive is aborted.
   void threadRunFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated. It is close the serial port.
   void threadExitFunction() override;

   // Thread shutdown function. It is called out of the context of
   // this thread. It aborts the serial port receive and waits for the
   // thread to terminate after execution of the thread exit function.
   void shutdownThread() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Helpers.

   // Show.
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SOMERINGREADERTHREAD_CPP_
RingReaderThread* gRingReaderThread = 0;
#else
extern  RingReaderThread* gRingReaderThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


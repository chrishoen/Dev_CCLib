#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "someQueueParms.h"
#include "someQueueReaderThread.h"
#include "someQueueWriterThread.h"
#include "someQueueMonitorThread1.h"
#include "someQueueMonitorThread2.h"

#include "risSleep.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This program tests the queues. It runs a queue writer
// thread, a queue reader thread, and a monitor thread.
//
// There are two scopes:
// scope1: test cpu-cpu. 
//   This writes and reads the cpu queue. 
//
// scope2: test cpu-rpu. 
//   This writes to the uplink queue and reads from the downlink
//   queue. The rpu reads from the uplink and writes to the downlink.

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program.

   main_initialize(argc,argv);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Launch program threads.

   if (true)
   {
      Some::gQueueReaderThread = new Some::QueueReaderThread;
      Some::gQueueReaderThread->launchThread();
   }
   if (true)
   {
      Some::gQueueWriterThread = new Some::QueueWriterThread;
      Some::gQueueWriterThread->launchThread();
   }
   if (Some::gQueueParms.mScope == 1)
   {
      Some::gQueueMonitorThread1 = new Some::QueueMonitorThread1;
      Some::gQueueMonitorThread1->launchThread();
   }
   else if (Some::gQueueParms.mScope == 2)
   {
      Some::gQueueMonitorThread2 = new Some::QueueMonitorThread2;
      Some::gQueueMonitorThread2->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Some::gQueueReaderThread) Some::gQueueReaderThread->showThreadInfo();
   if (Some::gQueueWriterThread) Some::gQueueWriterThread->showThreadInfo();
   if (Some::gQueueMonitorThread1) Some::gQueueMonitorThread1->showThreadInfo();
   if (Some::gQueueMonitorThread2) Some::gQueueMonitorThread2->showThreadInfo();


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Start user command line executive, wait for user to exit.

   CmdLineExec* exec = new CmdLineExec;
   Ris::executeCmdLineConsole(exec);
   delete exec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Shutdown program Threads.

   if (Some::gQueueMonitorThread1)
   {
      Some::gQueueMonitorThread1->shutdownThread();
      delete Some::gQueueMonitorThread1;
      Some::gQueueMonitorThread1 = 0;
   }
   if (Some::gQueueMonitorThread2)
   {
      Some::gQueueMonitorThread2->shutdownThread();
      delete Some::gQueueMonitorThread2;
      Some::gQueueMonitorThread2 = 0;
   }
   if (Some::gQueueWriterThread)
   {
      Some::gQueueWriterThread->shutdownThread();
      delete Some::gQueueWriterThread;
      Some::gQueueWriterThread = 0;
   }
   if (Some::gQueueReaderThread)
   {
      Some::gQueueReaderThread->shutdownThread();
      delete Some::gQueueReaderThread;
      Some::gQueueReaderThread = 0;
   }


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize program.

   main_finalize();
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

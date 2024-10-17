#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "someRingParms.h"
#include "someRingReaderThread.h"
#include "someRingWriterThread.h"
#include "someMonitorThread1.h"
#include "someMonitorThread2.h"

#include "risSleep.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This program tests the ring buffers. It runs a ring buffer writer
// thread, a ring buffer reader thread, and a monitor thread.
//
// There are two scopes:
// scope1: test cpu-cpu. 
//   This writes and reads the cpu ring buffer. 
//
// scope2: test cpu-rpu. 
//   This writes to the uplink ring buffer and reads from the downlink
//   ring buffer. The rpu reads from the uplink and writes to the downlink.
//     
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
      Some::gRingReaderThread = new Some::RingReaderThread;
      Some::gRingReaderThread->launchThread();
   }
   if (true)
   {
      Some::gRingWriterThread = new Some::RingWriterThread;
      Some::gRingWriterThread->launchThread();
   }
   if (Some::gRingParms.mScope == 1)
   {
      Some::gMonitorThread1 = new Some::MonitorThread1;
      Some::gMonitorThread1->launchThread();
   }
   else if (Some::gRingParms.mScope == 2)
   {
      Some::gMonitorThread2 = new Some::MonitorThread2;
      Some::gMonitorThread2->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Some::gRingReaderThread) Some::gRingReaderThread->showThreadInfo();
   if (Some::gRingWriterThread) Some::gRingWriterThread->showThreadInfo();
   if (Some::gMonitorThread1) Some::gMonitorThread1->showThreadInfo();
   if (Some::gMonitorThread2) Some::gMonitorThread2->showThreadInfo();

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

   if (Some::gMonitorThread1)
   {
      Some::gMonitorThread1->shutdownThread();
      delete Some::gMonitorThread1;
      Some::gMonitorThread1 = 0;
   }
   if (Some::gMonitorThread2)
   {
      Some::gMonitorThread2->shutdownThread();
      delete Some::gMonitorThread2;
      Some::gMonitorThread2 = 0;
   }
   if (Some::gRingWriterThread)
   {
      Some::gRingWriterThread->shutdownThread();
      delete Some::gRingWriterThread;
      Some::gRingWriterThread = 0;
   }
   if (Some::gRingReaderThread)
   {
      Some::gRingReaderThread->shutdownThread();
      delete Some::gRingReaderThread;
      Some::gRingReaderThread = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize program.

   main_finalize();
   return 0;
}


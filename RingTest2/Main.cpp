#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "someRingParms.h"
#include "someRingReaderThread2.h"
#include "someRingWriterThread.h"
#include "someMonitorThread2.h"

#include "risSleep.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

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
      Some::gRingReaderThread2 = new Some::RingReaderThread2;
      Some::gRingReaderThread2->launchThread();
   }
   if (true)
   {
      Some::gRingWriterThread = new Some::RingWriterThread;
      Some::gRingWriterThread->launchThread();
   }
   if (true)
   {
      Some::gMonitorThread2 = new Some::MonitorThread2;
      Some::gMonitorThread2->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Some::gRingReaderThread2) Some::gRingReaderThread2->showThreadInfo();
   if (Some::gRingWriterThread) Some::gRingWriterThread->showThreadInfo();
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
   if (Some::gRingReaderThread2)
   {
      Some::gRingReaderThread2->shutdownThread();
      delete Some::gRingReaderThread2;
      Some::gRingReaderThread2 = 0;
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

int main22(int argc, char** argv)
{
   bool tRestartFlag = true;
   int tRestartCount = 0;
restart:
   printf("RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART %d\n", tRestartCount++);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program.

   main_initialize(argc, argv);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Launch program threads.

   if (true)
   {
      Some::gRingReaderThread2 = new Some::RingReaderThread2;
      Some::gRingReaderThread2->launchThread();
   }
   if (true)
   {
      Some::gMonitorThread2 = new Some::MonitorThread2;
      Some::gMonitorThread2->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Some::gRingReaderThread2) Some::gRingReaderThread2->showThreadInfo();
   if (Some::gMonitorThread2) Some::gMonitorThread2->showThreadInfo();

   Ris::RandomSleepMs tSleep;
   tSleep.initialize(5000, 500);
   tSleep.doSleep();

   if (Some::gRingReaderThread2->mRingReader.mTestFailCount > 0) tRestartFlag = false;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Shutdown program Threads.

   if (Some::gRingReaderThread2)
   {
      Some::gRingReaderThread2->shutdownThread();
      delete Some::gRingReaderThread2;
      Some::gRingReaderThread2 = 0;
   }

   if (Some::gMonitorThread2)
   {
      Some::gMonitorThread2->shutdownThread();
      delete Some::gMonitorThread2;
      Some::gMonitorThread2 = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize program.

   main_finalize();
   if (tRestartFlag) goto restart;
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

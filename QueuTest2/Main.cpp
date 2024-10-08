#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "someQueueParms.h"
#include "someQueueReaderThread2.h"
#include "someQueueWriterThread.h"
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
      Some::gQueueReaderThread2 = new Some::QueueReaderThread2;
      Some::gQueueReaderThread2->launchThread();
   }
   if (true)
   {
      Some::gQueueWriterThread = new Some::QueueWriterThread;
      Some::gQueueWriterThread->launchThread();
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
   if (Some::gQueueReaderThread2) Some::gQueueReaderThread2->showThreadInfo();
   if (Some::gQueueWriterThread) Some::gQueueWriterThread->showThreadInfo();
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
   if (Some::gQueueWriterThread)
   {
      Some::gQueueWriterThread->shutdownThread();
      delete Some::gQueueWriterThread;
      Some::gQueueWriterThread = 0;
   }
   if (Some::gQueueReaderThread2)
   {
      Some::gQueueReaderThread2->shutdownThread();
      delete Some::gQueueReaderThread2;
      Some::gQueueReaderThread2 = 0;
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
      Some::gQueueReaderThread2 = new Some::QueueReaderThread2;
      Some::gQueueReaderThread2->launchThread();
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
   if (Some::gQueueReaderThread2) Some::gQueueReaderThread2->showThreadInfo();
   if (Some::gMonitorThread2) Some::gMonitorThread2->showThreadInfo();

   Ris::RandomSleepMs tSleep;
   tSleep.initialize(5000, 500);
   tSleep.doSleep();

   if (Some::gQueueReaderThread2->mQueueReader.mTestFailCount > 0) tRestartFlag = false;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Shutdown program Threads.

   if (Some::gQueueReaderThread2)
   {
      Some::gQueueReaderThread2->shutdownThread();
      delete Some::gQueueReaderThread2;
      Some::gQueueReaderThread2 = 0;
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

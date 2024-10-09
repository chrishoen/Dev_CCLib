#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "someQueueParms.h"
#include "someQueueReaderThread2.h"
#include "someQueueWriterThread.h"
#include "someQueueMonitorThread.h"

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
      Some::gQueueMonitorThread = new Some::QueueMonitorThread;
      Some::gQueueMonitorThread->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Some::gQueueReaderThread2) Some::gQueueReaderThread2->showThreadInfo();
   if (Some::gQueueWriterThread) Some::gQueueWriterThread->showThreadInfo();
   if (Some::gQueueMonitorThread) Some::gQueueMonitorThread->showThreadInfo();


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

   if (Some::gQueueMonitorThread)
   {
      Some::gQueueMonitorThread->shutdownThread();
      delete Some::gQueueMonitorThread;
      Some::gQueueMonitorThread = 0;
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

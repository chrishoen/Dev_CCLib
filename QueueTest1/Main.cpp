#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "someQueueParms.h"
#include "someQueueReaderThread1.h"
#include "someQueueWriterThread.h"
#include "someMonitorThread1.h"

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
      Some::gQueueReaderThread1 = new Some::QueueReaderThread1;
      Some::gQueueReaderThread1->launchThread();
   }
   if (true)
   {
      Some::gQueueWriterThread = new Some::QueueWriterThread;
      Some::gQueueWriterThread->launchThread();
   }
   if (true)
   {
      Some::gMonitorThread1 = new Some::MonitorThread1;
      Some::gMonitorThread1->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Some::gQueueReaderThread1) Some::gQueueReaderThread1->showThreadInfo();
   if (Some::gQueueWriterThread) Some::gQueueWriterThread->showThreadInfo();
   if (Some::gMonitorThread1) Some::gMonitorThread1->showThreadInfo();


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
   if (Some::gQueueWriterThread)
   {
      Some::gQueueWriterThread->shutdownThread();
      delete Some::gQueueWriterThread;
      Some::gQueueWriterThread = 0;
   }
   if (Some::gQueueReaderThread1)
   {
      Some::gQueueReaderThread1->shutdownThread();
      delete Some::gQueueReaderThread1;
      Some::gQueueReaderThread1 = 0;
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

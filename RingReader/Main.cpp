#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "someRingParms.h"
#include "someRingReaderThread.h"
#include "someMonitorThread.h"

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
      Some::gRingReaderThread = new Some::RingReaderThread;
      Some::gRingReaderThread->launchThread();
   }
   if (true)
   {
      Some::gMonitorThread = new Some::MonitorThread;
      Some::gMonitorThread->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Some::gRingReaderThread) Some::gRingReaderThread->showThreadInfo();
   if (Some::gMonitorThread) Some::gMonitorThread->showThreadInfo();


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

   if (Some::gRingReaderThread)
   {
      Some::gRingReaderThread->shutdownThread();
      delete Some::gRingReaderThread;
      Some::gRingReaderThread = 0;
   }

   if (Some::gMonitorThread)
   {
      Some::gMonitorThread->shutdownThread();
      delete Some::gMonitorThread;
      Some::gMonitorThread = 0;
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

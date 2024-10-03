#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "someRingParms.h"
#include "someRingReaderThread1.h"
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
      Some::gRingReaderThread1 = new Some::RingReaderThread1;
      Some::gRingReaderThread1->launchThread();
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
   if (Some::gRingReaderThread1) Some::gRingReaderThread1->showThreadInfo();
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

   if (Some::gRingReaderThread1)
   {
      Some::gRingReaderThread1->shutdownThread();
      delete Some::gRingReaderThread1;
      Some::gRingReaderThread1 = 0;
   }

   if (Some::gMonitorThread1)
   {
      Some::gMonitorThread1->shutdownThread();
      delete Some::gMonitorThread1;
      Some::gMonitorThread1 = 0;
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

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>

#include "MainInit.h"
#include "prnPrint.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "someCallerThread.h"


//******************************************************************************
int main(int argc,char** argv)
{
   //--------------------------------------------------------------------
   // Begin program

   main_initialize(argc,argv);

   //--------------------------------------------------------------------
   // Launch threads

   Some::gCallerThread = new Some::CallerThread;
   Some::gCallerThread->launchThread();

   //--------------------------------------------------------------------
   // Start user command line executive,
   // Wait for user to exit

   CmdLineExec* exec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(exec);
   delete exec;

   //--------------------------------------------------------------------
   // Shutdown threads

   Some::gCallerThread->shutdownThread();
   delete Some::gCallerThread;

   //--------------------------------------------------------------------
   // End program

   main_finalize();
   return 0;
}

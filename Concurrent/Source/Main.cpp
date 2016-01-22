#include "prnPrint.h"
#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

#include "someThread1.h"
#include "GSettings.h"
#include "MainInit.h"

using namespace Some;

//******************************************************************************
int main(int argc,char** argv)
{
   //--------------------------------------------------------------------
   // Initialize

   main_initialize(argc,argv);

   //--------------------------------------------------------------------
   // Launch threads

   gThread1 = new Thread1;
   gThread1->launchThread();

   //--------------------------------------------------------------------
   // Start user command line executive,
   // It returns when user exits

   CmdLineExec* tExec = new CmdLineExec;
   Ris::executeCmdLineConsole(tExec);
   delete tExec;

   //--------------------------------------------------------------------
   // Shutdown threads

   gThread1->shutdownThread();
   delete gThread1;

   //--------------------------------------------------------------------
   // Exit
   
   main_finalize();

   return 0;
}


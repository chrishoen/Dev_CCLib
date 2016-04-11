#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>

#include "MainInit.h"
#include "MainMemory.h"
#include "prnPrint.h"
#include "risCmdLineConsole.h"
#include "GSettings.h"
#include "someThread1.h"

#include "CmdLineExec.h"

void amain_init();


//******************************************************************************
int main(int argc,char** argv)
{
   //--------------------------------------------------------------------
   // Begin program

   main_initialize(argc,argv);
   main_memory_initialize();

   //--------------------------------------------------------------------
   // Launch threads

   if (gGSettings.mMyAppNumber != 1)
   {
      Some::gThread1 = new Some::Thread1;
      Some::gThread1->launchThread();
   }

   //--------------------------------------------------------------------
   // Start user command line executive,
   // Wait for user to exit

   CmdLineExec* tExec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(tExec);
   delete tExec;

   //--------------------------------------------------------------------
   // Shutdown threads

   if (gGSettings.mMyAppNumber != 1)
   {
      Some::gThread1->shutdownThread();
      delete Some::gThread1;
   }

   //--------------------------------------------------------------------
   // End program

   main_memory_finalize();
   main_finalize();
   return 0;
}

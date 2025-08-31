#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"


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
   // Start user command line executive, wait for user to exit.

   CmdLineExec* exec = new CmdLineExec;
   Ris::executeCmdLineConsole(exec);
   delete exec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize program.

   main_finalize();
   return 0;
}


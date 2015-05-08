#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

#include "ccShortTermMemory.h"

void main_initialize();


//******************************************************************************
int main(int argc,char** argv)
{
   //--------------------------------------------------------------------
   // Begin program

   main_initialize();

   Prn::print(0,0,"amain***************************************************BEGIN");
   
   //--------------------------------------------------------------------
   // Start user command line executive,
   // Wait for user to exit

   CmdLineExec* exec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(exec);
   delete exec;

   //--------------------------------------------------------------------
   // End program

   Prn::print(0,0,"amain*****************************************************END");
   return 0;
}
//******************************************************************************
void main_initialize()
{
   // Initialize the message heap
   CC::initializeShortTermMemory(1024);

   // Initialize print filters
   Prn::initializePrint();

   Ris::setConsoleTitle("test");
}


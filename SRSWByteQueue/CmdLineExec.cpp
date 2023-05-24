#include "stdafx.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#include "ccSRSWByteQueue.h"
#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

SRSWByteQueue gQueue;
char gMemory[2000];

CmdLineExec::CmdLineExec()
{
   SRSWByteQueue_initialize(&gQueue, gMemory, 4);
}

void CmdLineExec::reset()
{
   SRSWByteQueue_reset(&gQueue);
   Prn::print(0, "RESET %d", SRSWByteQueue_size(&gQueue));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"))   reset();
   if (aCmd->isCmd("W"))      executeWrite(aCmd);
   if (aCmd->isCmd("R"))      executeRead(aCmd);
   if (aCmd->isCmd("S"))      executeShow(aCmd);

   if (aCmd->isCmd("GO1"))    executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))    executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))    executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))    executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))    executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))    executeGo6(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   char tChar = aCmd->argInt(1);

   if (SRSWByteQueue_tryWrite(&gQueue, tChar))
   {
      Prn::print(0, "WRITE PASS  $$ %d", SRSWByteQueue_size(&gQueue));
   }
   else
   {
      Prn::print(0, "WRITE FAIL  $$ %d", SRSWByteQueue_size(&gQueue));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   char tChar = 0;

   if (SRSWByteQueue_tryRead(&gQueue, &tChar))
   {
      Prn::print(0, "READ PASS   $$ %d %d", SRSWByteQueue_size(&gQueue), (int)tChar);
   }
   else
   {
      Prn::print(0, "READ FAIL   $$ %d", SRSWByteQueue_size(&gQueue));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "SIZE  $$ %d", SRSWByteQueue_size(&gQueue));

   for (int i = 0; i < 5; i++)
   {
      Prn::print(0, "%d %d", i, gQueue.mElement[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   printf("printf\n");
   Prn::print(0, "Prn::print 0");
   Prn::print(Prn::Show1, "Prn::print Prn::Show1");
   Prn::print(Prn::Show2, "Prn::print Prn::Show");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}


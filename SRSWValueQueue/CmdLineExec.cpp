#include "stdafx.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#include "ccSRSWValueQueue.h"
#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CC::SRSWValueQueue<char, 4> gQueue;

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
   gQueue.reset();
   Prn::print(0, "RESET");
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
   if (aCmd->isCmd("P"))      executePut(aCmd);
   if (aCmd->isCmd("G"))      executeGet(aCmd);
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

void CmdLineExec::executePut(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   char tChar = aCmd->argInt(1);

   if (gQueue.tryWrite(tChar))
   {
      Prn::print(0, "WRITE PASS  $$ %d", gQueue.size());
   }
   else
   {
      Prn::print(0, "WRITE FAIL  $$ %d", gQueue.size());
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGet(Ris::CmdLineCmd* aCmd)
{
   char tChar = 0;

   if (gQueue.tryRead(&tChar))
   {
      Prn::print(0, "READ PASS   $$ %d", gQueue.size());
   }
   else
   {
      Prn::print(0, "READ FAIL   $$ %d", gQueue.size());
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "SIZE   $$ %d", gQueue.size());
   Prn::print(0, "PUTI   $$ %d", gQueue.mPutIndex);
   Prn::print(0, "GETI   $$ %d", gQueue.mGetIndex);

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


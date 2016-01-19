#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "SListQueue.h"

#include "CmdLineExec.h"

//******************************************************************************

CmdLineExec::CmdLineExec()
{
   mCount=0;
   SListQueue::initialize(4);
}

//******************************************************************************

void CmdLineExec::reset()
{
   mCount=0;
   SListQueue::initialize(4);
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1  (aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2  (aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3  (aCmd);
   if(aCmd->isCmd("W"      ))  executeWrite(aCmd);
   if(aCmd->isCmd("R"      ))  executeRead(aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   if (SListQueue::tryWrite(++mCount))
   {
      Prn::print(0, "WRITE PASS  $$ %d", mCount);
   }
   else
   {
      Prn::print(0, "WRITE FAIL");
   }
}

//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   int tCount=0;
   if (SListQueue::tryRead(&tCount))
   {
      Prn::print(0, "READ  PASS  $$ %d", tCount);
   }
   else
   {
      Prn::print(0, "READ  FAIL");
   }
}

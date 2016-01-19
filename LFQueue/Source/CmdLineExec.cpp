#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "LFQueue.h"

#include "CmdLineExec.h"

//******************************************************************************

CmdLineExec::CmdLineExec()
{
   mCount=0;
   LFQueue::initialize(4);
}

//******************************************************************************

void CmdLineExec::reset()
{
   mCount=0;
   LFQueue::initialize(4);
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
   mCount++;
   int  tWriteIndex=0;
   bool tStatus = LFQueue::tryStartWrite(&tWriteIndex);

   if (tStatus)
   {
      LFQueue::write(tWriteIndex,mCount);
      LFQueue::finishWrite();
      Prn::print(0, "WRITE PASS  %2d $$ %d", tWriteIndex,mCount);
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
   int  tReadIndex=0;
   bool tStatus = LFQueue::tryStartRead(&tReadIndex);


   if (tStatus)
   {
      LFQueue::read(tReadIndex,&tCount);
      LFQueue::finishRead();
      Prn::print(0, "READ  PASS  %2d $$      %d", tReadIndex,tCount);
   }
   else
   {
      Prn::print(0, "READ  FAIL");
   }
}

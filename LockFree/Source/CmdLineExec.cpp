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
   mStack.initialize(4);
   LFQueue::initialize();
}

//******************************************************************************

void CmdLineExec::reset()
{
   mCount=0;
   mStack.initialize(4);
   LFQueue::initialize();
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1  (aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2  (aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3  (aCmd);
   if(aCmd->isCmd("PUSH"   ))  executePush (aCmd);
   if(aCmd->isCmd("POP"    ))  executePop  (aCmd);
   if(aCmd->isCmd("W"      ))  executeWrite(aCmd);
   if(aCmd->isCmd("R"      ))  executeRead(aCmd);
}

//******************************************************************************

//******************************************************************************

void CmdLineExec::executePush(Ris::CmdLineCmd* aCmd)
{
   bool tStatus = mStack.push(mCount);

   if (tStatus)
   {
      Prn::print(0, "push       %d $$ %d", mStack.mIndex,mCount);
   }
   else
   {
      Prn::print(0, "push FAIL  %d", mStack.mIndex);
   }
   mCount++;
}

//******************************************************************************

void CmdLineExec::executePop(Ris::CmdLineCmd* aCmd)
{
   int tCount=0;
   bool tStatus = mStack.pop(&tCount);

   if (tStatus)
   {
      Prn::print(0, "pop        %d $$      %d", mStack.mIndex,tCount);
   }
   else
   {
      Prn::print(0, "pop  FAIL  %d", mStack.mIndex);
   }
}

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

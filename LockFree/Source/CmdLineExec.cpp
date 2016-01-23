#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "Timing.h"
#include "LFIntQueue.h"
#include "LFBlockQueue.h"

#include "CmdLineExec.h"

//******************************************************************************

CmdLineExec::CmdLineExec()
{
   mCount=0;
   LFIntQueue::initialize(4);
   LFBlockQueue::initialize(4);
}

//******************************************************************************

void CmdLineExec::reset()
{
   for (int i=0;i<100;i++) printf("\n",i);
   mCount=0;
   LFIntQueue::initialize(4);
   LFBlockQueue::initialize(4);
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1        (aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2        (aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3        (aCmd);
   if(aCmd->isCmd("SHOW"   ))  executeShow       (aCmd);
   if(aCmd->isCmd("WI"     ))  executeWriteInt   (aCmd);
   if(aCmd->isCmd("RI"     ))  executeReadInt    (aCmd);
   if(aCmd->isCmd("W"      ))  executeWriteBlock (aCmd);
   if(aCmd->isCmd("R"      ))  executeReadBlock  (aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,3);
   Timing::run1(aCmd->argInt(1));
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   for (int i=4 ; i>=0; --i)
   {
      printf("%d\n",i);
   }
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   LFIntQueue::show();
}

//******************************************************************************

void CmdLineExec::executeWriteInt(Ris::CmdLineCmd* aCmd)
{
   if (LFIntQueue::tryWrite(++mCount))
   {
      Prn::print(0, "WRITE PASS  $$ %d", mCount);
   }
   else
   {
      Prn::print(0, "WRITE FAIL");
   }
}

//******************************************************************************

void CmdLineExec::executeReadInt(Ris::CmdLineCmd* aCmd)
{
   int tCount=0;
   if (LFIntQueue::tryRead(&tCount))
   {
      Prn::print(0, "READ            PASS  $$ %d", tCount);
   }
   else
   {
      Prn::print(0, "READ            FAIL");
   }
}

//******************************************************************************

void CmdLineExec::executeWriteBlock(Ris::CmdLineCmd* aCmd)
{
   mCount++;
   int tNode;

   if (!LFBlockQueue::startWrite(&tNode))
   {
      Prn::print(0, "WRITE FAIL");
      return;
   }

   Prn::print(0, "WRITE PASS  $$ %d", mCount);

   LFBlockQueue::BlockT* tBlock = (LFBlockQueue::BlockT*)LFBlockQueue::element(tNode);
   tBlock->mCode1 = mCount;
   LFBlockQueue::finishWrite(tNode);

}

//******************************************************************************

void CmdLineExec::executeReadBlock(Ris::CmdLineCmd* aCmd)
{
   int tCount=0;
   int tNode;

   if (!LFBlockQueue::startRead(&tNode))
   {
      Prn::print(0, "READ            FAIL");
      return;
   }

   LFBlockQueue::BlockT* tBlock = (LFBlockQueue::BlockT*)LFBlockQueue::element(tNode);
   tCount = tBlock->mCode1;
   LFBlockQueue::finishRead(tNode);

   Prn::print(0, "READ            PASS  $$ %d", tCount);
}

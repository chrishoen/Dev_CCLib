#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "Timing.h"
#include "LFIndex.h"
#include "LFIntQueue.h"

#include "CmdLineExec.h"

using namespace std;

//******************************************************************************

CmdLineExec::CmdLineExec()
{
   mCount=0;
   LFIntQueue::initialize(4);
}

//******************************************************************************

void CmdLineExec::reset()
{
   for (int i=0;i<100;i++) printf("\n",i);
   mCount=0;
   LFIntQueue::initialize(4);
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RES"    ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1        (aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2        (aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3        (aCmd);
   if(aCmd->isCmd("SHOW"   ))  executeShow       (aCmd);
   if(aCmd->isCmd("W"      ))  executeWriteInt   (aCmd);
   if(aCmd->isCmd("R"      ))  executeReadInt    (aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   LFIndex         tX(1,2);
   atomic<LFIndex> tA;
   AtomicLFIndex   tB;

   Prn::print(0,"is_lock_free %d",tA.is_lock_free());
   Prn::print(0,"sizeof %d %d",sizeof(LFIndex),sizeof(AtomicLFIndex));

   AtomicLFIndex   tB1;
   AtomicLFIndex   tB2(tX);
   AtomicLFIndex   tB3(LFIndex(4,5));

   Prn::print(0,"tB1 %d %d",LFIindex(tB1));
   Prn::print(0,"tB2 %d %d",LFIindex(tB2));
   Prn::print(0,"tB3 %d %d",LFIindex(tB3));
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   LFIndex tN1(1,2);
   LFIndex tN2(1,2);

   if (tN1 == tN2)
   {
      return;
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


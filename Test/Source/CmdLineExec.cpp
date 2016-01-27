#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "CmdLineExec.h"

#include "LFIndex.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   LFIndex tY = LFIndex(1,2);
   int tI = tY.mIndex;
   AtomicLFIndex tX;

   tY = tX.load();
   tI = tX.load().mCount;

   Prn::print(0, "MyUnion11 %d %d",
      tY.mIndex,
      tY.mCount);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   LFIndex tY(1,2);
   AtomicLFIndex tX = tY;

   Prn::print(0, "tY %d %d",
      tY.mIndex,
      tY.mCount);

   Prn::print(0, "tX %d %d",
      tX.load().mIndex,
      tX.load().mCount);

   int* tPI = (int*)&tX;
   int& tRI = (int&)*tPI;
   atomic<int>& tARI = (atomic<int>&)*tPI;


   atomic<int>* tAPI1 = (atomic<int>*)&tX;
   atomic<int>& tARI2 = (atomic<int>&)*tAPI1;

   Prn::print(0, "tARI2 %d",tARI2);

   tARI2 = 8;
   Prn::print(0, "tARI2 %d",tARI2);

   Prn::print(0, "tX %d %d",
      tX.load().mIndex,
      tX.load().mCount);
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


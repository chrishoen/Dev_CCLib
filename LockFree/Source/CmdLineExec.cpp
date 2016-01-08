#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "CmdLineExec.h"

//******************************************************************************

CmdLineExec::CmdLineExec()
{
   mCount=0;
   mStack.initialize(4);
}

//******************************************************************************

void CmdLineExec::reset()
{
   mCount=0;
   mStack.initialize(4);
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

LONG my_add101(LONG* aX, LONG aA)
{
    LONG tOriginal;
    LONG tX;
    while (true)
    {
        tX = *aX;
        tOriginal = InterlockedCompareExchange(aX , tX + aA, tX);
        if (tX==tOriginal) break;
    }
    return tOriginal + aA;

}

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
    LONG tY = 100;
    LONG tA = 1;
    Prn::print(0, "%d",my_add101(&tY,tA));
}


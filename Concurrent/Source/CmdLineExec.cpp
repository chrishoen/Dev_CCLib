
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "prnPrint.h"
#include "my_functions.h"

#include "LFFreeList.h"
#include "CmdLineExec.h"

#include "someBlockPoolIndex.h"
#include "someMyBlockC.h"
#include "ccBlockPoolCentral.h"

#include "Timing.h"
#include "someThreads.h"
#include "someShare.h"

using namespace Some;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
// for (int i=0;i<100;i++) printf("\n",i);
   gShare.initialize();
}
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RES"   ))  reset();

   if(aCmd->isCmd("GO1"   ))  executeGo1   (aCmd);
   if(aCmd->isCmd("W"     ))  executeWrite (aCmd);
   if(aCmd->isCmd("R"     ))  executeRead  (aCmd);
   if(aCmd->isCmd("START" ))  executeStart (aCmd);
   if(aCmd->isCmd("STOP"  ))  executeStop  (aCmd);
   if(aCmd->isCmd("X"     ))  executeStop  (aCmd);
   if(aCmd->isCmd("SHOW"  ))  executeShow  (aCmd);
   if(aCmd->isCmd("T1"    ))  executeTime1 (aCmd);
   if(aCmd->isCmd("T2"    ))  executeTime2 (aCmd);
   if(aCmd->isCmd("T8"    ))  executeTime8 (aCmd);
   if(aCmd->isCmd("D1"    ))  executeDelay1(aCmd);
   if(aCmd->isCmd("D2"    ))  executeDelay2(aCmd);


   if(aCmd->isCmd("GO2"   ))  executeGo2   (aCmd);
   if(aCmd->isCmd("GO3"   ))  executeGo3   (aCmd);
   if(aCmd->isCmd("GO4"   ))  executeGo4   (aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

Some::MyBlockC* gC1[100000];

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);
   return;

   for (int i = 0; i < 10; i++)
   {
      gC1[i] = Some::MyBlockC::create();
   }

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);
}

//******************************************************************************

void CmdLineExec::executeTime1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);
   Timing::run1(aCmd->argInt(1));
}

//******************************************************************************

void CmdLineExec::executeTime2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,2);
   Timing::run2(aCmd->argInt(1));
}

//******************************************************************************

void CmdLineExec::executeTime8(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);
   Timing::run8(aCmd->argInt(1));
}

//******************************************************************************

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,100);

   gShare.mWriter[0].write (aCmd->argInt(1));
   gShare.mWriter[0].show();
}

//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,0);

   gShare.mReader.read  (aCmd->argInt(1));
   gShare.mReader.show();
}

//******************************************************************************

void CmdLineExec::executeStart(Ris::CmdLineCmd* aCmd)
{
   gShare.initialize();
   gThreads.start();
}

//******************************************************************************

void CmdLineExec::executeStop(Ris::CmdLineCmd* aCmd)
{
   gThreads.stop();
}

//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   gShare.update();
   gShare.show();
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   for (int i = 0; i < 30; i++)
   {
      Prn::print(0, "rand %d", my_irand(11, 18));
   }
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

void CmdLineExec::executeDelay1(Ris::CmdLineCmd* aCmd)
{
   double tX = aCmd->argDouble(1);
   double y = 791.55*tX - 84.245;
   Prn::print(0, "%8.1f",y);
}

//******************************************************************************
 inline int convertFromUsec(double aDelay)
   {
   }
void CmdLineExec::executeDelay2(Ris::CmdLineCmd* aCmd)
{
   double tX = aCmd->argDouble(1);
      int tN = lround(385.79*tX - 38.827);
      if (tN<0) tN=0;
   Prn::print(0, "%d",tN);
}


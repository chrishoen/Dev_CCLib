#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccShiftRegister.h"
#include "CmdLineExec.h"

using namespace std;

// change201
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
   CC::ShiftRegister tF;
   tF.initialize(4);

   for (int i=0;i<16;i++)
   {
      tF.shiftRight(i*1.0);
   }

   for (int i=0;i<4;i++)
   {
      Prn::print(0,"%3d %8.3f",i,tF.get(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   CC::ShiftRegister tF;
   tF.initialize(4);

   for (int i = 0; i<16; i++)
   {
      tF.shiftRight(11.0 + i*1.0);
      Prn::print(0,"%3d %8.3f %8.3f", i, tF.getLeft(), tF.getRight());
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   CC::ShiftRegister tF;
   tF.initialize(256);

   for (int i = 0; i<1000; i++)
   {
      tF.shiftRight(11.0 + i*1.0);
   }

   for (int i = 0; i<16; i++)
   {
      tF.shiftRight(11.0 + i*1.0);
      Prn::print(0,"%3d %8.3f %8.3f", i, tF.getLeft(), tF.getRight());
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "sizeof(size_t)  %d", (int)sizeof(size_t));
   Prn::print(0, "sizeof(int[10]) %d", (int)sizeof(int[10]));
   Prn::print(0, "sizeof(atomic<int>[10]) %d", (int)sizeof(atomic<int>[10]));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,0.99);

   double tC = aCmd->argDouble(1);
   double tX = (1.0 + tC)/2.0;

   Prn::print(0, "%8.7f %8.7f",tC,tX);
}


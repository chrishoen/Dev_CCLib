#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "CmdLineExec.h"
#include "LLogic.h"

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

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   char tString1[10];
   char tString2[10];
   char tString3[10];

   LLogic tX1(50);
   LLogic tX2(75);

   LLogic tY1 = ~tX2;
   LLogic tY2 = tX1 & tX2;
   LLogic tY3 = tX1 | tX2;;

   Prn::print(0,"%s %s",      tX1.str(tString1),tX2.str(tString2));
   Prn::print(0,"%s %s %s",tY1.str(tString1),tY2.str(tString2),tY3.str(tString3));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   char tString1[10];
   char tString2[10];

   LLogic tX1(25);
   LLogic tX2(75);
   LLogic tY1 = LLogic::cNull;

   Prn::print(0,"%s %s", tX1.str(tString1),tX2.str(tString2));
   Prn::print(0,"%s",tY1.str(tString1));
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   char tString1[10];
   char tString2[10];

   LLogic tX1(25);
   LLogic tX2(75);
   LLogic tY1 = tX1 >> tX2;

   Prn::print(0,"%s %s", tX1.str(tString1),tX2.str(tString2));
   Prn::print(0,"%s",tY1.str(tString1));
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   char tString1[10];

   LLogic tX1(55);
   LLogic tX2(45);
   LLogic tY1 = tX1 %= tX2;
   LLogic tY2 = (tX1 >> tX2) & (tX2 >> tX1);

   Prn::print(0,"X1 %s", tX1.str(tString1));
   Prn::print(0,"X2 %s", tX2.str(tString1));
   Prn::print(0,"Y1 %s", tY1.str(tString1));
   Prn::print(0,"Y2 %s", tY2.str(tString1));
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


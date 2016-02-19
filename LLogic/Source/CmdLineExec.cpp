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
   LLogic tX1(0.50f);
   LLogic tX2(0.750f);

   LLogic tY1 = ~tX2;
   LLogic tY2 = tX1 & tX2;
   LLogic tY3 = tX1 | tX2;;
   LLogic tY4 = tX1 & ~tX2;

   Prn::print(0,"%s %s",      tX1.str(),tX2.str());
   Prn::print(0,"%s %s %s %s",tY1.str(),tY2.str(),tY3.str(),tY4.str());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   LLogic tX1(0.25f);
   LLogic tX2(0.75f);
   LLogic tY1 = LLogic::cNull;

   Prn::print(0,"%s %s", tX1.str(),tX2.str());
   Prn::print(0,"%s",tY1.str());
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   LLogic tX1(0.25f);
   LLogic tX2(0.75f);
   LLogic tY1 = tX1 >> tX2;

   Prn::print(0,"%s %s", tX1.str(),tX2.str());
   Prn::print(0,"%s",tY1.str());
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "risContainers.h"

#include "someClass3.h"
using namespace Some;


#include "CmdLineExec.h"

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

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, 0, "");

   Prn::print(0, 0, "new Class3B");
   Class3B* t3B = new Class3B;
   Prn::print(0, 0, "");

   Prn::print(0, 0, "new Class3A");
   Class3A* t3A = new Class3A;
   Prn::print(0, 0, "");

   Prn::print(0, 0, "delete Class3B");
   delete t3B;
   Prn::print(0, 0, "");

   Prn::print(0, 0, "delete Class3A");
   delete t3A;
   Prn::print(0, 0, "");
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   int tSize=10;
   double* tX = new double[tSize];

   tX[0]=0.0;
   tX[9]=9.0;
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


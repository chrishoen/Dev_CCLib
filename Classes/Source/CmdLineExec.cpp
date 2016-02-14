#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <functional>

#include "prnPrint.h"
#include "risContainers.h"

#include "someClass1.h"
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
   Prn::print(0,"LINE101 new Class3A");
   Prn::print(0,"");
   Class3A* tX1 = new Class3A;
   Prn::print(0,"");

   Prn::print(0,"LINE102 new Class3A[2]");
   Prn::print(0,"");
   Class3A* tX2 = new Class3A[2];
   Prn::print(0,"");

   Prn::print(0,"LINE103 delete Class3A");
   Prn::print(0,"");
   delete tX1;
   Prn::print(0,"");

   Prn::print(0,"LINE104 delete[] Class3A[2]");
   Prn::print(0,"");
   delete[] tX2;
   Prn::print(0,"");

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

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


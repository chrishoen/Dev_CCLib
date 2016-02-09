#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <functional>

#include "prnPrint.h"
#include "risContainers.h"

#include "someClass1.h"
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
   Prn::print(0,"new Class1A");
   Class1A* tX = new Class1A;
   tX->myCall1(101);
   tX->mMyCallPointer1(102);
   tX->mMyCallPointer2(103);

   using namespace std::placeholders;
   std::function<void(int)> tF = std::bind( &Class1A::myCall2, tX, _1); 
   tF(104);

   Prn::print(0,"sizeof1 %d",sizeof(Ris::CallPointer1<int>));
   Prn::print(0,"sizeof2 %d",sizeof(std::function<void(int)>));

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


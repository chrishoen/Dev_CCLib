#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <functional>

#include "prnPrint.h"
#include "risContainers.h"

#include "someClass1.h"
#include "someClass2.h"
#include "someClass3.h"
#include "someMemory.h"
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
   Prn::print(0,"*****************************tX1 new Class3A");
   Prn::print(0,"");
   Class3A* tX1 = new Class3A;
   Prn::print(0,"");

   Prn::print(0,"*****************************tX2 new Class3A[2]");
   Prn::print(0,"");
   Class3A* tX2 = new Class3A[2];
   Prn::print(0,"");

   Prn::print(0,"*****************************delete tX1");
   Prn::print(0,"");
   delete tX1;
   Prn::print(0,"");

   Prn::print(0,"*****************************delete tX2");
   Prn::print(0,"");
   delete[] tX2;
   Prn::print(0,"");

}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"*****************************tX1 new(1) Class3A");
   Prn::print(0,"");
   Class3A* tX1 = new(1) Class3A;
   Prn::print(0,"");

   Prn::print(0,"*****************************tX2 new(1) Class3A[2]");
   Prn::print(0,"");
   Class3A* tX2 = new(1) Class3A[2];
   Prn::print(0,"");

   Prn::print(0,"*****************************delete(tX1,1)");
   Prn::print(0,"");
   Class3A::operator delete(tX1,1);
   Prn::print(0,"");

   Prn::print(0,"*****************************delete[](tX1,1)");
   Prn::print(0,"");
   delete[] tX2;
   return;
   Class3A::operator delete[](tX2,1);
   Prn::print(0,"");
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"*****************************tX1 create Class2A");
   Prn::print(0,"");
   Class2A* tX1 = memCreate<Class2A>(1);
   tX1->method1();
   Prn::print(0,"");

   Prn::print(0,"*****************************tX2 create Class2A");
   Prn::print(0,"");
   Class2A* tX2 = memCreateArray<Class2A>(1,2);
   tX2[0].method1();
   delete[] tX2;
   return;
   Prn::print(0,"");

   Prn::print(0,"*****************************tX1 destroy Class2A");
   Prn::print(0,"");
   memDestroy<Class2A>(tX1,1);
   Prn::print(0,"");

   Prn::print(0,"*****************************tX2 destroy Class2A");
   Prn::print(0,"");
   return;
   free(tX2);
   memDestroyArray<Class2A>(tX2,1,2);
   Prn::print(0,"");
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   char* tBuffer = new char[2 * sizeof(Class2A)];
   Class2A* tX2 = new (tBuffer)Class2A[2];
   tX2[0].method1();
   delete[] tX2;

}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


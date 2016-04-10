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
#include "someClass4.h"
#include "someClass5.h"
#include "someMemory.h"
using namespace Some;


#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   Some::Class4B::mCode1=101;
}
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO11"   ))  executeGo11 (aCmd);
   if(aCmd->isCmd("GO12"   ))  executeGo12 (aCmd);
   if(aCmd->isCmd("GO20"   ))  executeGo20 (aCmd);
   if(aCmd->isCmd("GO21"   ))  executeGo21 (aCmd);
   if(aCmd->isCmd("GO22"   ))  executeGo22 (aCmd);
   if(aCmd->isCmd("GO31"   ))  executeGo31 (aCmd);
   if(aCmd->isCmd("GO32"   ))  executeGo32 (aCmd);
   if(aCmd->isCmd("GO41"   ))  executeGo41 (aCmd);
   if(aCmd->isCmd("GO42"   ))  executeGo42 (aCmd);
   if(aCmd->isCmd("GO43"   ))  executeGo43 (aCmd);
   if(aCmd->isCmd("GO44"   ))  executeGo44 (aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5  (aCmd);
   if(aCmd->isCmd("GO6"    ))  executeGo6  (aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7  (aCmd);
   if(aCmd->isCmd("GO8"    ))  executeGo8  (aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo31(Ris::CmdLineCmd* aCmd)
{
   Class3A* tX1 = new(1)Class3A;
   Class3A::operator delete(tX1,1);
}

//******************************************************************************

void CmdLineExec::executeGo32(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "sizeof(Class3A[2]) %d",sizeof(Class3A[2]));
   Class3A* tX2 = new(1)Class3A[2];
   Class3A::operator delete[](tX2,1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"sizeof5A  %d",sizeof(Class5A));
   Prn::print(0,"sizeof5B  %d",sizeof(Class5B));
   Prn::print(0,"");

   Class5A* t5A = new Class5A();
   t5A->method5A1();


   Class5A::method5AS1();
   Prn::print(0,"");

   Class5B::method5BS1();
   Prn::print(0,"");

   Class5B::method5AS1();
   Prn::print(0,"");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo41(Ris::CmdLineCmd* aCmd)
{
   Class4B* tX = new Class4B;
   tX->method4A();
   tX->method4B();

}

//******************************************************************************

void CmdLineExec::executeGo42(Ris::CmdLineCmd* aCmd)
{
   Class4B* tX = new Class4B;
   testBase4(tX);
   testClass4A(tX);
}

//******************************************************************************

void CmdLineExec::executeGo43(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo44(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo11(Ris::CmdLineCmd* aCmd)
{
   Class1A* tX = new Class1A;
   delete tX;
}

//******************************************************************************

void CmdLineExec::executeGo12(Ris::CmdLineCmd* aCmd)
{
   intializeClass1A();

   gClass1A->function1(101);
   Prn::print(0,"%d",gClass1A->mCode1);

   finalizeClass1A();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo20(Ris::CmdLineCmd* aCmd)
{
   Class2A* tX = new Class2A;
   delete tX;
}

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"*****************************tX1 create Class2A");
   Prn::print(0,"");
   Class2A* tX1 = memCreate<Class2A>(1);
   tX1->method1();
   Prn::print(0,"");

   Prn::print(0,"*****************************tX1 destroy Class2A");
   Prn::print(0,"");
   memDestroy<Class2A>(tX1,1);
   Prn::print(0,"");

}

//******************************************************************************

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"*****************************tX2 create Class2A");
   Prn::print(0,"");
   Class2A* tX2 = memCreateArray<Class2A>(1,2);
   tX2[0].method1();
   Prn::print(0,"");

   Prn::print(0,"*****************************tX2 destroy Class2A");
   Prn::print(0,"");
   memDestroyArray<Class2A>(tX2,1,2);
   Prn::print(0,"");
}

//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   int* tPtr1 = new int;
   int* tPtr2 = new int;

   Prn::print(0,"tPtr1   %llX",tPtr1);
   Prn::print(0,"tPtr2   %llX",tPtr2);
}

//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
}


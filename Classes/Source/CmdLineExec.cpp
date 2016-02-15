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
   if(aCmd->isCmd("GO1"    ))  executeGo1  (aCmd);
   if(aCmd->isCmd("GO21"   ))  executeGo21 (aCmd);
   if(aCmd->isCmd("GO22"   ))  executeGo22 (aCmd);
   if(aCmd->isCmd("GO31"   ))  executeGo31 (aCmd);
   if(aCmd->isCmd("GO32"   ))  executeGo32 (aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4  (aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5  (aCmd);
   if(aCmd->isCmd("GO6"    ))  executeGo6  (aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7  (aCmd);
   if(aCmd->isCmd("GO8"    ))  executeGo8  (aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   intializeClass1A();

   gClass1A->function1(101);
   Prn::print(0,"%d",gClass1A->mCode1);

   finalizeClass1A();
}

//******************************************************************************

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

void CmdLineExec::executeGo31(Ris::CmdLineCmd* aCmd)
{
   Class3A* tX1 = new(1)Class3A;
   Class3A::operator delete(tX1,1);
}

//******************************************************************************

void CmdLineExec::executeGo32(Ris::CmdLineCmd* aCmd)
{
   Class3A* tX2 = new(1)Class3A[2];
   Class3A::operator delete[](tX2,1);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   char* tBuffer1 = new char[(2*sizeof(Class2A))+4];
   void* tBuffer2 = malloc((2*sizeof(Class2A))+4);

   void* tBuffer3 = (void*)tBuffer2;

   Class2A* tX1 = new(tBuffer3) Class2A;
   tX1->method1();

   Prn::print(0,"tBuffer3  %llX",tBuffer3);
   Prn::print(0,"tX1       %llX",tX1);

   free(tX1);
// delete tX1;





}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"sizof  %d",sizeof(Class2A));

   char* tBuffer1 = new char[(2*sizeof(Class2A)) + 4];
   void* tBuffer2 = malloc((2*sizeof(Class2A)) + 4);

   void* tBuffer3 = (void*)tBuffer2;

   Class2A* tX2 = new(tBuffer3) Class2A[2];
   tX2[1].method1();

   Prn::print(0,"tBuffer3  %llX",tBuffer3);
   Prn::print(0,"tX2       %llX",tX2);

// free(tBuffer3);
// delete[] tX2;

   char* tPtr1 = (char*)tX2 - 4;
   void* tPtr2 = (void*)((char*)tX2 - 4);

   Prn::print(0,"tPtr1     %llX",tPtr1);
   Prn::print(0,"tPtr2     %llX",tPtr2);



   free(tPtr2);
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


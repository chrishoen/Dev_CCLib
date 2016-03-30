#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccMemPool.h"
#include "ccMemPoolIndex.h"
#include "someClass1.h"
#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   CC::resetMemPool();
   CC::addBlockPool(1000, sizeof(Some::Class1A),CC::cMemPoolIndex_Class1A);
   CC::initializeMemPool();
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
   Some::Class1A tX1;
   Prn::print(0, "sizeof %d",sizeof(tX1));

   Some::Class1B tX2;
   Prn::print(0, "sizeof %d",sizeof(tX2));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   CC::showMemPool(CC::cMemPoolIndex_Class1A);

   Some::Class1A* t1A = Some::Class1A::allocate();

   CC::showMemPool(CC::cMemPoolIndex_Class1A);

   t1A->method1A();
   t1A->~Class1A();
   t1A->deallocate();

   CC::showMemPool(CC::cMemPoolIndex_Class1A);

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


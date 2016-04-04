#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccBlockPoolCentral.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockA.h"
#include "someMyBlockB.h"
#include "CmdLineExec.h"

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
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

   Some::MyBlockA* t1A = Some::MyBlockA::allocateA();

   t1A->method1A();
   t1A->~MyBlockA();
   t1A->deallocateA();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   Some::MyBlockA* t1A1 = Some::MyBlockA::allocateA();
   Some::MyBlockA* t1A2 = Some::MyBlockA::allocateA();
   Some::MyBlockB* t1B1 = Some::MyBlockB::allocate();
   Some::MyBlockB* t1B2 = Some::MyBlockB::allocate();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   t1A1->deallocateA();
   t1A2->deallocateA();
   Some::MyBlockB::deallocate(t1B1);
   Some::MyBlockB::deallocate(t1B2);

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);
}


//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* t1A1 = Some::MyBlockA::allocateA();
   Some::MyBlockA* t1A2 = (Some::MyBlockA*)CC::BlockHandle::ptr(t1A1->mBlockHandle);

   t1A1->method1A();
   t1A2->method1A();
   t1A1->deallocateA();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);
   int tPoolIndex = aCmd->argInt(1);
   CC::testBlockPool(tPoolIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "sizeofA %d",sizeof(Some::MyBlockA));
   Prn::print(0, "sizeofB %d",sizeof(Some::MyBlockB));
}


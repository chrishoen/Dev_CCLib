#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccBlockPoolList.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockA.h"
#include "someMyBlockB.h"
#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   CC::resetBlockPoolList();
   CC::addToBlockPoolList(1000, sizeof(Some::MyBlockA),Some::cBlockPoolIndex_MyBlockA);
   CC::addToBlockPoolList(1000, sizeof(Some::MyBlockB),Some::cBlockPoolIndex_MyBlockB);
   CC::initializeBlockPoolList();
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
   Prn::print(0, "sizeofA %d",sizeof(Some::MyBlockA));
   Prn::print(0, "sizeofB %d",sizeof(Some::MyBlockB));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

   Some::MyBlockA* t1A = Some::MyBlockA::allocate();

   t1A->method1A();
   t1A->~MyBlockA();
   t1A->deallocate();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   Some::MyBlockA* t1A1 = Some::MyBlockA::allocate();
   Some::MyBlockB* t1B1 = Some::MyBlockB::allocate();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   t1A1->deallocate();
   Some::MyBlockB::deallocate(t1B1);

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* t1A1 = Some::MyBlockA::allocate();
   Some::MyBlockA* t1A2 = (Some::MyBlockA*)CC::getBlockPoolBlockPtr(t1A1->mBlockHandle);

   t1A1->method1A();
   t1A2->method1A();
   t1A1->deallocate();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

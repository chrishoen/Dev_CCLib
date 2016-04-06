#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "prnPrint.h"
#include "ccBlockPoolCentral.h"
#include "ccBlockPoolFreeList.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockA.h"
#include "someMyBlockB.h"
#include "someMyBlockC.h"
#include "someMyBlockD.h"
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
   if(aCmd->isCmd("GO1"    ))  executeGoA1(aCmd);
   if(aCmd->isCmd("A1"     ))  executeGoA1(aCmd);
   if(aCmd->isCmd("A2"     ))  executeGoA2(aCmd);

   if(aCmd->isCmd("B1"     ))  executeGoB1(aCmd);
   if(aCmd->isCmd("B2"     ))  executeGoB2(aCmd);

   if(aCmd->isCmd("C1"     ))  executeGoC1(aCmd);
   if(aCmd->isCmd("C2"     ))  executeGoC2(aCmd);

   if(aCmd->isCmd("D1"     ))  executeGoD1(aCmd);
   if(aCmd->isCmd("D2"     ))  executeGoD2(aCmd);

   if(aCmd->isCmd("T1"     ))  executeGoT1(aCmd);
   if(aCmd->isCmd("T2"     ))  executeGoT2(aCmd);
   if(aCmd->isCmd("T3"     ))  executeGoT3(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoT1(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* tC1 = Some::MyBlockA::create(101);
   Some::MyBlockA* tC2 = (Some::MyBlockA*)CC::getBlockPoolBlockPtr(tC1->mBlockHandle);
   tC1->method1();
   tC2->method1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoT2(Ris::CmdLineCmd* aCmd)
{
   CC::testBlockPool(Some::cBlockPoolIndex_MyBlockA);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoA1(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

   Some::MyBlockA* tC1 = Some::MyBlockA::create(101);
   tC1->method1();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

   tC1->destroy();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoA2(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* tC1 = Some::MyBlockA::create(101);
   Prn::print(0, "%d %d",tC1->mBlockHandle.mPoolIndex,tC1->mBlockHandle.mBlockIndex);

   CC::BlockHandle tBlockHandle = CC::getBlockPoolBlockHandle(tC1);
   Prn::print(0, "%d %d",tBlockHandle.mPoolIndex,tBlockHandle.mBlockIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoB1(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   Some::MyBlockB* t1B1 = Some::MyBlockB::create();
   Some::MyBlockB* t1B2 = Some::MyBlockB::create();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   t1B1->destroy();
   t1B2->destroy();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoB2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoC1(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);

   Some::MyBlockC* tC1 = Some::MyBlockC::create(101);
   tC1->method1();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);

   tC1->destroy();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoC2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoD1(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockD);

   Some::MyBlockD* tD1 = Some::MyBlockD::create();
   Some::MyBlockD* tD2 = Some::MyBlockD::create();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockD);

   tD1->destroy();
   tD2->destroy();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockD);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoD2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoT3(Ris::CmdLineCmd* aCmd)
{
}


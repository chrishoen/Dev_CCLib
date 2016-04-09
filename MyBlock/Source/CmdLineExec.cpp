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
   if(aCmd->isCmd("A3"     ))  executeGoA3(aCmd);
   if(aCmd->isCmd("A4"     ))  executeGoA4(aCmd);

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

void CmdLineExec::executeGoA1(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "GoA1 %d", sizeof(Some::MyBlockA));
   Some::MyBlockA* tX1 = new Some::MyBlockA(101);
   tX1->method1();
   delete tX1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoA2(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

   Some::MyBlockA* tX1 = new Some::MyBlockA(101);
   tX1->method1();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

   delete tX1;

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoA3(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* tX1 = new Some::MyBlockA(101);
   Prn::print(0, "%d %d",tX1->mBlockHandle.mPoolIndex,tX1->mBlockHandle.mBlockIndex);

   CC::BlockHandle tBlockHandle = CC::getBlockPoolBlockHandle(tX1);
   Prn::print(0, "%d %d",tBlockHandle.mPoolIndex,tBlockHandle.mBlockIndex);

   Some::MyBlockA* tX2 = new Some::MyBlockA(102);
   Prn::print(0, "%d %d",tX2->mBlockHandle.mPoolIndex,tX2->mBlockHandle.mBlockIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoA4(Ris::CmdLineCmd* aCmd)
{
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

void CmdLineExec::executeGoT1(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* tX1 = new Some::MyBlockA(101);
   Some::MyBlockA* tX2 = new Some::MyBlockA(101);
   Some::MyBlockA* tX3 = new Some::MyBlockA(101);
   delete tX1;
   delete tX2;
   delete tX3;
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

void CmdLineExec::executeGoT3(Ris::CmdLineCmd* aCmd)
{
}


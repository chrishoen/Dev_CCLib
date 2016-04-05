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
   if(aCmd->isCmd("GOA1"    ))  executeGoA1(aCmd);
   if(aCmd->isCmd("GOA2"    ))  executeGoA2(aCmd);

   if(aCmd->isCmd("GOB1"    ))  executeGoB1(aCmd);
   if(aCmd->isCmd("GOB2"    ))  executeGoB2(aCmd);

   if(aCmd->isCmd("GOC1"    ))  executeGoC1(aCmd);
   if(aCmd->isCmd("GOC2"    ))  executeGoC2(aCmd);
   if(aCmd->isCmd("GOC3"    ))  executeGoC3(aCmd);

   if(aCmd->isCmd("GOT1"    ))  executeGoT1(aCmd);
   if(aCmd->isCmd("GOT2"    ))  executeGoT2(aCmd);
   if(aCmd->isCmd("GOT3"    ))  executeGoT3(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

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

   Some::MyBlockB* t1B1 = Some::MyBlockB::createBlock();
   Some::MyBlockB* t1B2 = Some::MyBlockB::createBlock();

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

   Some::MyBlockC* t1C = Some::MyBlockC::allocateC();

   t1C->method1C();
   t1C->~MyBlockC();
   t1C->deallocateC();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoC2(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   Some::MyBlockC* t1C1 = Some::MyBlockC::allocateC();
   Some::MyBlockC* t1C2 = Some::MyBlockC::allocateC();
   Some::MyBlockB* t1B1 = Some::MyBlockB::createBlock();
   Some::MyBlockB* t1B2 = Some::MyBlockB::createBlock();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   t1C1->deallocateC();
   t1C2->deallocateC();
   t1B1->destroy();
   t1B2->destroy();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);
}

//******************************************************************************

void CmdLineExec::executeGoC3(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockC* t1C1 = Some::MyBlockC::allocateC();
   Some::MyBlockC* t1C2 = (Some::MyBlockC*)CC::BlockHandle::ptr(t1C1->mBlockHandle);

   t1C1->method1C();
   t1C2->method1C();
   t1C1->deallocateC();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockC);
}

//******************************************************************************

void CmdLineExec::executeGoT1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);
   int tPoolIndex = aCmd->argInt(1);
   CC::testBlockPool(tPoolIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoT2(Ris::CmdLineCmd* aCmd)
{
   // Block pool parameters.
   CC::BlockPoolParms tBlockPoolParms;

   // Create block pool.
   tBlockPoolParms.reset();
   tBlockPoolParms.mPoolIndex     = Some::cBlockPoolIndex_MyBlockA;
   tBlockPoolParms.mBlockPoolType = CC::cBlockPoolType_FreeList;
   tBlockPoolParms.mNumBlocks     = 1000;
   tBlockPoolParms.mBlockSize     = sizeof(Some::MyBlockA);

   int tSize = CC::BlockPoolBase::getMemorySize(&tBlockPoolParms);
   Prn::print(0, "Size %d",tSize);

   // Create block pool.
   CC::BlockPoolBase* tBP = new CC::BlockPoolFreeList;
   tBP->initialize(&tBlockPoolParms);
   tBP->finalize();
   delete tBP;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGoT3(Ris::CmdLineCmd* aCmd)
{
}


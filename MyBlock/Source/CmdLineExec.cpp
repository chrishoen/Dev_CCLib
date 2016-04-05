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
   if(aCmd->isCmd("GO11"    ))  executeGo11(aCmd);
   if(aCmd->isCmd("GO12"    ))  executeGo12(aCmd);
   if(aCmd->isCmd("GO21"    ))  executeGo21(aCmd);
   if(aCmd->isCmd("GO22"    ))  executeGo22(aCmd);
   if(aCmd->isCmd("GO23"    ))  executeGo23(aCmd);
   if(aCmd->isCmd("GO24"    ))  executeGo24(aCmd);
   if(aCmd->isCmd("GO25"    ))  executeGo25(aCmd);
   if(aCmd->isCmd("GO26"    ))  executeGo26(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo11(Ris::CmdLineCmd* aCmd)
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

void CmdLineExec::executeGo12(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockC* tC1 = Some::MyBlockC::create(101);
   Prn::print(0, "%d %d",tC1->mBlockHandle.mPoolIndex,tC1->mBlockHandle.mBlockIndex);

   CC::BlockHandle tBlockHandle = CC::getBlockPoolBlockHandle(tC1);
   Prn::print(0, "%d %d",tBlockHandle.mPoolIndex,tBlockHandle.mBlockIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
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

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   Some::MyBlockA* t1A1 = Some::MyBlockA::allocateA();
   Some::MyBlockA* t1A2 = Some::MyBlockA::allocateA();
   Some::MyBlockB* t1B1 = Some::MyBlockB::createBlock();
   Some::MyBlockB* t1B2 = Some::MyBlockB::createBlock();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);

   t1A1->deallocateA();
   t1A2->deallocateA();
   t1B1->destroy();
   t1B2->destroy();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockB);
}


//******************************************************************************

void CmdLineExec::executeGo23(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* t1A1 = Some::MyBlockA::allocateA();
   Some::MyBlockA* t1A2 = (Some::MyBlockA*)CC::BlockHandle::ptr(t1A1->mBlockHandle);

   t1A1->method1A();
   t1A2->method1A();
   t1A1->deallocateA();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
}

//******************************************************************************

void CmdLineExec::executeGo24(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);
   int tPoolIndex = aCmd->argInt(1);
   CC::testBlockPool(tPoolIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo25(Ris::CmdLineCmd* aCmd)
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

void CmdLineExec::executeGo26(Ris::CmdLineCmd* aCmd)
{
}


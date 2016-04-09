#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "prnPrint.h"
#include "ccBlockPoolCentral.h"
#include "ccSharedMemory.h"
#include "ccSharedSynch.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockA.h"
#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
  mCount = 0;
}

//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"     ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"     ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"     ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"     ))  executeGo4(aCmd);

   if(aCmd->isCmd("I"       ))  executeTxInt(aCmd);
   if(aCmd->isCmd("B"       ))  executeTxBlock(aCmd);
   if(aCmd->isCmd("C"       ))  executeCreate(aCmd);
   if(aCmd->isCmd("D"       ))  executeDestroy(aCmd);
   if(aCmd->isCmd("S"       ))  executeShow(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTxInt(Ris::CmdLineCmd* aCmd)
{
   CC::gSharedSynch.mIntQueue.tryWrite(++mCount);
   CC::gSharedSynch.putSemaphore();
   Prn::print(0, "IntQueue         write %d",mCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTxBlock(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* tBlock = new Some::MyBlockA(++mCount);

   CC::gSharedSynch.mBlockHandleQueue.tryWrite(tBlock->mBlockHandle);
   CC::gSharedSynch.putSemaphore();
   Prn::print(0, "BlockHandleQueue write %d",mCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

   Some::MyBlockA* tC1 = new Some::MyBlockA(101);
   tC1->method1();

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);

   delete tC1;

   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlockA* tC1 = new Some::MyBlockA(101);
   Prn::print(0, "%d %d",tC1->mBlockHandle.mPoolIndex,tC1->mBlockHandle.mBlockIndex);

   CC::BlockHandle tBlockHandle = CC::getBlockPoolBlockHandle(tC1);
   Prn::print(0, "%d %d",tBlockHandle.mPoolIndex,tBlockHandle.mBlockIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeCreate(Ris::CmdLineCmd* aCmd)
{
   mMyBlockA = new Some::MyBlockA(101);
}

void CmdLineExec::executeDestroy(Ris::CmdLineCmd* aCmd)
{
   delete mMyBlockA;
}

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyBlockA);
}



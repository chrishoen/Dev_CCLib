#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccMemPool.h"
#include "ccMemPoolIndex.h"
#include "someMyBlock.h"
#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   CC::resetMemPool();
   CC::addBlockPool(1000, sizeof(Some::MyBlock),CC::cMemPoolIndex_MyBlock);
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
   Some::MyBlock tX1;
   Prn::print(0, "sizeof %d",sizeof(tX1));

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   CC::showMemPool(CC::cMemPoolIndex_MyBlock);

   Some::MyBlock* t1A = Some::MyBlock::allocate();

   t1A->method1A();
   t1A->~MyBlock();
   t1A->deallocate();

   CC::showMemPool(CC::cMemPoolIndex_MyBlock);

}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   CC::showMemPool(CC::cMemPoolIndex_MyBlock);

   Some::MyBlock* t1A1 = Some::MyBlock::allocate();
   Some::MyBlock* t1A2 = Some::MyBlock::allocate();

   CC::showMemPool(CC::cMemPoolIndex_MyBlock);

   t1A1->deallocate();
   t1A2->deallocate();

   CC::showMemPool(CC::cMemPoolIndex_MyBlock);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlock* t1A1 = Some::MyBlock::allocate();
   Some::MyBlock* t1A2 = (Some::MyBlock*)CC::getMemPoolBlockPtr(t1A1->mMemHandle);

   t1A1->method1A();
   t1A2->method1A();
   t1A1->deallocate();

   CC::showMemPool(CC::cMemPoolIndex_MyBlock);
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


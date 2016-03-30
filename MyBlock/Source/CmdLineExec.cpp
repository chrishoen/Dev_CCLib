#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccBlockPoolList.h"
#include "ccBlockPoolIndex.h"
#include "someMyBlock.h"
#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   CC::resetBlockPoolList();
   CC::addToBlockPoolList(1000, sizeof(Some::MyBlock),CC::cBlockPoolIndex_MyBlock);
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
   Some::MyBlock tX1;
   Prn::print(0, "sizeof %d",sizeof(tX1));

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(CC::cBlockPoolIndex_MyBlock);

   Some::MyBlock* t1A = Some::MyBlock::allocate();

   t1A->method1A();
   t1A->~MyBlock();
   t1A->deallocate();

   CC::showBlockPool(CC::cBlockPoolIndex_MyBlock);

}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(CC::cBlockPoolIndex_MyBlock);

   Some::MyBlock* t1A1 = Some::MyBlock::allocate();
   Some::MyBlock* t1A2 = Some::MyBlock::allocate();

   CC::showBlockPool(CC::cBlockPoolIndex_MyBlock);

   t1A1->deallocate();
   t1A2->deallocate();

   CC::showBlockPool(CC::cBlockPoolIndex_MyBlock);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Some::MyBlock* t1A1 = Some::MyBlock::allocate();
   Some::MyBlock* t1A2 = (Some::MyBlock*)CC::getBlockPoolBlockPtr(t1A1->mBlockHandle);

   t1A1->method1A();
   t1A2->method1A();
   t1A1->deallocate();

   CC::showBlockPool(CC::cBlockPoolIndex_MyBlock);
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


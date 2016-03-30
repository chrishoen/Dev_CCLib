#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccBlockPoolList.h"
#include "someBlockPoolIndex.h"
#include "someMyTreeBlock.h"
#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   CC::resetBlockPoolList();
   CC::addToBlockPoolList(1000, sizeof(Some::MyTreeBlock),Some::cBlockPoolIndex_MyTreeBlock);
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
   Some::MyTreeBlock tX1;
   Prn::print(0, "sizeof %d",sizeof(tX1));

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   Some::MyTreeBlock* t1A = Some::MyTreeBlock::allocate();

   t1A->method1A();
   t1A->~MyTreeBlock();
   t1A->deallocate();

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   Some::MyTreeBlock* t1A1 = Some::MyTreeBlock::allocate();
   Some::MyTreeBlock* t1A2 = Some::MyTreeBlock::allocate();

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   t1A1->deallocate();
   t1A2->deallocate();

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Some::MyTreeBlock* t1A1 = Some::MyTreeBlock::allocate();
   Some::MyTreeBlock* t1A2 = (Some::MyTreeBlock*)CC::getBlockPoolBlockPtr(t1A1->mBlockHandle);

   t1A1->method1A();
   t1A2->method1A();
   t1A1->deallocate();

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


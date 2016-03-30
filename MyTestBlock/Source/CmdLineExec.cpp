#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccBlockPoolList.h"
#include "someBlockPoolIndex.h"
#include "someMyTestBlock.h"
#include "someGenerateMyTestBlocks.h"
#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   CC::resetBlockPoolList();
   CC::addToBlockPoolList(1000, sizeof(Some::MyTestBlock),Some::cBlockPoolIndex_MyTestBlock);
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

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,2);

   CC::showBlockPool(Some::cBlockPoolIndex_MyTestBlock);

   Some::MyTestBlock* tRootNode = Some::MyTestBlock::create(1);

   if (aCmd->argInt(1) == 1)
   {
      Some::generateMyTestBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      Some::generateMyTestBlocks2(tRootNode);
   }

   CC::showBlockPool(Some::cBlockPoolIndex_MyTestBlock);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Some::MyTestBlock* tRootNode = Some::MyTestBlock::create(1);
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


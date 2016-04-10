#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeDestroyer.h"
#include "ccBlockPoolCentral.h"
#include "someBlockPoolIndex.h"
#include "someMyTreeBlock.h"
#include "someGenerateMyTreeBlocks.h"
#include "someMyTreeBlockVisitor.h"
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
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
   Some::MyTreeBlock* tRootNode = new Some::MyTreeBlock(999);
   Some::generateMyTreeBlocks1(tRootNode);
   Some::printAllMyTreeBlocksCO(tRootNode);

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
// CC::destroyAllTreeNodes(tRootNode);
   Some::destroyAllMyTreeBlocks(tRootNode);
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   Some::MyTreeBlock* tRootNode = new Some::MyTreeBlock(1);

   if (aCmd->argInt(1) == 1)
   {
      Some::generateMyTreeBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      Some::generateMyTreeBlocks2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      Some::generateMyTreeBlocks3(tRootNode);
   }

   Some::printAllMyTreeBlocksCO(tRootNode);
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   Some::MyTreeBlock* tRootNode = new Some::MyTreeBlock(0);
   generateMyTreeBlocks1(tRootNode);

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   if (aCmd->argInt(1) == 1)
   {
      Some::printAllMyTreeBlocksCO(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      Some::printAllMyTreeBlocksDO(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      Some::printAllMyTreeBlocksVN(tRootNode);
   }
   else if (aCmd->argInt(1) == 4)
   {
      Some::destroyAllMyTreeBlocks(tRootNode);
   }
   else if (aCmd->argInt(1) == 5)
   {
      CC::destroyAllTreeNodes(tRootNode);
   }

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   Some::MyTreeBlock* tX1 = new Some::MyTreeBlock(1000);
   Some::MyTreeBlock* tX2 = new Some::MyTreeBlock(1000);
   CC::TreeNode* tY2 = tX2;

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   delete tX1;
   delete tY2;

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   Some::MyTreeBlock* tRootNode = new Some::MyTreeBlock(1000);

   Some::MyTreeBlock* tRootNode1 = 0;

   tRootNode1 = new Some::MyTreeBlock(2000);
   Some::generateMyTreeBlocks1(tRootNode1);
   Some::printAllMyTreeBlocksCO(tRootNode1);
   Some::printAllMyTreeBlocksCO(tRootNode1);
   return;
   printf("MMMMMMMMMMMM\n");
   tRootNode->attachAfterLastChild(tRootNode1);

   Some::printAllMyTreeBlocksCO(tRootNode);
}


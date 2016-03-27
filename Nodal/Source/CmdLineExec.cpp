#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "ccTreeNode.h"
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeDestroyer.h"
#include "someNodeBlock.h"
#include "someNodeBlockVisitor.h"
#include "someGenerateBlocks.h"

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   Some::NodeBlock::initializeShortTermBlockPool(1000);
}
//******************************************************************************
void CmdLineExec::reset()
{
   mRootNode = new Some::NodeBlock(0);

   Some::generateBlocks1(mRootNode);
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
   if(aCmd->isCmd("GO6"    ))  executeGo6(aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,2);

   Some::NodeBlock* tRootNode = new Some::NodeBlock(0);

   if (aCmd->argInt(1) == 1)
   {
      Some::generateBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      Some::generateBlocks2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      Some::generateBlocks3(tRootNode);
   }

   Some::printAllNodeBlocks3(tRootNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);

   Some::NodeBlock* tRootNode = new Some::NodeBlock(0);
   Some::generateBlocks3(tRootNode);

   if (aCmd->argInt(1) == 1)
   {
      Some::printAllNodeBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      Some::printAllNodeBlocks2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      Some::printAllNodeBlocks3(tRootNode);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);

   Some::NodeBlock::mBlockPool.show();

   Some::NodeBlock* tRootNode = Some::NodeBlock::create(0);
   Some::generateBlocks2(tRootNode);

   Some::NodeBlock::mBlockPool.show();

   if (aCmd->argInt(1) == 1)
   {
      Some::printAllNodeBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      Some::printAllNodeBlocks2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      Some::printAllNodeBlocks3(tRootNode);
   }
   else if (aCmd->argInt(1) == 4)
   {
      Some::destroyAllNodeBlocks(tRootNode);
   }
   else if (aCmd->argInt(1) == 5)
   {
      CC::destroyAllTreeNodes(tRootNode);
   }

   Some::NodeBlock::mBlockPool.show();
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

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   printf("**********************************go5\n");
   printf("**********************************go5\n");
   printf("**********************************go5\n");
   printf("\n");

   Some::NodeBlock* tRootNode = new Some::NodeBlock(0);

   printf("**********************************Some::generateBlocks1(tRootNode1)\n");
   Some::NodeBlock* tRootNode1 = new Some::NodeBlock(0);
   Some::generateBlocks1(tRootNode1);

   printf("**********************************Some::generateBlocks1(tRootNode2)\n");
   Some::NodeBlock* tRootNode2 = new Some::NodeBlock(0);
   Some::generateBlocks1(tRootNode2);

   printf("**********************************attachAfterLastChild(tRootNode1)\n");
   tRootNode->attachAfterLastChild(tRootNode1);

   printf("**********************************attachAfterLastChild(tRootNode2\n");
   tRootNode->attachAfterLastChild(tRootNode2);

   printf("**********************************printAllNodeBlocks1(mRootNode)\n");
   Some::printAllNodeBlocks1(tRootNode);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
}
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "ccTreeNode.h"
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeDestroyer.h"
#include "someMyTreeBlock.h"
#include "someMyTreeBlockVisitor.h"
#include "someMyTreeBlockChannel.h"
#include "ccTreeNodeTxQueue.h"
#include "ccTreeNodeRxQueue.h"
#include "someGenerateMyTreeBlocks.h"

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
   mRootNode = Some::MyTreeBlock::create(0);

   Some::generateMyTreeBlocks1(mRootNode);
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

   Some::MyTreeBlock* tRootNode = Some::MyTreeBlock::create(0);

   if (aCmd->argInt(1) == 1)
   {
      generateMyTreeBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      generateMyTreeBlocks2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      generateMyTreeBlocks3(tRootNode);
   }

   Some::printAllMyTreeBlocksVN(tRootNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);

   Some::MyTreeBlock* tRootNode = Some::MyTreeBlock::create(0);
   generateMyTreeBlocks3(tRootNode);

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

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);

   Some::MyTreeBlock* tRootNode = Some::MyTreeBlock::create(0);
   generateMyTreeBlocks2(tRootNode);


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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   //---------------------------------------------------------------------------
   aCmd->setArgDefault(1,3);
   int tStage = aCmd->argInt(1);

   printf("**********************************go4\n");
   printf("**********************************go4\n");
   printf("**********************************go4\n");
   printf("\n");


   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   CC::TreeNodeTxQueue<Some::MyTreeBlock> tTxQueue;
   CC::TreeNodeRxQueue<Some::MyTreeBlock> tRxQueue;

   Some::MyTreeBlock* tRootNode1 = Some::MyTreeBlock::create(1000);
   Some::MyTreeBlock* tRootNode2 = Some::MyTreeBlock::create(2000);
   Some::MyTreeBlock* tRootNode3 = Some::MyTreeBlock::create(3000);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   if (tStage >= 1)
   {
      printf("**********************************generateMyTreeBlocks1(tRootNode1)\n");
      generateMyTreeBlocks3(tRootNode1);
   }

   if (tStage >= 2)
   {
      printf("**********************************generateMyTreeBlocks1(tRootNode2)\n");
      generateMyTreeBlocks3(tRootNode2);
   }

   if (tStage >= 3)
   {
      printf("**********************************generateMyTreeBlocks1(tRootNode3)\n");
      generateMyTreeBlocks3(tRootNode3);
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   if (tStage >= 1)
   {
      printf("**********************************tTxQueue.putTxNode(tRootNode1)\n");
      tTxQueue.putTxNode(tRootNode1);
   }

   if (tStage >= 2)
   {
      printf("**********************************tTxQueue.putTxNode(tRootNode2)\n");
      tTxQueue.putTxNode(tRootNode2);
   }

   if (tStage >= 3)
   {
      printf("**********************************tTxQueue.putTxNode(tRootNode3)\n");
      tTxQueue.putTxNode(tRootNode3);
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   printf("**********************************printMyTreeBlockTxQueue\n");
   printf("\n");
   Some::printMyTreeBlockTxQueue(&tTxQueue);
   printf("\n");

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   printf("**********************************transferMyTreeBlockQueues\n");
   Some::transferMyTreeBlockQueues(&tTxQueue, &tRxQueue);
   printf("\n");

   printf("**********************************printMyTreeBlockRxQueue\n");
   Some::printMyTreeBlockRxQueue(&tRxQueue);
   printf("\n");
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

   Some::MyTreeBlock* tRootNode = Some::MyTreeBlock::create(0);

   printf("**********************************generateMyTreeBlocks1(tRootNode1)\n");
   Some::MyTreeBlock* tRootNode1 = Some::MyTreeBlock::create(0);
   generateMyTreeBlocks1(tRootNode1);

   printf("**********************************generateMyTreeBlocks1(tRootNode2)\n");
   Some::MyTreeBlock* tRootNode2 = Some::MyTreeBlock::create(0);
   generateMyTreeBlocks1(tRootNode2);

   printf("**********************************attachAfterLastChild(tRootNode1)\n");
   tRootNode->attachAfterLastChild(tRootNode1);

   printf("**********************************attachAfterLastChild(tRootNode2\n");
   tRootNode->attachAfterLastChild(tRootNode2);

   printf("**********************************printAllMyTreeBlocksCO(mRootNode)\n");
   Some::printAllMyTreeBlocksCO(tRootNode);
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
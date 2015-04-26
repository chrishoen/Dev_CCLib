#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "ccTreeNode.h"
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeDestroyer.h"
#include "ccNodeBlock.h"
#include "ccNodeBlockVisitor.h"
#include "ccNodeBlockChannel.h"
#include "ccTreeNodeTxQueue.h"
#include "ccTreeNodeRxQueue.h"
#include "GenerateNodeBlocks.h"

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   CC::NodeBlock::initializeShortTermBlockPool(1000);
}
//******************************************************************************
void CmdLineExec::reset()
{
   mRootNode = new CC::NodeBlock(0);

   generateTreeNodes1(mRootNode);
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

   CC::NodeBlock* tRootNode = new CC::NodeBlock(0);

   if (aCmd->argInt(1) == 1)
   {
      generateTreeNodes1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      generateTreeNodes2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      generateTreeNodes3(tRootNode);
   }

   CC::printAllNodeBlocks3(tRootNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);

   CC::NodeBlock* tRootNode = new CC::NodeBlock(0);
   generateTreeNodes3(tRootNode);

   if (aCmd->argInt(1) == 1)
   {
      CC::printAllNodeBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      CC::printAllNodeBlocks2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      CC::printAllNodeBlocks3(tRootNode);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);

   CC::NodeBlock::mBlockPool.show();

   CC::NodeBlock* tRootNode = CC::NodeBlock::create(0);
   generateTreeNodes2(tRootNode);

   CC::NodeBlock::mBlockPool.show();

   if (aCmd->argInt(1) == 1)
   {
      CC::printAllNodeBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      CC::printAllNodeBlocks2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      CC::printAllNodeBlocks3(tRootNode);
   }
   else if (aCmd->argInt(1) == 4)
   {
      CC::destroyAllNodeBlocks(tRootNode);
   }
   else if (aCmd->argInt(1) == 5)
   {
      CC::destroyAllTreeNodes(tRootNode);
   }

   CC::NodeBlock::mBlockPool.show();
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

   CC::TreeNodeTxQueue<CC::NodeBlock> tTxQueue;
   CC::TreeNodeRxQueue<CC::NodeBlock> tRxQueue;

   CC::NodeBlock* tRootNode1 = new CC::NodeBlock(1000);
   CC::NodeBlock* tRootNode2 = new CC::NodeBlock(2000);
   CC::NodeBlock* tRootNode3 = new CC::NodeBlock(3000);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   if (tStage >= 1)
   {
      printf("**********************************generateTreeNodes1(tRootNode1)\n");
      generateTreeNodes3(tRootNode1);
   }

   if (tStage >= 2)
   {
      printf("**********************************generateTreeNodes1(tRootNode2)\n");
      generateTreeNodes3(tRootNode2);
   }

   if (tStage >= 3)
   {
      printf("**********************************generateTreeNodes1(tRootNode3)\n");
      generateTreeNodes3(tRootNode3);
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

   printf("**********************************printNodeBlockTxQueue\n");
   printf("\n");
   CC::printNodeBlockTxQueue(&tTxQueue);
   printf("\n");

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   printf("**********************************transferNodeBlockQueues\n");
   CC::transferNodeBlockQueues(&tTxQueue, &tRxQueue);
   printf("\n");

   printf("**********************************printNodeBlockRxQueue\n");
   CC::printNodeBlockRxQueue(&tRxQueue);
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

   CC::NodeBlock* tRootNode = new CC::NodeBlock(0);

   printf("**********************************generateTreeNodes1(tRootNode1)\n");
   CC::NodeBlock* tRootNode1 = new CC::NodeBlock(0);
   generateTreeNodes1(tRootNode1);

   printf("**********************************generateTreeNodes1(tRootNode2)\n");
   CC::NodeBlock* tRootNode2 = new CC::NodeBlock(0);
   generateTreeNodes1(tRootNode2);

   printf("**********************************attachAfterLastChild(tRootNode1)\n");
   tRootNode->attachAfterLastChild(tRootNode1);

   printf("**********************************attachAfterLastChild(tRootNode2\n");
   tRootNode->attachAfterLastChild(tRootNode2);

   printf("**********************************printAllNodeBlocks1(mRootNode)\n");
   CC::printAllNodeBlocks1(tRootNode);
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
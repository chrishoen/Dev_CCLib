#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "ccTreeNode.h"
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeDestroyer.h"
#include "ccLabelledTreeNode.h"
#include "ccLabelledTreeNodeVisitor.h"
#include "ccLabelledTreeNodeChannel.h"
#include "ccTreeNodeTxQueue.h"
#include "ccTreeNodeRxQueue.h"
#include "someBlock1.h"
#include "someBlock2.h"
#include "GenerateTreeNodes.h"

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   Some::Block2A::initializeBlockUniverse(1000,1000);
   Some::Block2B::initializeBlockUniverse(1000,1000);

   CC::LabelledTreeNode::initializeBlockUniverse(1000,1000);
   CC::LabelledTreeNode::mDefaultMemoryType = CC::MemoryType_ShortTerm;
}
//******************************************************************************
void CmdLineExec::reset()
{
   mRootNode = new CC::LabelledTreeNode(0,"root");

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
   aCmd->setArgDefault(1,4);

   CC::LabelledTreeNode* tRootNode = new CC::LabelledTreeNode(0,"root");
   generateTreeNodes2(tRootNode);

   if (aCmd->argInt(1) == 1)
   {
      CC::printAllLabelledTreeNodes1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      CC::printAllLabelledTreeNodes2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      CC::printAllLabelledTreeNodes3(tRootNode);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);

   CC::LabelledTreeNode::mBlockUniverse.show("CC::LabelledTreeNode::mBlockUniverse1");

   CC::LabelledTreeNode* tRootNode = CC::LabelledTreeNode::create(0,"root");
   generateTreeNodes2(tRootNode);

   CC::LabelledTreeNode::mBlockUniverse.show("CC::LabelledTreeNode::mBlockUniverse2");

   if (aCmd->argInt(1) == 1)
   {
      CC::printAllLabelledTreeNodes1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      CC::printAllLabelledTreeNodes2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      CC::printAllLabelledTreeNodes3(tRootNode);
   }
   else if (aCmd->argInt(1) == 4)
   {
      CC::destroyAllLabelledTreeNodes(tRootNode);
   }
   else if (aCmd->argInt(1) == 5)
   {
      CC::destroyAllTreeNodes(tRootNode);
   }

   CC::LabelledTreeNode::mBlockUniverse.show("CC::LabelledTreeNode::mBlockUniverse3");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   CC::printAllLabelledTreeNodes1(mRootNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   CC::TreeNodeTxQueue<CC::LabelledTreeNode> tTxQueue;
   CC::TreeNodeRxQueue<CC::LabelledTreeNode> tRxQueue;

   printf("tTxQueue.putTxNode********************\n");
   tTxQueue.putTxNode(mRootNode);

   printf("tTxQueue.putRxNode********************BEGIN\n");

   while (true)
   {
      CC::LabelledTreeNode* tTxNode = tTxQueue.getNextTxNode();
      if (tTxNode != 0)
      {
         CC::LabelledTreeNode* tRxNode = new CC::LabelledTreeNode(tTxNode->mIdentifier, tTxNode->mLabel);
         tRxNode->mTreeNodeTxFlags = tTxNode->mTreeNodeTxFlags;
         tRxQueue.putRxNode(tRxNode);
      }
      else
      {
         break;
      }
   }

   printf("tTxQueue.putRxNode********************END\n");

   printf("tTxQueue.getRxNode********************************BEGIN\n");
   while (true)
   {
      CC::LabelledTreeNode* tRxNode = tRxQueue.getNextRxNode();
      if (tRxNode != 0)
      {
         CC::printAllLabelledTreeNodes1(tRxNode);
//       printf("LINE201 %d %d\n",tRxNode->mTreeNodeTxFlags.mIsLastInStructure,tRxNode->mIdentifier);
      }
      else
      {
         break;
      }
   }
   printf("tTxQueue.getRxNode********************************END\n");
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

   CC::TreeNodeTxQueue<CC::LabelledTreeNode> tTxQueue;
   CC::TreeNodeRxQueue<CC::LabelledTreeNode> tRxQueue;

   tTxQueue.mRootNode->setFullPath("TxRoot");
   tRxQueue.mRootNode->setFullPath("RxRoot");

   printf("**********************************generateTreeNodes1(tRootNode1)\n");
   CC::LabelledTreeNode* tRootNode1 = new CC::LabelledTreeNode(0,"root1");
   generateTreeNodes1(tRootNode1);

   printf("**********************************tTxQueue.putTxNode(tRootNode1)\n");

   tTxQueue.putTxNode(tRootNode1);

   printf("**********************************transferLabelledTreeNodeQueues\n");
   CC::transferLabelledTreeNodeQueues(&tTxQueue, &tRxQueue);
   return;
   printf("**********************************printLabelledTreeNodeRxQueue\n");
   CC::printLabelledTreeNodeRxQueue(&tRxQueue);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   printf("**********************************go6\n");
   printf("**********************************go6\n");
   printf("**********************************go6\n");
   printf("\n");

   CC::TreeNodeTxQueue<CC::LabelledTreeNode> tTxQueue;
   CC::TreeNodeRxQueue<CC::LabelledTreeNode> tRxQueue;

   tTxQueue.mRootNode->setLabel("TxRoot");
   tRxQueue.mRootNode->setLabel("RxRoot");
   tTxQueue.mRootNode->setFullPath("TxRoot");
   tRxQueue.mRootNode->setFullPath("RxRoot");

   printf("**********************************generateTreeNodes1(tRootNode1)\n");
   CC::LabelledTreeNode* tRootNode1 = new CC::LabelledTreeNode(0,"root1");
   generateTreeNodes1(tRootNode1);

   printf("**********************************generateTreeNodes1(tRootNode2)\n");
   CC::LabelledTreeNode* tRootNode2 = new CC::LabelledTreeNode(0,"root2");
   generateTreeNodes1(tRootNode2);

#if 1
   printf("**********************************tTxQueue.putTxNode(tRootNode1)\n");
   tTxQueue.putTxNode(tRootNode1);
#endif
#if 0
   printf("**********************************tTxQueue.putTxNode(tRootNode2)\n");
   tTxQueue.putTxNode(tRootNode2);
#endif
   printf("**********************************transferLabelledTreeNodeQueues\n");
   CC::transferLabelledTreeNodeQueues(&tTxQueue, &tRxQueue);
   return;
   printf("**********************************printLabelledTreeNodeRxQueue\n");
   CC::printLabelledTreeNodeRxQueue(&tRxQueue);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
   printf("**********************************go7\n");
   printf("**********************************go7\n");
   printf("**********************************go7\n");
   printf("\n");

   CC::LabelledTreeNode* tRootNode = new CC::LabelledTreeNode(0,"troot");

   printf("**********************************generateTreeNodes1(tRootNode1)\n");
   CC::LabelledTreeNode* tRootNode1 = new CC::LabelledTreeNode(0,"root1");
   generateTreeNodes1(tRootNode1);

   printf("**********************************generateTreeNodes1(tRootNode2)\n");
   CC::LabelledTreeNode* tRootNode2 = new CC::LabelledTreeNode(0,"root2");
   generateTreeNodes1(tRootNode2);

   printf("**********************************attachAfterLastChild(tRootNode1)\n");
   tRootNode->attachAfterLastChild(tRootNode1);

   printf("**********************************attachAfterLastChild(tRootNode2\n");
   tRootNode->attachAfterLastChild(tRootNode2);

   printf("**********************************printAllLabelledTreeNodes1(mRootNode)\n");
   CC::printAllLabelledTreeNodes1(tRootNode);
}
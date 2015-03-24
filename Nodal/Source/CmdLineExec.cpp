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

   tTxQueue.putTxNode(mRootNode);

   while (true)
   {
      CC::LabelledTreeNode* tTxNode = tTxQueue.getNextTxNode();
      if (tTxNode != 0)
      {
         CC::LabelledTreeNode* tRxNode = new CC::LabelledTreeNode(tTxNode->mIdentifier, tTxNode->mLabel);
         tRxQueue.putRxNode(tRxNode);
      }
      else
      {
         break;
      }
   }

   while (true)
   {
      CC::LabelledTreeNode* tRxNode = tRxQueue.getNextRxNode();
      if (tRxNode != 0)
      {
         printf("LINE201 %d\n",tRxNode->mIdentifier);
      }
      else
      {
         break;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}
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

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   Some::Block2A::initializeBlockUniverse(1000,1000);
   Some::Block2B::initializeBlockUniverse(1000,1000);

   CC::LabelledTreeNode::initializeBlockUniverse(1000,1000);
   CC::LabelledTreeNode::mDefaultMemoryType = CC::MemoryType_LongTerm;
   CC::LabelledTreeNode::mDefaultMemoryType = CC::MemoryType_ShortTerm;
}
//******************************************************************************
void CmdLineExec::reset()
{
   mRootNode = new CC::LabelledTreeNode(0,"root");
   CC::TreeNode* tNode = 0;

   tNode = new CC::LabelledTreeNode(1, "node1");
   mRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(2, "node2");
   mRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(21, "node21");
   mRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(22, "node22");
   mRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(221, "node221");
   mRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(222, "node222");
   mRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(23, "node23");
   mRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(24, "node24");
   mRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(3, "node3");
   mRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(4, "node4");
   mRootNode->attachAfterLastChild(tNode);
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
   CC::TreeNode* tNode = 0;

   tNode = new CC::LabelledTreeNode(1, "node1");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(2, "node2");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(21, "node21");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(22, "node22");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(221, "node221");
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(222, "node222");
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(23, "node23");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(24, "node24");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(3, "node3");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(4, "node4");
   tRootNode->attachAfterLastChild(tNode);


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
   aCmd->setArgDefault(1,3);

   CC::LabelledTreeNode* tRootNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm,0,"root");
   CC::TreeNode* tNode = 0;

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 1, "node1");
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 2, "node2");
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 21, "node21");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 22, "node22");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 221, "node221");
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 222, "node222");
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 23, "node23");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 24, "node24");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 3, "node3");
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 4, "node4");
   tRootNode->attachAfterLastChild(tNode);

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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);

   CC::LabelledTreeNode::mBlockUniverse.show("CC::LabelledTreeNode::mBlockUniverse1");

   CC::LabelledTreeNode* tRootNode = CC::LabelledTreeNode::create(0,"root");
   CC::TreeNode* tNode = 0;

   tNode = CC::LabelledTreeNode::create( 1,   "node1" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 2,   "node2" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 21,  "node21" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 22,  "node22" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 221, "node221" );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 222, "node222" );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 23,  "node23" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 24,  "node24" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 3,   "node3" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 4,   "node4" );
   tRootNode->attachAfterLastChild(tNode);

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

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, 0, "create  Block2A");
   Some::Block2A* t2A = Some::Block2A::create(CC::MemoryType_System);

   Prn::print(0, 0, "destroy Block2A");
   t2A->destroy();

   Prn::print(0, 0, "");

   Prn::print(0, 0, "create  Block2B");
   Some::Block2B* t2B = Some::Block2B::create(CC::MemoryType_System);

   Prn::print(0, 0, "destroy Block2B");
   t2B->destroy();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   CC::printAllLabelledTreeNodes1(mRootNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   CC::TreeNodeTxQueue tTxQueue;
   CC::TreeNodeRxQueue tRxQueue;

   tTxQueue.putTxNode(mRootNode);

   while (true)
   {
      CC::TreeNode* tNode = tTxQueue.getNextTxNode();
      if (tNode != 0)
      {
         printf("LINE101 %d\n",tNode->mIdentifier);
       //tRxQueue.putRxNode(tNode);
      }
      else
      {
         break;
      }
   }
   return;

   while (true)
   {
      CC::TreeNode* tNode = tRxQueue.getNextRxNode();
      if (tNode != 0)
      {
         printf("LINE201 %d\n",tNode->mIdentifier);
      }
      else
      {
         break;
      }
   }

}

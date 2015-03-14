#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "ccTreeNode.h"
#include "ccTreeNodeAttach.h"
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeDestroyer.h"
#include "ccLabelledTreeNode.h"
#include "ccLabelledTreeNodeVisitor.h"
#include "someBlock1.h"
#include "someBlock2.h"

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   Some::Block2A::initializeBlockUniverse(1000,1000);
   Some::Block2B::initializeBlockUniverse(1000,1000);

   CC::LabelledTreeNode::initializeBlockUniverse(1000,1000);
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
   aCmd->setArgDefault(1,4);

   CC::LabelledTreeNode* tRootNode = new CC::LabelledTreeNode(0,"root");
   CC::TreeNode* tNode = 0;

   tNode = new CC::LabelledTreeNode(1, "node1");
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = new CC::LabelledTreeNode(2, "node2");
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = new CC::LabelledTreeNode(21, "node21");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = new CC::LabelledTreeNode(22, "node22");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = new CC::LabelledTreeNode(221, "node221");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode->mLastChildNode);

   tNode = new CC::LabelledTreeNode(222, "node222");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode->mLastChildNode);

   tNode = new CC::LabelledTreeNode(23, "node23");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = new CC::LabelledTreeNode(24, "node24");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = new CC::LabelledTreeNode(3, "node3");
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = new CC::LabelledTreeNode(4, "node4");
   CC::attachAfterLastChild(tNode,tRootNode);


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
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 2, "node2");
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 21, "node21");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 22, "node22");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 221, "node221");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 222, "node222");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 23, "node23");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 24, "node24");
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 3, "node3");
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = CC::LabelledTreeNode::create(CC::MemoryType_LongTerm, 4, "node4");
   CC::attachAfterLastChild(tNode,tRootNode);

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
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = CC::LabelledTreeNode::create( 2,   "node2" );
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = CC::LabelledTreeNode::create( 21,  "node21" );
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create( 22,  "node22" );
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create( 221, "node221" );
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create( 222, "node222" );
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create( 23,  "node23" );
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create( 24,  "node24" );
   CC::attachAfterLastChild(tNode,tRootNode->mLastChildNode);

   tNode = CC::LabelledTreeNode::create( 3,   "node3" );
   CC::attachAfterLastChild(tNode,tRootNode);

   tNode = CC::LabelledTreeNode::create( 4,   "node4" );
   CC::attachAfterLastChild(tNode,tRootNode);

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
   Some::Block2A* t2A = Some::Block2A::create(CC::MemoryType_LongTerm);

   Prn::print(0, 0, "destroy Block2A");
   t2A->destroy();

   Prn::print(0, 0, "");

   Prn::print(0, 0, "create  Block2B");
   Some::Block2B* t2B = Some::Block2B::create(CC::MemoryType_LongTerm);

   Prn::print(0, 0, "destroy Block2B");
   t2B->destroy();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

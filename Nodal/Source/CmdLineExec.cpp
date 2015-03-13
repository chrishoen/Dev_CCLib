#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "ccTreeNode.h"
#include "ccTreeNodeAttach.h"
#include "ccTreeNodeVisitor.h"
#include "ccLabelledTreeNode.h"
#include "ccLabelledTreeNodeVisitor.h"
#include "someBlock1.h"
#include "someBlock2.h"

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   Some::Block2A::initializeMemory(1000);
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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,3);

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
   Prn::print(0, 0, "");

   Prn::print(0, 0, "new Block1A");
   Some::Block1A* t1A = new Some::Block1A;
   Prn::print(0, 0, "");

   Prn::print(0, 0, "new Block1B");
   Some::Block1B* t1B = new Some::Block1B;
   Prn::print(0, 0, "");

   Prn::print(0, 0, "delete Block1A");
   delete t1A;
   Prn::print(0, 0, "");

   Prn::print(0, 0, "delete Block1B");
   delete t1B;
   Prn::print(0, 0, "");
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, 0, "");

   Prn::print(0, 0, "new Block2A");
   Some::Block2A* t2A = new Some::Block2A;
   Prn::print(0, 0, "");

   Prn::print(0, 0, "delete Block2A");
   delete t2A;
   Prn::print(0, 0, "");
}

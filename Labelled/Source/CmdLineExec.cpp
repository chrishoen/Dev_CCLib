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
#include "GenerateLabelledTreeNodes.h"

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   CC::LabelledTreeNode::initializeLongTermBlockPool(1000);
}
//******************************************************************************
void CmdLineExec::reset()
{
   mRootNode = new CC::LabelledTreeNode(0,"root");

   generateLabelledTreeNodes1(mRootNode);
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

   CC::LabelledTreeNode* tRootNode = new CC::LabelledTreeNode(0,"root");

   if (aCmd->argInt(1) == 1)
   {
      generateLabelledTreeNodes1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      generateLabelledTreeNodes2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      generateLabelledTreeNodes3(tRootNode);
   }

   CC::printAllLabelledTreeNodes3(tRootNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);

   CC::LabelledTreeNode* tRootNode = new CC::LabelledTreeNode(0,"root");
   generateLabelledTreeNodes3(tRootNode);

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

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);

   CC::LabelledTreeNode::mBlockPool.show();

   CC::LabelledTreeNode* tRootNode = CC::LabelledTreeNode::create(0,"root");
   generateLabelledTreeNodes2(tRootNode);

   CC::LabelledTreeNode::mBlockPool.show();

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

   CC::LabelledTreeNode::mBlockPool.show();
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

   CC::LabelledTreeNode* tRootNode = new CC::LabelledTreeNode(0,"troot");

   printf("**********************************generateTreeNodes1(tRootNode1)\n");
   CC::LabelledTreeNode* tRootNode1 = new CC::LabelledTreeNode(0,"root1");
   generateLabelledTreeNodes1(tRootNode1);

   printf("**********************************generateTreeNodes1(tRootNode2)\n");
   CC::LabelledTreeNode* tRootNode2 = new CC::LabelledTreeNode(0,"root2");
   generateLabelledTreeNodes1(tRootNode2);

   printf("**********************************attachAfterLastChild(tRootNode1)\n");
   tRootNode->attachAfterLastChild(tRootNode1);

   printf("**********************************attachAfterLastChild(tRootNode2\n");
   tRootNode->attachAfterLastChild(tRootNode2);

   printf("**********************************printAllLabelledTreeNodes1(mRootNode)\n");
   CC::printAllLabelledTreeNodes1(tRootNode);
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
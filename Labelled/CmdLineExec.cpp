#include "stdafx.h"

#include <atomic>

#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeDestroyer.h"
#include "ccBlockPool.h"
#include "someBlockPoolIndex.h"
#include "someLabelledTreeNode.h"
#include "someGenerateLabelledTreeNodes.h"
#include "someLabelledTreeNodeVisitor.h"
#include "CmdLineExec.h"

using namespace Some;

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
   if(aCmd->isCmd("GO6"    ))  executeGo6(aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);

   LabelledTreeNode* tRootNode = new LabelledTreeNode(0,"root");

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

   printAllLabelledTreeNodesCO(tRootNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);

   LabelledTreeNode* tRootNode = new LabelledTreeNode(0,"root");
   generateLabelledTreeNodes1(tRootNode);

   if (aCmd->argInt(1) == 1)
   {
      printAllLabelledTreeNodesCO(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      printAllLabelledTreeNodesDO(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      printAllLabelledTreeNodesVN(tRootNode);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);

   CC::showBlockPool(Some::cBlockPoolIndex_LabelledTreeNode);

   LabelledTreeNode* tRootNode = new LabelledTreeNode(0,"root");
   generateLabelledTreeNodes1(tRootNode);

   CC::showBlockPool(Some::cBlockPoolIndex_LabelledTreeNode);

   if (aCmd->argInt(1) == 1)
   {
      printAllLabelledTreeNodesCO(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      printAllLabelledTreeNodesDO(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      printAllLabelledTreeNodesVN(tRootNode);
   }
   else if (aCmd->argInt(1) == 4)
   {
      destroyAllLabelledTreeNodes(tRootNode);
   }
   else if (aCmd->argInt(1) == 5)
   {
      CC::destroyAllTreeNodes(tRootNode);
   }

   CC::showBlockPool(Some::cBlockPoolIndex_LabelledTreeNode);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   LabelledTreeNode* tRootNode = new LabelledTreeNode(0,"root");

   generateLabelledTreeNodes1(tRootNode);
   printAllLabelledTreeNodesCO(tRootNode);
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

   LabelledTreeNode* tRootNode = new LabelledTreeNode(0,"troot");

   printf("**********************************generateTreeNodes1(tRootNode1)\n");
   LabelledTreeNode* tRootNode1 = new LabelledTreeNode(0,"root1");
   generateLabelledTreeNodes1(tRootNode1);

   printf("**********************************generateTreeNodes1(tRootNode2)\n");
   LabelledTreeNode* tRootNode2 = new LabelledTreeNode(0,"root2");
   generateLabelledTreeNodes1(tRootNode2);

   printf("**********************************attachAfterLastChild(tRootNode1)\n");
   tRootNode->attachAfterLastChild(tRootNode1);

   printf("**********************************attachAfterLastChild(tRootNode2\n");
   tRootNode->attachAfterLastChild(tRootNode2);

   printf("**********************************printAllLabelledTreeNodesCO(mRootNode)\n");
   printAllLabelledTreeNodesCO(tRootNode);
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

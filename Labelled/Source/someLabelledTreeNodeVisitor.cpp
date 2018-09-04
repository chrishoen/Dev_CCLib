
#include "stdafx.h"

#include "someLabelledTreeNodeVisitor.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitLabelledTreeNodeForPrint (CC::TreeNode* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor)
{
   LabelledTreeNode* tSubjectNode = static_cast<LabelledTreeNode*>(aSubjectNode);

   printf("visitLabelledTreeNodeForPrint %3d %d %d %5d %s\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier,
      tSubjectNode->getFullPath());
//    tSubjectNode->mFullPath);
}

void printAllLabelledTreeNodesCO(LabelledTreeNode* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall(visitLabelledTreeNodeForPrint);
   CC::RecursiveAnchor tRecursiveAnchor;

   visitAllNodesCO(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

void printAllLabelledTreeNodesDO(LabelledTreeNode* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall(visitLabelledTreeNodeForPrint);
   CC::RecursiveAnchor tRecursiveAnchor;

   visitAllNodesDO(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

void printAllLabelledTreeNodesVN(LabelledTreeNode* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall(visitLabelledTreeNodeForPrint);
   CC::RecursiveAnchor tRecursiveAnchor;

   CC::TreeNode* tNode = aSubjectNode;
   while (tNode)
   {
      tNode = visitNode(tNode, &tRecursiveAnchor, &tNodeVisitorCall);
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitLabelledTreeNodeForDestroy (CC::TreeNode* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor)
{
   LabelledTreeNode* tSubjectNode = static_cast<LabelledTreeNode*>(aSubjectNode);
#if 0
   printf("visitLabelledTreeNodeForDestroy %3d %1d %1d %5d %s\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier,
      tSubjectNode->mFullPath);
#endif
   delete tSubjectNode;
}

void destroyAllLabelledTreeNodes(LabelledTreeNode* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall(visitLabelledTreeNodeForPrint);
   CC::RecursiveAnchor tRecursiveAnchor;

   visitAllNodesDO(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

}//namespace
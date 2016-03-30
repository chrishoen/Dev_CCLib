
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void printAllLabelledTreeNodes1(LabelledTreeNode* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall(visitLabelledTreeNodeForPrint);
   CC::RecursiveAnchor tRecursiveAnchor;

   visitAllNodes1(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

void printAllLabelledTreeNodes2(LabelledTreeNode* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall(visitLabelledTreeNodeForPrint);
   CC::RecursiveAnchor tRecursiveAnchor;

   visitAllNodes2(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

void printAllLabelledTreeNodes3(LabelledTreeNode* aSubjectNode)
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
   tSubjectNode->destroy();
}

void destroyAllLabelledTreeNodes(LabelledTreeNode* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall(visitLabelledTreeNodeForPrint);
   CC::RecursiveAnchor tRecursiveAnchor;

   visitAllNodes2(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

}//namespace
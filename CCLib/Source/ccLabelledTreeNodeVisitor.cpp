
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccLabelledTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitLabelledTreeNodeForPrint (TreeNode* aSubjectNode, RecursiveAnchor* aRecursiveAnchor)
{
   LabelledTreeNode* tSubjectNode = static_cast<LabelledTreeNode*>(aSubjectNode);

   printf("visitLabelledTreeNodeForPrint %3d %d %d %5d %s\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier,
      tSubjectNode->mFullPath);
}

void printAllLabelledTreeNodes1(LabelledTreeNode* aSubjectNode)
{
   visitAllNodes1(
      aSubjectNode,
      new RecursiveAnchor(),
      new NodeVistorCall(visitLabelledTreeNodeForPrint));
}

void printAllLabelledTreeNodes2(LabelledTreeNode* aSubjectNode)
{
   visitAllNodes2(
      aSubjectNode,
      new RecursiveAnchor(),
      new NodeVistorCall(visitLabelledTreeNodeForPrint));
}

void printAllLabelledTreeNodes3(LabelledTreeNode* aSubjectNode)
{
   NodeVistorCall tNodeVisitorCall;
   tNodeVisitorCall.bind(visitLabelledTreeNodeForPrint);
   RecursiveAnchor tRecursiveAnchor;

   TreeNode* tNode = aSubjectNode;
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

void visitLabelledTreeNodeForDestroy (TreeNode* aSubjectNode, RecursiveAnchor* aRecursiveAnchor)
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
   visitAllNodes2(
      aSubjectNode,
      new RecursiveAnchor(),
      new NodeVistorCall(visitLabelledTreeNodeForDestroy));
}

}//namespace
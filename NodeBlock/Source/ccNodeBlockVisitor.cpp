
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccNodeBlockVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitNodeBlockForPrint (TreeNode* aSubjectNode, RecursiveAnchor* aRecursiveAnchor)
{
   NodeBlock* tSubjectNode = static_cast<NodeBlock*>(aSubjectNode);

   printf("visitNodeBlockForPrint %3d %d %d %5d %s\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier,
      tSubjectNode->mFullPath);
}

void printAllNodeBlocks1(NodeBlock* aSubjectNode)
{
   visitAllNodes1(
      aSubjectNode,
      new RecursiveAnchor(),
      new NodeVistorCall(visitNodeBlockForPrint));
}

void printAllNodeBlocks2(NodeBlock* aSubjectNode)
{
   visitAllNodes2(
      aSubjectNode,
      new RecursiveAnchor(),
      new NodeVistorCall(visitNodeBlockForPrint));
}

void printAllNodeBlocks3(NodeBlock* aSubjectNode)
{
   NodeVistorCall tNodeVisitorCall;
   tNodeVisitorCall.bind(visitNodeBlockForPrint);
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

void visitNodeBlockForDestroy (TreeNode* aSubjectNode, RecursiveAnchor* aRecursiveAnchor)
{
   NodeBlock* tSubjectNode = static_cast<NodeBlock*>(aSubjectNode);
#if 0
   printf("visitNodeBlockForDestroy %3d %1d %1d %5d %s\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier,
      tSubjectNode->mFullPath);
#endif
   tSubjectNode->destroy();
}

void destroyAllNodeBlocks(NodeBlock* aSubjectNode)
{
   visitAllNodes2(
      aSubjectNode,
      new RecursiveAnchor(),
      new NodeVistorCall(visitNodeBlockForDestroy));
}

}//namespace
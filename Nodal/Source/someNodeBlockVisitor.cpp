
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "someNodeBlockVisitor.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitNodeBlockForPrint (CC::TreeNode* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor)
{
   NodeBlock* tSubjectNode = static_cast<NodeBlock*>(aSubjectNode);

   printf("visitNodeBlockForPrint %3d %d %d %5d\n",
      aRecursiveAnchor->mIndex,
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier);
}

void printAllNodeBlocks1(NodeBlock* aSubjectNode)
{
   CC::visitAllNodes1(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      new CC::NodeVisitorCall(visitNodeBlockForPrint));
}

void printAllNodeBlocks2(NodeBlock* aSubjectNode)
{
   CC::visitAllNodes2(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      new CC::NodeVisitorCall(visitNodeBlockForPrint));
}

void printAllNodeBlocks3(NodeBlock* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall;
   tNodeVisitorCall.bind(visitNodeBlockForPrint);
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

void visitNodeBlockForDestroy (CC::TreeNode* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor)
{
   NodeBlock* tSubjectNode = static_cast<NodeBlock*>(aSubjectNode);
#if 0
   printf("visitNodeBlockForDestroy %3d %1d %1d %5d\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier);
#endif
   tSubjectNode->destroy();
}

void destroyAllNodeBlocks(NodeBlock* aSubjectNode)
{
   CC::visitAllNodes2(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      new CC::NodeVisitorCall(visitNodeBlockForDestroy));
}

}//namespace
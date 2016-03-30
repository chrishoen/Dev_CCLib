
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "someMyTreeBlockVisitor.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitMyTreeBlockForPrint (CC::TreeNode* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor)
{
   MyTreeBlock* tSubjectNode = static_cast<MyTreeBlock*>(aSubjectNode);

   printf("visitMyTreeBlockForPrint %3d %d %d %5d\n",
      aRecursiveAnchor->mIndex,
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier);
}

void printAllMyTreeBlocks1(MyTreeBlock* aSubjectNode)
{
   CC::visitAllNodes1(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      new CC::NodeVisitorCall(visitMyTreeBlockForPrint));
}

void printAllMyTreeBlocks2(MyTreeBlock* aSubjectNode)
{
   CC::visitAllNodes2(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      new CC::NodeVisitorCall(visitMyTreeBlockForPrint));
}

void printAllMyTreeBlocks3(MyTreeBlock* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall;
   tNodeVisitorCall.bind(visitMyTreeBlockForPrint);
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

void visitMyTreeBlockForDestroy (CC::TreeNode* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor)
{
   MyTreeBlock* tSubjectNode = static_cast<MyTreeBlock*>(aSubjectNode);
#if 1
   printf("visitMyTreeBlockForDestroy %3d %1d %1d %5d\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      tSubjectNode->mIdentifier);
#endif
   tSubjectNode->destroy();
}

void destroyAllMyTreeBlocks(MyTreeBlock* aSubjectNode)
{
   CC::visitAllNodes2(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      new CC::NodeVisitorCall(visitMyTreeBlockForDestroy));
}

}//namespace
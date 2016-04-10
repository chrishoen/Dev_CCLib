
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

void printAllMyTreeBlocksCO(MyTreeBlock* aSubjectNode)
{
   CC::RecursiveAnchor tRecursiveAnchor;
   CC::NodeVisitorCall tNodeVisitorCall(visitMyTreeBlockForPrint);

   CC::visitAllNodesCO(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

void printAllMyTreeBlocksDO(MyTreeBlock* aSubjectNode)
{
   CC::RecursiveAnchor tRecursiveAnchor;
   CC::NodeVisitorCall tNodeVisitorCall(visitMyTreeBlockForPrint);

   CC::visitAllNodesDO(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

void printAllMyTreeBlocksVN(MyTreeBlock* aSubjectNode)
{
   CC::NodeVisitorCall tNodeVisitorCall(visitMyTreeBlockForPrint);
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
   delete tSubjectNode;
}

void destroyAllMyTreeBlocks(MyTreeBlock* aSubjectNode)
{
   CC::RecursiveAnchor tRecursiveAnchor;
   CC::NodeVisitorCall tNodeVisitorCall(visitMyTreeBlockForDestroy);

   CC::visitAllNodesDO(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

}//namespace
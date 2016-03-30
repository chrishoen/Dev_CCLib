
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccTestNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitAllNodes1(
   TestNode*         aSubjectNode,
   RecursiveAnchor*  aRecursiveAnchor,
   NodeVisitorCall*  aNodeVisitorCall)
{
   // Visit the subject node
   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);

   // Visit all nodes below the subject node
   visitAllNodesAfter1(
      aSubjectNode,
      aRecursiveAnchor,
      aNodeVisitorCall);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitAllNodesAfter1(
   TestNode*         aSubjectNode,
   RecursiveAnchor*  aRecursiveAnchor,
   NodeVisitorCall*  aNodeVisitorCall)
{
   //-------------------------------------------------------------------------
   // Loop for each child node of the subject node

   // Start the loop at the first child node
   TestNode* tAfterNode = aSubjectNode->mAfterNode;

   // Loop through the child nodes
   while (tAfterNode != 0)
   {
      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Visit the child node before the recursive call
      (*aNodeVisitorCall)(tAfterNode, aRecursiveAnchor);

      // Proceed to the next child node
      tAfterNode = tAfterNode->mAfterNode;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}


//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitNodeForPrint (TestNode* aNode, RecursiveAnchor* aRecursiveAnchor)
{
   printf("visitNodeForPrint %3d %d %d %5d\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      aNode->mIdentifier);
}

void printAllTestNodes1(TestNode* aSubjectNode)
{
   NodeVisitorCall tNodeVisitorCall(visitNodeForPrint);
   RecursiveAnchor tRecursiveAnchor;

   visitAllNodes1(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

}//namespace
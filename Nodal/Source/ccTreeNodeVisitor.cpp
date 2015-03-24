
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

RecursiveAnchor::RecursiveAnchor()
{
   mIndex = 0;
   mLevel = 0;
   mFirstInLevel = true;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitAllNodes1(
   TreeNode*        aSubjectNode,
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall)
{
   // Visit the subject node
   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);

   // Visit all nodes below the subject node
   visitAllNodesBelow1(
      aSubjectNode,
      aRecursiveAnchor,
      aNodeVisitorCall);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitAllNodes2(
   TreeNode*        aSubjectNode,
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall)
{
   // Visit all nodes below the subject node
   visitAllNodesBelow2(
      aSubjectNode,
      aRecursiveAnchor,
      aNodeVisitorCall);

   // Visit the subject node
   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);

}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitAllNodesBelow1(
   TreeNode*        aSubjectNode,
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall)
{
   //-------------------------------------------------------------------------
   // Loop for each child node of the subject node

   // Recursive local variable for first in level flag, 
   bool tFirstInLevel=true;

   // Before the loop, increment the recursive level
   aRecursiveAnchor->mLevel++;

   // Start the loop at the first child node
   TreeNode* tChildNode = aSubjectNode->mFirstChildNode;

   // Loop through the child nodes
   while (tChildNode != 0)
   {
      // Update the recursive first in level flag
      aRecursiveAnchor->mFirstInLevel = tFirstInLevel;
      tFirstInLevel = false;

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Visit the child node before the recursive call
      (*aNodeVisitorCall)(tChildNode, aRecursiveAnchor);

      // Recursively call this method for the child node
      visitAllNodesBelow1(
         tChildNode,
         aRecursiveAnchor,
         aNodeVisitorCall);

      // Proceed to the next child node
      tChildNode = tChildNode->mAfterNode;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Visit all nodes below

void visitAllNodesBelow2(
   TreeNode*        aSubjectNode,
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall)
{
   //-------------------------------------------------------------------------
   // Loop for each child node of the subject node

   // Recursive local variable for first in level flag, 
   bool tFirstInLevel=true;

   // Before the loop, increment the recursive level
   aRecursiveAnchor->mLevel++;

   // Start the loop at the first child node
   TreeNode* tChildNode = aSubjectNode->mFirstChildNode;

   // Loop through the child nodes
   while (tChildNode != 0)
   {
      // Update the recursive first in level flag
      aRecursiveAnchor->mFirstInLevel = tFirstInLevel;
      tFirstInLevel = false;

      // Recursively call this method for the child node
      visitAllNodesBelow2(
         tChildNode,
         aRecursiveAnchor,
         aNodeVisitorCall);

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Visit the child node after the recursive call
      (*aNodeVisitorCall)(tChildNode, aRecursiveAnchor);

      // Proceed to the next child node
      tChildNode = tChildNode->mAfterNode;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitNodeForPrint (TreeNode* aNode, RecursiveAnchor* aRecursiveAnchor)
{
   printf("visitNodeForPrint %3d %d %d %5d\n", 
      aRecursiveAnchor->mIndex, 
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      aNode->mIdentifier);
}

void printAllTreeNodes1(TreeNode* aSubjectNode)
{
   visitAllNodes1(
      aSubjectNode,
      new RecursiveAnchor(),
      new NodeVistorCall(visitNodeForPrint));
}

void printAllTreeNodes2(TreeNode* aSubjectNode)
{
   NodeVistorCall tNodeVisitorCall;
   tNodeVisitorCall.bind(visitNodeForPrint);
   RecursiveAnchor tRecursiveAnchor;

   visitAllNodes2(
      aSubjectNode,
      &tRecursiveAnchor,
      &tNodeVisitorCall);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Visit a node and return a pointer to the next node

TreeNode* visitNode(
   TreeNode*        aSubjectNode,
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall)
{
   // Visit the subject node
   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

   // Pointer to the next node
   TreeNode* tNextNode = 0;

   // If the subject node has child nodes
   if (aSubjectNode->mFirstChildNode)
   {
      // The next node will be the first child node of the subject node
      tNextNode = aSubjectNode->mFirstChildNode;
      // The next node level will increase
      aRecursiveAnchor->mLevel++;
      // The next node will be the first in its level
      aRecursiveAnchor->mFirstInLevel = true;
   }
   // Else if the subject node has a node after it
   else if (aSubjectNode->mAfterNode)
   {
      // The next node will be the node after it
      tNextNode = aSubjectNode->mAfterNode;
      // The next node will not be the first in its level
      aRecursiveAnchor->mFirstInLevel = false;
   }
   // Else the subject node has no child nodes and no nodes after it
   else
   {
      // If the subject node is the child of a parent node
      if (aSubjectNode->mParentNode)
      {
         // The next node will be the node after the parent node.
         // If the parent node has no node after it then there is no next node.
         tNextNode = aSubjectNode->mParentNode->mAfterNode;
         // The next node level will decrease
         aRecursiveAnchor->mLevel--;
      }
      // If all nodes have already been visited then there is no next node
      else
      {
         tNextNode = 0;
      }
   }
   // Return the next node
   return tNextNode;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
void printAllTreeNodes3(TreeNode* aSubjectNode)
{
   NodeVistorCall tNodeVisitorCall;
   tNodeVisitorCall.bind(visitNodeForPrint);
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
// Return a pointer to the next node, in construction order

TreeNode* getNextNode(
   TreeNode*        aSubjectNode)
{
   // Guard
   if (aSubjectNode == 0) return 0;

   // Pointer to the next node
   TreeNode* tNextNode = 0;

   // If the subject node has child nodes
   if (aSubjectNode->mFirstChildNode)
   {
      // The next node will be the first child node of the subject node
      tNextNode = aSubjectNode->mFirstChildNode;
   }
   // Else if the subject node has a node after it
   else if (aSubjectNode->mAfterNode)
   {
      // The next node will be the node after it
      tNextNode = aSubjectNode->mAfterNode;
   }
   // Else the subject node has no child nodes and no nodes after it
   else
   {
      // If the subject node is the child of a parent node
      if (aSubjectNode->mParentNode)
      {
         // The next node will be the node after the parent node.
         // If the parent node has no node after it then there is no next node.
         tNextNode = aSubjectNode->mParentNode->mAfterNode;
      }
      // If all nodes have already been visited then there is no next node
      else
      {
         tNextNode = 0;
      }
   }
   // Return the next node
   return tNextNode;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Return a pointer to the next node, in construction order

TreeNode* getNextNode(
   TreeNode*        aSubjectNode,
   TreeNode*        aRootNode)
{
   // Guard
   if (aSubjectNode == 0) return 0;

   // Pointer to the next node
   TreeNode* tNextNode = 0;

   // If the subject node has child nodes
   if (aSubjectNode->mFirstChildNode)
   {
      // The next node will be the first child node of the subject node
      tNextNode = aSubjectNode->mFirstChildNode;
   }
   // Else if the subject node has a node after it
   else if (aSubjectNode->mAfterNode)
   {
      // The next node will be the node after it
      tNextNode = aSubjectNode->mAfterNode;
   }
   // Else the subject node has no child nodes and no nodes after it
   else
   {
      // If the subject node is the child of a parent node that is not the root node
      if (aSubjectNode->mParentNode && aSubjectNode->mParentNode != aRootNode)
      {
         // The next node will be the node after the parent node.
         // If the parent node has no node after it then there is no next node.
         tNextNode = aSubjectNode->mParentNode->mAfterNode;
      }
      // If all nodes have already been visited then there is no next node
      else
      {
         tNextNode = 0;
      }
   }
   // Return the next node
   return tNextNode;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Return a pointer to the previous node, in construction order

TreeNode* getPreviousNode(
   TreeNode*        aSubjectNode)
{
   // Guard
   if (aSubjectNode == 0) return 0;

   // Pointer to the previous node
   TreeNode* tPreviousNode = 0;

   // If the subject node has a node before it
   if (aSubjectNode->mBeforeNode)
   {
      // The previous node will be the node before it
      tPreviousNode = aSubjectNode->mBeforeNode;
   }
   // Else If the subject node has a parent node
   else if (aSubjectNode->mParentNode)
   {
      // The previous node will be the parent node
      tPreviousNode = aSubjectNode->mParentNode;
   }
   // Else the subject node doesn't have a previous node, it is a root node.
   else
   {
      tPreviousNode = 0;
   }

   // Return the previous node
   return tPreviousNode;
}

}//namespace
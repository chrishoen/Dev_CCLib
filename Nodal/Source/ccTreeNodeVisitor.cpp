
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
   //--------------------------------------------------------------------------
   // Visit the subject node

   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);

   //--------------------------------------------------------------------------
   // Set the subject node ancestor with after node

   // If the subject node has no parent
   if (aSubjectNode->mParentNode == 0)
   {
      // Then it has no ancestor with after node
      aSubjectNode->mAncestorWithAfter = 0;
   }
   // Else if the parent of the subject node has a node after it
   else if (aSubjectNode->mParentNode->mAfterNode !=0)
   {
      // Then the subject node ancestor with after node is its parent
      aSubjectNode->mAncestorWithAfter = aSubjectNode->mParentNode;
   }
   // Else the subject node has no parent with an ancestor node
   else
   {
      // Copy the subject node's parent ancestor after node to it.
      // That will be the closest ancestor that has a node after it.
      aSubjectNode->mAncestorWithAfter = aSubjectNode->mParentNode->mAncestorWithAfter;
   }

   //--------------------------------------------------------------------------
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
      // If the subject node has an ancestor after node
      if (aSubjectNode->mAncestorWithAfter)
      {
         // Set the next node to the ancestor after node
         tNextNode = aSubjectNode->mAncestorWithAfter->mAfterNode;
      }

#if 0
      // Loop up through the parent nodes of the subject node
      // to find the first parent node that has an after node

      // Start the loop at the subject node's parent
      TreeNode* tParentNode = aSubjectNode->mParentNode;

      // Loop until a parent is found that has an after node or there 
      // there are no parents
      while (tParentNode != 0)
      {
         // The next node level will decrease
         aRecursiveAnchor->mLevel--;

         // If the parent has an after node then the next node will be
         // that one
         if ((tNextNode = tParentNode->mAfterNode) != 0)
         {
            // This is the closest parent to the subject node that has
            // an after node. Exit the loop
            break;
         }
         // If the parent doesn't have an after node
         else
         {
            // Advance up to the next parent
            tParentNode = tParentNode->mParentNode;
         }
      }
#endif
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

   //--------------------------------------------------------------------------
   // Set the subject node above with after node

   // If the subject node has no parent
   if (aSubjectNode->mParentNode == 0)
   {
      // Then it has no above node with after node
      aSubjectNode->mAncestorWithAfter = 0;
   }
   // Else if the parent of the subject node has a node after it
   else if (aSubjectNode->mParentNode->mAfterNode !=0)
   {
      // Then the subject node above with after node is its parent
      aSubjectNode->mAncestorWithAfter = aSubjectNode->mParentNode;
   }
   // Else the subject node has no parent with an above node
   else
   {
      // Copy the subject node's parent above after node to it
      aSubjectNode->mAncestorWithAfter = aSubjectNode->mParentNode->mAncestorWithAfter;
   }

   //--------------------------------------------------------------------------
   // Pointer to the next node

   TreeNode* tNextNode = 0;

   //--------------------------------------------------------------------------
   // The transmit attach level starts at the subject node level

   int tTxAttachLevel = aSubjectNode->mTxAttachLevel;

   //--------------------------------------------------------------------------
   // If the subject node has child nodes

   if (aSubjectNode->mFirstChildNode)
   {
      // The next node will be the first child node of the subject node
      tNextNode = aSubjectNode->mFirstChildNode;

      // Update the transmit attachment level, going down one level
      tTxAttachLevel++;
      tNextNode->mTxAttachLevel = tTxAttachLevel;
   }
   // Else if the subject node has a node after it
   else if (aSubjectNode->mAfterNode)
   {
      // The next node will be the node after it
      tNextNode = aSubjectNode->mAfterNode;

      // Update the transmit attachment level
      tNextNode->mTxAttachLevel = tTxAttachLevel;
   }
   // Else the subject node has no child nodes and no nodes after it
   else
   {
      // Loop up through the parent nodes of the subject node
      // to find the first parent node that has an after node

      // Start the loop at the subject node's parent
      TreeNode* tParentNode = aSubjectNode->mParentNode;

      // Loop until a parent is found that has an after node or there 
      // there are no parents
      while (tParentNode != 0)
      {
         // Decrement the transmit attachment level, going up one level
         tTxAttachLevel--;

         // If the parent has an after node then the next node will be
         // that one
         if ((tNextNode = tParentNode->mAfterNode) != 0)
         {
            // This is the closest parent to the subject node that has
            // an after node. Update the transmit attachment level.
            tNextNode->mTxAttachLevel = tTxAttachLevel;
            // Exit the loop.
            break;
         }
         // If the parent doesn't have an after node
         else
         {
            // Advance up to the next parent
            tParentNode = tParentNode->mParentNode;
         }
      }
   }
   // Return the next node
   return tNextNode;
}

}//namespace
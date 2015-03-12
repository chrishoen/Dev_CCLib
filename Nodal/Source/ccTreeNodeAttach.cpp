
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccTreeNode.h"
#include "ccTreeNodeAttach.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to an object node, before it

void attachBefore (TreeNode* aSubjectNode,TreeNode* aObjectNode)
{
   // If the object node does not have a node before it
   if (aObjectNode->mBeforeNode == 0)
   {
      // The object node is its root node's first child
      if (aObjectNode->mParentNode != 0)
      {
         // Set the subject node as the root node's new first child
         aObjectNode->mParentNode->mFirstChildNode = aSubjectNode;
      }
      // Attach the subject node before the object node
      aSubjectNode->mBeforeNode      = 0;
      aSubjectNode->mAfterNode       = aObjectNode;
      aObjectNode->mBeforeNode       = aSubjectNode;
   }
   // If the object node does have a node before it
   else
   {
      // Insert the subject node between the object node and the node before it
      aSubjectNode->mBeforeNode      = aObjectNode->mBeforeNode;
      aSubjectNode->mAfterNode       = aObjectNode;
      aObjectNode->mBeforeNode->mAfterNode = aSubjectNode;
      aObjectNode->mBeforeNode             = aSubjectNode;
   }
   // The subect node inherits the object nodes's parent node
   aSubjectNode->mParentNode = aObjectNode->mParentNode;
   // Notify the subject node that it is attached to an object node
   aSubjectNode->onAttached();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to an object node, after it

void attachAfter (TreeNode* aSubjectNode,TreeNode* aObjectNode)
{
   // If the object node does not have a node after it
   if (aObjectNode->mAfterNode == 0)
   {
      // The object node is its root node's last child
      if (aObjectNode->mParentNode != 0)
      {
         // Set the subject node as the root node's new last child
         aObjectNode->mParentNode->mLastChildNode = aSubjectNode;
      }
      // Attach the subject node after the object node
      aSubjectNode->mBeforeNode      = aObjectNode;
      aSubjectNode->mAfterNode       = 0;
      aObjectNode->mAfterNode        = aSubjectNode;
   }
   // Else the object node does have a node after it
   else
   {
      // Insert the subject node between the object node and the node after it
      aSubjectNode->mBeforeNode      = aObjectNode;
      aSubjectNode->mAfterNode       = aObjectNode->mAfterNode;
      aObjectNode->mAfterNode->mBeforeNode = aSubjectNode;
      aObjectNode->mAfterNode              = aSubjectNode;
   }
   // The subject node inherits the object node's parent node
   aSubjectNode->mParentNode = aObjectNode->mParentNode;
   // Notify the subject node that it is attached to an object node
   aSubjectNode->onAttached();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to the first child of an object node, before it.
// The subject node becomes the object node's first child.

void attachBeforeFirstChild (TreeNode* aSubjectNode,TreeNode* aObjectNode)
{
   // If the object node's parent node doesn't have any children
   if (aObjectNode->mFirstChildNode == 0)
   {
      // Set the subject node as the first and last child to the parent
      aSubjectNode->mParentNode        = aObjectNode;
      aObjectNode->mFirstChildNode     = aSubjectNode;
      aObjectNode->mLastChildNode      = aSubjectNode;
      // Notify the subject node that it is attached to an object node
      aSubjectNode->onAttached();
      return;
   }
   // Else the object node's parent node does have children
   else
   {
      // Start a loop at the first child node of the object node. 
      // The loop will attach the subject node to the child node or a 
      // node after it, based on relative order.

      TreeNode* tChildNode = aObjectNode->mFirstChildNode;

      // Loop through the child nodes, starting at the first
      while (true)
      {
         // If the order of the subject node is less than or equal 
         // to the loop child node then the subject node is inserted
         // before the child node
         if (aSubjectNode->mOrder <= tChildNode->mOrder)
         {
            // Attach the subject node before the loop child node
            attachBefore(aSubjectNode,tChildNode);
            // Exit the loop
            return;
         }
         // If there is not a node after the loop child node then all
         // child nodes have been searched and none were of order less
         // than or equal. The subject node will be attached after the
         // last child node. 
         if (tChildNode->mAfterNode == 0)
         {
            // Attach the subject node after the loop child node. This will
            // become the last child node of the given object node.
            attachAfter(aSubjectNode,tChildNode);
            // Exit the loop
            return;
         }
         // Else advance the loop child node to the one after it
         tChildNode = tChildNode->mAfterNode;
      }
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to the last child of an object node, after it
// The subject node becomes the object node's last child.

void attachAfterLastChild  (TreeNode* aSubjectNode,TreeNode* aObjectNode)
{
   // If the object node's parent node doesn't have any children
   if (aObjectNode->mFirstChildNode == 0)
   {
      // Set the subject node as the first and last child to the parent
      aSubjectNode->mParentNode        = aObjectNode;
      aObjectNode->mFirstChildNode     = aSubjectNode;
      aObjectNode->mLastChildNode      = aSubjectNode;
      // Notify the subject node that it is attached to an object node
      aSubjectNode->onAttached();
   }
   // Else the object node's parent node does have children
   else
   {
      // Attach the subject node after the last child
      attachAfter(aSubjectNode,aObjectNode->mLastChildNode);
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach a subject node from its parent and before and after nodes

void detach(TreeNode* aSubjectNode)
{
   // If this subject node does not have a node before it
   if (aSubjectNode->mBeforeNode == 0)
   {
      // If this node has a parent then it's its root node's first child
      if (aSubjectNode->mParentNode != 0)
      {
         // Set the node after this node as the root node's first child
         aSubjectNode->mParentNode->mFirstChildNode = aSubjectNode->mAfterNode;
      }
   }
   // Else this node has a node before it
   else
   {
      // Set the node before it to point to the node after it
      aSubjectNode->mBeforeNode->mAfterNode = aSubjectNode->mAfterNode;
   }

   // If this node does not have a node after it
   if (aSubjectNode->mAfterNode == 0)
   {
      // If this node has a parent then it's its root node's last child
      if (aSubjectNode->mParentNode != 0)
      {
         // Set the node before this node as the root node's last child
         aSubjectNode->mParentNode->mLastChildNode = aSubjectNode->mBeforeNode;
      }
   }
   // Else this node has a node after it
   else
   {
      // Set the node after it to point to the node before it
      aSubjectNode->mAfterNode->mBeforeNode = aSubjectNode->mBeforeNode;
   }

   // This node no longer has a parent or nodes before and after it
   aSubjectNode->mParentNode = 0;
   aSubjectNode->mBeforeNode = 0;
   aSubjectNode->mAfterNode = 0;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
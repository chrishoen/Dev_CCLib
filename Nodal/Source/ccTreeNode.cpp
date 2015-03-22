
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccTreeNode.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructors

TreeNode::TreeNode()
{
   // All pointers to zero
   mParentNode = 0;
   mBeforeNode = 0;
   mAfterNode = 0;
   mFirstChildNode = 0;
   mLastChildNode = 0;

   // Empty state
   mIdentifier=0;
   mMemoryType = 0;
   mTreeNodeFlags.mValue = 0;
}

TreeNode::TreeNode(int aIdentifier)
{
   // All pointers to zero
   mParentNode = 0;
   mBeforeNode = 0;
   mAfterNode = 0;
   mFirstChildNode = 0;
   mLastChildNode = 0;

   // Set state
   mIdentifier = aIdentifier;
   mMemoryType = 0;
   mTreeNodeFlags.mValue = 0;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to an object node, before it

void TreeNode::attachBefore (TreeNode* aObjectNode)
{
   // If the object node does not have a node before it
   if (aObjectNode->mBeforeNode == 0)
   {
      // The object node is its root node's first child
      if (aObjectNode->mParentNode != 0)
      {
         // Set the subject node as the root node's new first child
         aObjectNode->mParentNode->mFirstChildNode = this;
      }
      // Attach the subject node before the object node
      this->mBeforeNode      = 0;
      this->mAfterNode       = aObjectNode;
      aObjectNode->mBeforeNode       = this;
   }
   // If the object node does have a node before it
   else
   {
      // Insert the subject node between the object node and the node before it
      this->mBeforeNode      = aObjectNode->mBeforeNode;
      this->mAfterNode       = aObjectNode;
      aObjectNode->mBeforeNode->mAfterNode = this;
      aObjectNode->mBeforeNode             = this;
   }
   // The subect node inherits the object nodes's parent node
   this->mParentNode = aObjectNode->mParentNode;
   // Notify the subject node that it is attached to an object node
   this->onAttached();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to an object node, after it

void TreeNode::attachAfter (TreeNode* aObjectNode)
{
   // If the object node does not have a node after it
   if (aObjectNode->mAfterNode == 0)
   {
      // The object node is its root node's last child
      if (aObjectNode->mParentNode != 0)
      {
         // Set the subject node as the root node's new last child
         aObjectNode->mParentNode->mLastChildNode = this;
      }
      // Attach the subject node after the object node
      this->mBeforeNode      = aObjectNode;
      this->mAfterNode       = 0;
      aObjectNode->mAfterNode        = this;
   }
   // Else the object node does have a node after it
   else
   {
      // Insert the subject node between the object node and the node after it
      this->mBeforeNode      = aObjectNode;
      this->mAfterNode       = aObjectNode->mAfterNode;
      aObjectNode->mAfterNode->mBeforeNode = this;
      aObjectNode->mAfterNode              = this;
   }
   // The subject node inherits the object node's parent node
   this->mParentNode = aObjectNode->mParentNode;
   // Notify the subject node that it is attached to an object node
   this->onAttached();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to the first child of an object node, before it.
// The subject node becomes the object node's first child.

void TreeNode::attachBeforeFirstChild (TreeNode* aObjectNode)
{
   // If the object node's parent node doesn't have any children
   if (aObjectNode->mFirstChildNode == 0)
   {
      // Set the subject node as the first and last child to the parent
      this->mParentNode        = aObjectNode;
      aObjectNode->mFirstChildNode     = this;
      aObjectNode->mLastChildNode      = this;
      // Notify the subject node that it is attached to an object node
      this->onAttached();
      return;
   }
   // Else the object node's parent node does have children
   else
   {
      // Attach the subject node before the first child
      this->attachBefore(aObjectNode->mFirstChildNode);
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to the last child of an object node, after it
// The subject node becomes the object node's last child.

void TreeNode::attachAfterLastChild  (TreeNode* aObjectNode)
{
   // If the object node's parent node doesn't have any children
   if (aObjectNode->mFirstChildNode == 0)
   {
      // Set the subject node as the first and last child to the parent
      this->mParentNode        = aObjectNode;
      aObjectNode->mFirstChildNode     = this;
      aObjectNode->mLastChildNode      = this;
      // Notify the subject node that it is attached to an object node
      this->onAttached();
   }
   // Else the object node's parent node does have children
   else
   {
      // Attach the subject node after the last child
      this->attachAfter(aObjectNode->mLastChildNode);
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach a subject node from its parent and before and after nodes

void TreeNode::detach()
{
   // If this subject node does not have a node before it
   if (this->mBeforeNode == 0)
   {
      // If this node has a parent then it's its root node's first child
      if (this->mParentNode != 0)
      {
         // Set the node after this node as the root node's first child
         this->mParentNode->mFirstChildNode = this->mAfterNode;
      }
   }
   // Else this node has a node before it
   else
   {
      // Set the node before it to point to the node after it
      this->mBeforeNode->mAfterNode = this->mAfterNode;
   }

   // If this node does not have a node after it
   if (this->mAfterNode == 0)
   {
      // If this node has a parent then it's its root node's last child
      if (this->mParentNode != 0)
      {
         // Set the node before this node as the root node's last child
         this->mParentNode->mLastChildNode = this->mBeforeNode;
      }
   }
   // Else this node has a node after it
   else
   {
      // Set the node after it to point to the node before it
      this->mAfterNode->mBeforeNode = this->mBeforeNode;
   }

   // This node no longer has a parent or nodes before and after it
   this->mParentNode = 0;
   this->mBeforeNode = 0;
   this->mAfterNode = 0;
}
//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
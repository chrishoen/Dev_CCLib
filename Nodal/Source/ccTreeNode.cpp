
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
   mTreeNodeTxFlags.mValue = 0;
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
   mTreeNodeTxFlags.mValue = 0;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to the first child of this subject node, before it.
// The object node becomes this subject node's first child.

void TreeNode::attachBeforeFirstChild (TreeNode* aObjectNode)
{
   // If this node doesn't have any children
   // Attach the object node as the only child of this node
   if (this->mFirstChildNode == 0)
   {
      // Set object node's parent as this node
      // Set object node's before as null
      // Set object node's after  as null
      aObjectNode->mParentNode  = this;
      aObjectNode->mBeforeNode  = 0;
      aObjectNode->mAfterNode   = 0;

      // Set the object node as the first and last child of this node
      this->mFirstChildNode     = aObjectNode;
      this->mLastChildNode      = aObjectNode;
   }
   // Else this node does have children
   // Attach the object node after the last child of this node
   else
   {
      // Set object node's parent as this node
      // Set object node's before as null
      // Set object node's after  as the current first child
      aObjectNode->mParentNode  = this;
      aObjectNode->mBeforeNode  = 0;
      aObjectNode->mAfterNode   = this->mFirstChildNode;

      // Set the object node as this node's new first child
      this->mFirstChildNode->mBeforeNode = aObjectNode;
      this->mFirstChildNode              = aObjectNode;
   }

   // Notify the object node that it is attached to this node
   aObjectNode->onAttached();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to the last child of this subject node, after it.
// The object node becomes this subject node's last child.

void TreeNode::attachAfterLastChild  (TreeNode* aObjectNode)
{
   // If this node doesn't have any children
   // Attach the object node as the only child of this node
   if (this->mFirstChildNode == 0)
   {
      // Set object node's parent as this node
      // Set object node's before as null
      // Set object node's after  as null
      aObjectNode->mParentNode  = this;
      aObjectNode->mBeforeNode  = 0;
      aObjectNode->mAfterNode   = 0;

      // Set the object node as the first and last child of this node
      this->mFirstChildNode     = aObjectNode;
      this->mLastChildNode      = aObjectNode;
   }
   // Else this node does have children
   // Attach the object node after the last child of this node
   else
   {
      // Set object node's parent as this node
      // Set object node's before as the current last child
      // Set object node's after  as null
      aObjectNode->mParentNode  = this;
      aObjectNode->mBeforeNode  = this->mLastChildNode;
      aObjectNode->mAfterNode   = 0;

      // Set the object node as this node's new last child
      this->mLastChildNode->mAfterNode = aObjectNode;
      this->mLastChildNode             = aObjectNode;
   }

   // Notify the object node that it is attached to this node
   aObjectNode->onAttached();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach the first child node of this parent subject node. Return a pointer
// to detached child node.

TreeNode* TreeNode::detachFirstChild ()
{
   // Pointer to the first child node of this subject parent node, this is
   // the node that is to be be detached.
   TreeNode* tNodeToDetach = this->mFirstChildNode;

   // If there is a node to be detached
   if (tNodeToDetach != 0)
   {
      // If the node to be detached has a node after it
      if (tNodeToDetach->mAfterNode != 0)
      {
         // Because this node is the first child of its parent and therefore has
         // no node before it then set the node after it to also have no node
         // before it.
         tNodeToDetach->mAfterNode->mBeforeNode = 0;

         // Set the new first child node of this subject parent node to be the
         // node after the node that is to be detached.
         this->mFirstChildNode = tNodeToDetach->mAfterNode;
      }
      // If the node to be detached does not have a node after it,
      // then it is the only child node of its parent.
      else
      {
         // Set the subect parent node to have no first child node.
         this->mFirstChildNode = 0;
         // Also, set the subect parent node to have no last child node.
         this->mLastChildNode = 0;
      }

      // Set the detached node to have no node after it. Because it is the 
      // first child node then it already has no node before it.
      tNodeToDetach->mAfterNode = 0;

      // Set the detached node to have no node parent node above it.
      tNodeToDetach->mParentNode = 0;
   }
   // Return the pointer to the detached node.
   return tNodeToDetach;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach the last child node of this parent subject node. Return a pointer
// to the detached child node.

TreeNode* TreeNode::detachLastChild()
{
   // Pointer to the last child node of this subject parent node, this is
   // the node that is to be be detached.
   TreeNode* tNodeToDetach = this->mLastChildNode;

   // If there is a node to be detached
   if (tNodeToDetach != 0)
   {
      // If the node to be detached has a node before it
      if (tNodeToDetach->mBeforeNode != 0)
      {
         // Because this node is the last child of its parent and therefore has
         // no node after it then set the node before it to also have no node
         // after it.
         tNodeToDetach->mBeforeNode->mAfterNode = 0;

         // Set the new last child node of this subject parent node to be the
         // node before the node that is to be detached.
         this->mLastChildNode = tNodeToDetach->mBeforeNode;
      }
      // If the node to be detached does not have a node before it,
      // then it is the only child node of its parent.
      else
      {
         // Set the subect parent node to have no last child node.
         this->mLastChildNode = 0;
         // Also, set the subect parent node to have no first child node.
         this->mFirstChildNode = 0;
      }

      // Set the detached node to have no node before it. Because it is the 
      // last child node then it already has no node after it.
      tNodeToDetach->mBeforeNode = 0;

      // Set the detached node to have no node parent node above it.
      tNodeToDetach->mParentNode = 0;
   }
   // Return the pointer to the detached node.
   return tNodeToDetach;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to this subject node, before it

void TreeNode::attachBefore (TreeNode* aObjectNode)
{
   // If this node does not have a node before it
   if (this->mBeforeNode == 0)
   {
      // This node is its root node's first child
      if (this->mParentNode != 0)
      {
         // Set the object node as this node's parent's new last child
         this->mParentNode->mFirstChildNode = aObjectNode;
      }
      // Attach the object node before this node
      aObjectNode->mBeforeNode      = 0;
      aObjectNode->mAfterNode       = this;
      this->mBeforeNode       = aObjectNode;
   }
   // If this node does have a node before it
   else
   {
      // Insert the object node between this node and the node before it
      aObjectNode->mBeforeNode      = this->mBeforeNode;
      aObjectNode->mAfterNode       = this;
      this->mBeforeNode->mAfterNode = aObjectNode;
      this->mBeforeNode             = aObjectNode;
   }
   // The object node inherits this nodes's parent node
   aObjectNode->mParentNode = this->mParentNode;
   // Notify the object node that it is attached to this node
   aObjectNode->onAttached();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to this subject node, after it

void TreeNode::attachAfter (TreeNode* aObjectNode)
{
   // If this node does not have a node after it
   if (this->mAfterNode == 0)
   {
      // This node is its root node's last child
      if (this->mParentNode != 0)
      {
         // Set the object node as this node's parent's new last child
         this->mParentNode->mLastChildNode = aObjectNode;
      }
      // Attach the object node after this node
      aObjectNode->mBeforeNode      = this;
      aObjectNode->mAfterNode       = 0;
      this->mAfterNode        = aObjectNode;
   }
   // Else this node does have a node after it
   else
   {
      // Insert the object node between this node and the node after it
      aObjectNode->mBeforeNode      = this;
      aObjectNode->mAfterNode       = this->mAfterNode;
      this->mAfterNode->mBeforeNode = aObjectNode;
      this->mAfterNode              = aObjectNode;
   }
   // The object node inherits this node's parent node
   aObjectNode->mParentNode = this->mParentNode;
   // Notify the object node that it is attached to this node
   aObjectNode->onAttached();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach a subject node from its parent and before and after nodes

void TreeNode::detachFromAll()
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
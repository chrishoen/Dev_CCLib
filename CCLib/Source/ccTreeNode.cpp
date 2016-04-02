
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccBlockPool.h"
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
   mParentNodeH = BlockHandle::nullH;
   mBeforeNodeH = BlockHandle::nullH;
   mAfterNodeH = BlockHandle::nullH;
   mFirstChildNodeH = BlockHandle::nullH;
   mLastChildNodeH = BlockHandle::nullH;

   // Empty state
   mIdentifier=0;
   mMemoryType = 0;
   mAncestorWithAfterH = BlockHandle::nullH;
}

TreeNode::TreeNode(int aIdentifier)
{
   // All pointers to zero
   mParentNodeH = BlockHandle::nullH;
   mBeforeNodeH = BlockHandle::nullH;
   mAfterNodeH = BlockHandle::nullH;
   mFirstChildNodeH = BlockHandle::nullH;
   mLastChildNodeH = BlockHandle::nullH;

   // Set state
   mIdentifier = aIdentifier;
   mMemoryType = 0;
   mAncestorWithAfterH = BlockHandle::nullH;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Get a pointer from a block handle.

TreeNode* TreeNode::ptr(BlockHandle aBlockHandle)
{
   return static_cast<TreeNode*>(getBlockPoolBlockPtr(aBlockHandle));
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to the first child of this subject node, before it.
// The object node becomes this subject node's first child.

void TreeNode::attachBeforeFirstChild (TreeNode* aObjectNodeP)
{
   // If this node doesn't have any children
   // Attach the object node as the only child of this node
   if (this->mFirstChildNodeH == BlockHandle::nullH)
   {
      // Set object node's parent as this node
      // Set object node's before as null
      // Set object node's after  as null
      aObjectNodeP->mParentNodeH  = this->mBlockHandle;
      aObjectNodeP->mBeforeNodeH  = BlockHandle::nullH;
      aObjectNodeP->mAfterNodeH   = BlockHandle::nullH;

      // Set the object node as the first and last child of this node
      this->mFirstChildNodeH     = aObjectNodeP->mBlockHandle;
      this->mLastChildNodeH      = aObjectNodeP->mBlockHandle;
   }
   // Else this node does have children
   // Attach the object node after the last child of this node
   else
   {
      // Set object node's parent as this node
      // Set object node's before as null
      // Set object node's after  as the current first child
      aObjectNodeP->mParentNodeH  = this->mBlockHandle;
      aObjectNodeP->mBeforeNodeH  = BlockHandle::nullH;
      aObjectNodeP->mAfterNodeH   = this->mFirstChildNodeH;

      // Set the object node as this node's new first child
      this->ptrFirstChildNode()->mBeforeNodeH = aObjectNodeP->mBlockHandle;
      this->mFirstChildNodeH                  = aObjectNodeP->mBlockHandle;
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to the last child of this subject node, after it.
// The object node becomes this subject node's last child.

void TreeNode::attachAfterLastChild  (TreeNode* aObjectNodeP)
{
   // If this node doesn't have any children
   // Attach the object node as the only child of this node
   if (this->mFirstChildNodeH == BlockHandle::nullH)
   {
      // Set object node's parent as this node
      // Set object node's before as null
      // Set object node's after  as null
      aObjectNodeP->mParentNodeH  = this->mBlockHandle;
      aObjectNodeP->mBeforeNodeH  = BlockHandle::nullH;
      aObjectNodeP->mAfterNodeH   = BlockHandle::nullH;

      // Set the object node as the first and last child of this node
      this->mFirstChildNodeH     = aObjectNodeP->mBlockHandle;
      this->mLastChildNodeH      = aObjectNodeP->mBlockHandle;
   }
   // Else this node does have children
   // Attach the object node after the last child of this node
   else
   {
      // Set object node's parent as this node
      // Set object node's before as the current last child
      // Set object node's after  as null
      aObjectNodeP->mParentNodeH  = this->mBlockHandle;
      aObjectNodeP->mBeforeNodeH  = this->mLastChildNodeH;
      aObjectNodeP->mAfterNodeH   = BlockHandle::nullH;

      // Set the object node as this node's new last child
      this->ptrLastChildNode()->mAfterNodeH = aObjectNodeP->mBlockHandle;
      this->mLastChildNodeH                 = aObjectNodeP->mBlockHandle;
   }
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
   TreeNode* tNodeToDetachP = this->ptrFirstChildNode();

   // If there is a node to be detached
   if (tNodeToDetachP != 0)
   {
      // If the node to be detached has a node after it
      if (tNodeToDetachP->mAfterNodeH != BlockHandle::nullH)
      {
         // Because this node is the first child of its parent and therefore has
         // no node before it then set the node after it to also have no node
         // before it.
         tNodeToDetachP->ptrAfterNode()->mBeforeNodeH = BlockHandle::nullH;

         // Set the new first child node of this subject parent node to be the
         // node after the node that is to be detached.
         this->mFirstChildNodeH = tNodeToDetachP->mAfterNodeH;
      }
      // If the node to be detached does not have a node after it,
      // then it is the only child node of its parent.
      else
      {
         // Set the subect parent node to have no first child node.
         this->mFirstChildNodeH = BlockHandle::nullH;
         // Also, set the subect parent node to have no last child node.
         this->mLastChildNodeH  = BlockHandle::nullH;
      }

      // Set the detached node to have no node after it. Because it is the 
      // first child node then it already has no node before it.
      tNodeToDetachP->mAfterNodeH = BlockHandle::nullH;

      // Set the detached node to have no node parent node above it.
      tNodeToDetachP->mParentNodeH = BlockHandle::nullH;
   }
   // Return the pointer to the detached node.
   return tNodeToDetachP;
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
   TreeNode* tNodeToDetachP = this->ptrLastChildNode();

   // If there is a node to be detached
   if (tNodeToDetachP != 0)
   {
      // If the node to be detached has a node before it
      if (tNodeToDetachP->mBeforeNodeH != BlockHandle::nullH)
      {
         // Because this node is the last child of its parent and therefore has
         // no node after it then set the node before it to also have no node
         // after it.
         tNodeToDetachP->ptrBeforeNode()->mAfterNodeH = BlockHandle::nullH;

         // Set the new last child node of this subject parent node to be the
         // node before the node that is to be detached.
         this->mLastChildNodeH = tNodeToDetachP->mBeforeNodeH;
      }
      // If the node to be detached does not have a node before it,
      // then it is the only child node of its parent.
      else
      {
         // Set the subect parent node to have no last child node.
         this->mLastChildNodeH = BlockHandle::nullH;
         // Also, set the subect parent node to have no first child node.
         this->mFirstChildNodeH = BlockHandle::nullH;
      }

      // Set the detached node to have no node before it. Because it is the 
      // last child node then it already has no node after it.
      tNodeToDetachP->mBeforeNodeH = BlockHandle::nullH;

      // Set the detached node to have no node parent node above it.
      tNodeToDetachP->mParentNodeH = BlockHandle::nullH;
   }
   // Return the pointer to the detached node.
   return tNodeToDetachP;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to this subject node, before it

void TreeNode::attachBefore (TreeNode* aObjectNodeP)
{
   // If this node does not have a node before it
   if (this->mBeforeNodeH == BlockHandle::nullH)
   {
      // This node is its root node's first child
      if (this->mParentNodeH != BlockHandle::nullH)
      {
         // Set the object node as this node's parent's new last child
         this->ptrParentNode()->mFirstChildNodeH = aObjectNodeP->mBlockHandle;
      }
      // Attach the object node before this node
      aObjectNodeP->mBeforeNodeH      = BlockHandle::nullH;
      aObjectNodeP->mAfterNodeH       = this->mBlockHandle;
      this->mBeforeNodeH              = aObjectNodeP->mBlockHandle;
   }
   // If this node does have a node before it
   else
   {
      // Insert the object node between this node and the node before it
      aObjectNodeP->mBeforeNodeH      = this->mBeforeNodeH;
      aObjectNodeP->mAfterNodeH       = this->mBlockHandle;
      this->ptrBeforeNode()->mAfterNodeH = aObjectNodeP->mBlockHandle;
      this->mBeforeNodeH                 = aObjectNodeP->mBlockHandle;
   }
   // The object node inherits this nodes's parent node
   aObjectNodeP->mParentNodeH = this->mParentNodeH;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to this subject node, after it

void TreeNode::attachAfter (TreeNode* aObjectNodeP)
{
   // If this node does not have a node after it
   if (this->mAfterNodeH == BlockHandle::nullH)
   {
      // This node is its root node's last child
      if (this->mParentNodeH != BlockHandle::nullH)
      {
         // Set the object node as this node's parent's new last child
         this->ptrParentNode()->mLastChildNodeH = aObjectNodeP->mBlockHandle;
      }
      // Attach the object node after this node
      aObjectNodeP->mBeforeNodeH      = this->mBlockHandle;
      aObjectNodeP->mAfterNodeH       = BlockHandle::nullH;
      this->mAfterNodeH               = aObjectNodeP->mBlockHandle;
   }
   // Else this node does have a node after it
   else
   {
      // Insert the object node between this node and the node after it
      aObjectNodeP->mBeforeNodeH      = this->mBlockHandle;
      aObjectNodeP->mAfterNodeH       = this->mAfterNodeH;
      this->ptrAfterNode()->mBeforeNodeH = aObjectNodeP->mBlockHandle;
      this->mAfterNodeH                  = aObjectNodeP->mBlockHandle;
   }
   // The object node inherits this node's parent node
   aObjectNodeP->mParentNodeH = this->mParentNodeH;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach a subject node from its parent and before and after nodes

void TreeNode::detachFromAll()
{
   // If this subject node does not have a node before it
   if (this->mBeforeNodeH == BlockHandle::nullH)
   {
      // If this node has a parent then it's its root node's first child
      if (this->mParentNodeH != BlockHandle::nullH)
      {
         // Set the node after this node as the root node's first child
         this->ptrParentNode()->mFirstChildNodeH = this->mAfterNodeH;
      }
   }
   // Else this node has a node before it
   else
   {
      // Set the node before it to point to the node after it
      this->ptrBeforeNode()->mAfterNodeH = this->mAfterNodeH;
   }

   // If this node does not have a node after it
   if (this->mAfterNodeH == BlockHandle::nullH)
   {
      // If this node has a parent then it's its root node's last child
      if (this->mParentNodeH != BlockHandle::nullH)
      {
         // Set the node before this node as the root node's last child
         this->ptrParentNode()->mLastChildNodeH = this->mBeforeNodeH;
      }
   }
   // Else this node has a node after it
   else
   {
      // Set the node after it to point to the node before it
      this->ptrAfterNode()->mBeforeNodeH = this->mBeforeNodeH;
   }

   // This node no longer has a parent or nodes before and after it
   this->mParentNodeH = BlockHandle::nullH;
   this->mBeforeNodeH = BlockHandle::nullH;
   this->mAfterNodeH  = BlockHandle::nullH;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This method deallocates the object from the block pool from which it was
// created. It does not call a class destructor.

void TreeNode::destroy()
{
   // Deallocate the block back to the block pool
   deallocateBlockPoolBlock(this->mBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
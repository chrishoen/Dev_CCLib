
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccBlockPoolList.h"
#include "ccTestNode.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructors

TestNode::TestNode()
{
   // All pointers to zero
   mBeforeNodeH = BlockHandle::nullH;
   mAfterNodeH  = BlockHandle::nullH;

   // Empty state
   mIdentifier=0;
}

TestNode::TestNode(int aIdentifier)
{
   // All pointers to zero
   mBeforeNodeH = BlockHandle::nullH;
   mAfterNodeH  = BlockHandle::nullH;

   // Set state
   mIdentifier = aIdentifier;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Get a pointer from a block handle.

TestNode* TestNode::ptr(BlockHandle aBlockHandle)
{
   return static_cast<TestNode*>(getBlockPoolBlockPtr(aBlockHandle));
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to this subject node, after it

void TestNode::attachAfter (TestNode* aObjectNodeP)
{
   // If this node does not have a node after it
   if (this->mAfterNodeH == BlockHandle::nullH)
   {
      // Attach the object node after this node
      aObjectNodeP->mBeforeNodeH     = this->mBlockHandle;
      aObjectNodeP->mAfterNodeH      = BlockHandle::nullH;
      this->mAfterNodeH              = aObjectNodeP->mBlockHandle;
   }
   // Else this node does have a node after it
   else
   {
      // Insert the object node between this node and the node after it
      aObjectNodeP->mBeforeNodeH     = this->mBlockHandle;
      aObjectNodeP->mAfterNodeH      = this->mAfterNodeH;
      this->ptrAfterNode()->mBeforeNodeH = aObjectNodeP->mBlockHandle;
      this->mAfterNodeH              = aObjectNodeP->mBlockHandle;
      printf("LINE101 %d\n",this->mAfterNodeH.mBlockIndex);
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach a subject node from its parent and before and after nodes

void TestNode::detachFromAll()
{
   // If this subject node does not have a node before it
   if (this->mBeforeNodeH == BlockHandle::nullH)
   {
   }
   // Else this node has a node before it
   else
   {
      // Set the node before it to point to the node after it
      ptr(this->mBeforeNodeH)->mAfterNodeH = this->mAfterNodeH;
   }

   // If this node does not have a node after it
   if (this->mAfterNodeH == BlockHandle::nullH)
   {
   }
   // Else this node has a node after it
   else
   {
      // Set the node after it to point to the node before it
      this->ptrAfterNode()->mBeforeNodeH = this->mBeforeNodeH;
   }

   // This node no longer has a parent or nodes before and after it
   this->mBeforeNodeH = BlockHandle::nullH;
   this->mAfterNodeH  = BlockHandle::nullH;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This method deallocates the object from the block pool from which it was
// created. It does not call a class destructor.

void TestNode::destroy()
{
   // Deallocate the block back to the block pool
   deallocateBlockPoolBlock(this->mBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
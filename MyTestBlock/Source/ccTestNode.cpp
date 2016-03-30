
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
   mBeforeNode = 0;
   mAfterNode = 0;

   // Empty state
   mIdentifier=0;
}

TestNode::TestNode(int aIdentifier)
{
   // All pointers to zero
   mBeforeNode = 0;
   mAfterNode = 0;

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

void TestNode::attachAfter (TestNode* aObjectNode)
{
   // If this node does not have a node after it
   if (this->mAfterNode == 0)
   {
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
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach a subject node from its parent and before and after nodes

void TestNode::detachFromAll()
{
   // If this subject node does not have a node before it
   if (this->mBeforeNode == 0)
   {
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
   }
   // Else this node has a node after it
   else
   {
      // Set the node after it to point to the node before it
      this->mAfterNode->mBeforeNode = this->mBeforeNode;
   }

   // This node no longer has a parent or nodes before and after it
   this->mBeforeNode = 0;
   this->mAfterNode = 0;
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
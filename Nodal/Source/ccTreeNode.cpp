
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
   mOrder = 0;
   mMemoryType = 0;
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
   mOrder = 0;
   mMemoryType = 0;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
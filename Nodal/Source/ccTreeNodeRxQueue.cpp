
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeRxQueue.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

TreeNodeRxQueue::TreeNodeRxQueue()
{
   mRootNode = &mRootNodeInstance;
   mPreviousRxNode = 0;
}

void TreeNodeRxQueue::putRxNode(TreeNode* aNode)
{
   if (mPreviousRxNode == 0)
   {
      mRootNode->attachAfterLastChild(aNode);
   }
   else
   {
      if (aNode->mTreeNodeTxFlags.mFirstChild)
      {
         mPreviousRxNode->attachBeforeFirstChild(aNode);
      }
      else if (aNode->mTreeNodeTxFlags.mLastChild)
      {
         mPreviousRxNode->attachAfterLastChild(aNode);
      }
      else 
      {
         mPreviousRxNode->mParentNode->attachAfterLastChild(aNode);
      }
   }
   mPreviousRxNode = aNode;
}

TreeNode* TreeNodeRxQueue::getNextRxNode()
{
   return 0;
}
}//namespace
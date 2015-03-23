
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
      mPreviousRxNode = aNode;
   }
   else
   {
      if (aNode->mTreeNodeTxFlags.mFirstChild)
      {
         mPreviousRxNode->attachBeforeFirstChild(aNode);
         mPreviousRxNode = aNode;
      }
      else if (aNode->mTreeNodeTxFlags.mLastChild)
      {
         mPreviousRxNode->mParentNode->attachAfterLastChild(aNode);
         mPreviousRxNode = mPreviousRxNode->mParentNode;
      }
      else 
      {
         mPreviousRxNode->mParentNode->attachAfterLastChild(aNode);
         mPreviousRxNode = aNode;
      }
   }
}

TreeNode* TreeNodeRxQueue::getNextRxNode()
{
   return 0;
}
}//namespace
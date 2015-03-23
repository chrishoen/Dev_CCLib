
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeTxQueue.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

TreeNodeTxQueue::TreeNodeTxQueue()
{
   mRootNode = &mRootNodeInstance;
   mPreviousTxNode = 0;
}

void TreeNodeTxQueue::putTxNode(TreeNode* aNode)
{
   if (mPreviousTxNode == 0)
   {
      mPreviousTxNode = aNode;
   }

   mRootNode->attachAfterLastChild(aNode);
}

TreeNode* TreeNodeTxQueue::getNextTxNode()
{
   TreeNode* tNextTxNode = getNextNode(mPreviousTxNode);

   tNextTxNode->mTreeNodeTxFlags.mValue = 0;

   if (tNextTxNode != 0)
   {
      if (tNextTxNode == mPreviousTxNode->mFirstChildNode)
      {
         tNextTxNode->mTreeNodeTxFlags.mFirstChild = true;
      }
      else if (tNextTxNode == mPreviousTxNode->mParentNode->mLastChildNode)
      {
         tNextTxNode->mTreeNodeTxFlags.mLastChild = true;
      }

   }
   mPreviousTxNode = tNextTxNode;
   return tNextTxNode;
}
}//namespace
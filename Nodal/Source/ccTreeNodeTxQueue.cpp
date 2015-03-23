
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
   mNextTxNode = 0;
}

void TreeNodeTxQueue::putTxNode(TreeNode* aNode)
{
   if (mNextTxNode == 0)
   {
      mNextTxNode = aNode;
   }

   mRootNode->attachAfterLastChild(aNode);
}

TreeNode* TreeNodeTxQueue::getNextTxNode()
{
   TreeNode* tNode = mNextTxNode;
   if (mNextTxNode != 0)
   {
      mNextTxNode = getNextNode(mNextTxNode);
   }
   return tNode;
}
}//namespace
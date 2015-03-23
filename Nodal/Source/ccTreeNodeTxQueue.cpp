
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeTxQueue.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

TreeNodeTxQueue::TreeNodeTxQueue()
: mRootNodeInstance(0,"TxRoot")
{
   mRootNode = &mRootNodeInstance;
   mPreviousTxNode = 0;
}

void TreeNodeTxQueue::putTxNode(LabelledTreeNode* aNode)
{
   if (mPreviousTxNode == 0)
   {
      mPreviousTxNode = aNode;
   }

   mRootNode->attachAfterLastChild(aNode);
}

LabelledTreeNode* TreeNodeTxQueue::getNextTxNode()
{
   LabelledTreeNode* tNextTxNode = (LabelledTreeNode*)getNextNode(mPreviousTxNode);

   if (tNextTxNode != 0)
   {
      tNextTxNode->mTreeNodeTxFlags.mValue = 0;

      if (tNextTxNode == mPreviousTxNode->mFirstChildNode)
      {
         tNextTxNode->mTreeNodeTxFlags.mFirstChild = true;
      }

      if (tNextTxNode == mPreviousTxNode->mParentNode != 0)
      {
         if (tNextTxNode == mPreviousTxNode->mParentNode->mLastChildNode)
         {
            tNextTxNode->mTreeNodeTxFlags.mLastChild = true;
         }
      }
      else
      {
         tNextTxNode->mTreeNodeTxFlags.mLastChild = true;
      }

   }
   mPreviousTxNode = tNextTxNode;
   return tNextTxNode;
}
}//namespace

#include <stdio.h>
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeRxQueue.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

TreeNodeRxQueue::TreeNodeRxQueue()
: mRootNodeInstance(0,"RxRoot")
{
   mRootNode = &mRootNodeInstance;
   mPreviousRxNode = 0;
   mLevel = 0;
}

void TreeNodeRxQueue::putRxNode(LabelledTreeNode* aNode)
{
   if (mPreviousRxNode == 0)
   {
      mRootNode->attachAfterLastChild(aNode);
      mPreviousRxNode = aNode;
      mLevel = 1;
   }
   else
   {
      if (aNode->mTreeNodeTxFlags.mFirstChild)
      {
         mPreviousRxNode->attachBeforeFirstChild(aNode);
         mPreviousRxNode = aNode;
         mLevel++;
      }
      else if (aNode->mTreeNodeTxFlags.mLastChild)
      {
         mPreviousRxNode->mParentNode->attachAfterLastChild(aNode);
         mPreviousRxNode = (LabelledTreeNode*)mPreviousRxNode->mParentNode;
         mLevel--;
      }
      else 
      {
         mPreviousRxNode->mParentNode->attachAfterLastChild(aNode);
         mPreviousRxNode = aNode;
      }
   }
}

LabelledTreeNode* TreeNodeRxQueue::getNextRxNode()
{
   if (mLevel != 1) return 0;

   LabelledTreeNode* tNode = (LabelledTreeNode*)mRootNode->detachFirstChild();
   return tNode;
}
}//namespace
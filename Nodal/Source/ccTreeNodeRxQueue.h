#ifndef _CCTREENODERXQUEUE_H_
#define _CCTREENODERXQUEUE_H_

#include "ccTreeNode.h"
#include "ccTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class TreeNodeClass>
class TreeNodeRxQueue
{
public:
   // Members
   TreeNodeClass  mRootNodeInstance;
   TreeNodeClass* mRootNode;
   TreeNodeClass* mPutNode;

   TreeNode* mParentAtLevel[MaxLevelDepth];

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

   TreeNodeRxQueue()
   {
      mRootNode = &mRootNodeInstance;
      mPutNode = 0;

      for (int i = 0; i < MaxLevelDepth; i++)
      {
         mParentAtLevel[i] = 0;
      }
      mParentAtLevel[0] = mRootNode;
      mParentAtLevel[1] = mRootNode;
   }

   void putRxNode(TreeNodeClass* aNode)
   {

      if (mRootNode->mFirstChildNode==0)
      {
         mRootNode->attachAfterLastChild(aNode);
         aNode->mTxAttachLevel = 1;
         mParentAtLevel[0] = mRootNode;
         mParentAtLevel[1] = mRootNode;
         mPutNode = aNode;
      }
      else
      {
         if (aNode->mTxAttachLevel > mPutNode->mTxAttachLevel)
         {
            mParentAtLevel[aNode->mTxAttachLevel - 1] = mPutNode;
         }
         mParentAtLevel[aNode->mTxAttachLevel - 1]->attachAfterLastChild(aNode);
         mPutNode = aNode;
         mParentAtLevel[aNode->mTxAttachLevel] = mPutNode->mParentNode;
#if 0
         if (aNode->mTxAttachLevel > mPutNode->mTxAttachLevel)
         {
            mParentAtLevel[aNode->mTxAttachLevel + 1] = mPutNode;
            mPutNode->attachBeforeFirstChild(aNode);
            mPutNode = aNode;
         }
         if (aNode->mTreeNodeTxFlags.mIsFirstChild)
         {
            mPutNode->attachBeforeFirstChild(aNode);
            mPutNode = aNode;
         }
         else if (aNode->mTreeNodeTxFlags.mIsLastChild)
         {
            mPutNode->mParentNode->attachAfterLastChild(aNode);
            mPutNode = (TreeNodeClass*)mPutNode->mParentNode;
         }
         else 
         {
            mPutNode->mParentNode->attachAfterLastChild(aNode);
            mPutNode = aNode;
         }
#endif
      }
      if (aNode->mTreeNodeTxFlags.mIsLastInStructure)
      {
         mRootNode->mLastChildNode->mTreeNodeTxFlags.mIsLastInStructure = true;
      }
   }
   void putRxNode22(TreeNodeClass* aNode)
   {
      if (mRootNode->mFirstChildNode==0)
      {
         mRootNode->attachAfterLastChild(aNode);
         mPutNode = aNode;
      }
      else
      {
         if (aNode->mTreeNodeTxFlags.mIsFirstChild)
         {
            mPutNode->attachBeforeFirstChild(aNode);
            mPutNode = aNode;
         }
         else if (aNode->mTreeNodeTxFlags.mIsLastChild)
         {
            mPutNode->mParentNode->attachAfterLastChild(aNode);
            mPutNode = (TreeNodeClass*)mPutNode->mParentNode;
         }
         else 
         {
            mPutNode->mParentNode->attachAfterLastChild(aNode);
            mPutNode = aNode;
         }
      }
      if (aNode->mTreeNodeTxFlags.mIsLastInStructure)
      {
         mRootNode->mLastChildNode->mTreeNodeTxFlags.mIsLastInStructure = true;
      }
   }

   TreeNodeClass* getNextRxNode()
   {
      if (mRootNode->mFirstChildNode == 0)
      {
         return 0;
      }

      if (!mRootNode->mFirstChildNode->mTreeNodeTxFlags.mIsLastInStructure)
      {
         return 0;
      }

      TreeNodeClass* tNode = (TreeNodeClass*)mRootNode->detachFirstChild();
      if (tNode == 0)
      {
      }
      return tNode;
   }
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
#ifndef _CCTREENODETXQUEUE_H_
#define _CCTREENODETXQUEUE_H_

#include "ccTreeNode.h"
#include "ccTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
template <class TreeNodeClass>
class TreeNodeTxQueue
{
public:
   // Members
   TreeNodeClass  mRootNodeInstance;
   TreeNodeClass* mRootNode;

   TreeNodeClass* mPreviousGetNode;
   TreeNodeClass* mGetNode;
   TreeNodeClass* mNextGetNode;

   TreeNodeTxQueue()
   {
      mRootNode = &mRootNodeInstance;
      mPreviousGetNode=0;
      mGetNode=0;
      mNextGetNode=0;
   }

   void putTxNode(TreeNodeClass* aNode)
   {
      if (mRootNode->mFirstChildNode == 0)
      {
         mPreviousGetNode = 0;
         mGetNode         = aNode;
         mNextGetNode     = (TreeNodeClass*)getNextNode(aNode);
      }

      mRootNode->attachAfterLastChild(aNode);
   }

   TreeNodeClass* getNextTxNode()
   {
      if (mGetNode == 0)
      {
         mPreviousGetNode=0;
         mNextGetNode=0;
         return 0;
      }

      if (mGetNode->mParentNode != 0)
      {
         mGetNode->mTreeNodeTxFlags.mIsFirstChild = (mGetNode == mGetNode->mParentNode->mFirstChildNode);
      }
      else
      {
         mGetNode->mTreeNodeTxFlags.mIsFirstChild = false;
      }

      if (mGetNode->mParentNode != 0)
      if (mGetNode->mParentNode != mRootNode)
      {
         mGetNode->mTreeNodeTxFlags.mIsLastChild = (mGetNode == mGetNode->mParentNode->mLastChildNode);
      }
      else
      {
         mGetNode->mTreeNodeTxFlags.mIsLastChild = false;
      }

      TreeNodeClass* tGetNode = mGetNode;

      if (mGetNode->mTreeNodeTxFlags.mIsLastInStructure && false)
      {
         mPreviousGetNode = 0;
         mGetNode = 0;
         mNextGetNode = 0;
      }
      else
      {
         mPreviousGetNode = mGetNode;
         mGetNode = mNextGetNode;
         mNextGetNode = (TreeNodeClass*)getNextNode(mNextGetNode);
      }

      return tGetNode;
   }
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
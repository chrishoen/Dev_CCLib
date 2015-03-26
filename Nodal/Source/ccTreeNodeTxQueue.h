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
   int mTxAttachLevel;

   TreeNodeTxQueue()
   {
      mRootNode = &mRootNodeInstance;
      mPreviousGetNode=0;
      mGetNode=0;
      mNextGetNode=0;
      mTxAttachLevel=0;
   }

   void putTxNode(TreeNodeClass* aNode)
   {
      aNode->mTxAttachLevel = 0;
      mRootNode->attachAfterLastChild(aNode);
   }

   TreeNodeClass* getNextTxNode()
   {
      if (mRootNode->mFirstChildNode == 0 && mGetNode==0)
      {
         return 0;
      }

      if (mGetNode == 0)
      {
         mGetNode = (TreeNodeClass*)mRootNode->detachFirstChild();
      }
      else
      {
         mGetNode = (TreeNodeClass*)getNextNode(mGetNode);
      }

      if (mGetNode == 0)
      {
         mGetNode = (TreeNodeClass*)mRootNode->detachFirstChild();
      }

      if (mGetNode == 0)
      {
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
      {
         if (mGetNode->mParentNode != mRootNode)
         {
            mGetNode->mTreeNodeTxFlags.mIsLastChild = (mGetNode == mGetNode->mParentNode->mLastChildNode);
         }
      }
      else
      {
         mGetNode->mTreeNodeTxFlags.mIsLastChild = false;
      }

      return mGetNode;
   }

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
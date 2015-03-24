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
//    if (mRootNode->mFirstChildNode == 0)
      if (mPreviousGetNode==0)
      {
         mPreviousGetNode = 0;
         mGetNode         = aNode;
         mNextGetNode     = (TreeNodeClass*)getNextNode(aNode);
         mGetNode->mTreeNodeTxFlags.mIsLastInStructure = mNextGetNode == 0;
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

      if (mPreviousGetNode != 0)
      {
         mGetNode->mTreeNodeTxFlags.mIsFirstChild = mGetNode == mPreviousGetNode->mFirstChildNode;
      }
      else
      {
         mGetNode->mTreeNodeTxFlags.mIsFirstChild = false;
      }

      if (mPreviousGetNode != 0)
      {
         mGetNode->mTreeNodeTxFlags.mIsLastChild = mGetNode == mPreviousGetNode->mLastChildNode;
      }
      else
      {
         mGetNode->mTreeNodeTxFlags.mIsLastChild = false;
      }


//    mGetNode->mTreeNodeTxFlags.mIsLastInStructure = mNextGetNode == 0;

      if (mNextGetNode == 0)
      {
         mGetNode->mTreeNodeTxFlags.mIsLastInStructure = true;
      }
      else if (mNextGetNode->mParentNode == mRootNode)
      {
         mGetNode->mTreeNodeTxFlags.mIsLastInStructure = true;
      }
      else
      {
         mGetNode->mTreeNodeTxFlags.mIsLastInStructure = false;
      }

      TreeNodeClass* tGetNode = mGetNode;

      if (mGetNode->mTreeNodeTxFlags.mIsLastInStructure)
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


      if (tGetNode->mTreeNodeTxFlags.mIsLastInStructure)
      {
         printf("LINE201 LastInStructure %d %d\n",tGetNode->mTreeNodeTxFlags.mIsLastInStructure,tGetNode->mIdentifier);
      }


      return tGetNode;
   }
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
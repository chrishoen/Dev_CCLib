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
   TreeNodeClass* mPreviousRxNode;
   bool           mLastChildRxComplete;

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

   TreeNodeRxQueue()
   {
      mRootNode = &mRootNodeInstance;
      mPreviousRxNode = 0;
      mLastChildRxComplete = false;
   }

   void putRxNode(TreeNodeClass* aNode)
   {
      if (mRootNode->mFirstChildNode==0)
      {
         mRootNode->attachAfterLastChild(aNode);
         mPreviousRxNode = aNode;
      }
      else
      {
         if (aNode->mTreeNodeTxFlags.mIsFirstChild)
         {
            mPreviousRxNode->attachBeforeFirstChild(aNode);
            mPreviousRxNode = aNode;
         }
         else if (aNode->mTreeNodeTxFlags.mIsLastChild)
         {
            mPreviousRxNode->mParentNode->attachAfterLastChild(aNode);
            mPreviousRxNode = (TreeNodeClass*)mPreviousRxNode->mParentNode;
//          mPreviousRxNode = aNode;
         }
         else 
         {
            mPreviousRxNode->mParentNode->attachAfterLastChild(aNode);
            mPreviousRxNode = aNode;
         }
      }
//    mLastChildRxComplete = aNode->mTreeNodeTxFlags.mIsLastInStructure;
      if (aNode->mTreeNodeTxFlags.mIsLastInStructure)
      {
         mRootNode->mLastChildNode->mTreeNodeTxFlags.mIsLastInStructure = true;
         printf("AAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
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
      return tNode;
   }
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
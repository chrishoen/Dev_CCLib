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
            mPreviousRxNode = (TreeNodeClass*)mPreviousRxNode->mParentNode;
         }
         else 
         {
            mPreviousRxNode->mParentNode->attachAfterLastChild(aNode);
            mPreviousRxNode = aNode;
         }
      }
   }

   TreeNodeClass* getNextRxNode()
   {
      TreeNodeClass* tNode = (TreeNodeClass*)mRootNode->detachFirstChild();
      return tNode;
   }
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
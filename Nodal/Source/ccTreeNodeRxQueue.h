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
   int               mLevel;

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

   TreeNodeRxQueue()
   {
      mRootNode = &mRootNodeInstance;
      mPreviousRxNode = 0;
      mLevel = 0;
   }

   void putRxNode(TreeNodeClass* aNode)
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
            mPreviousRxNode = (TreeNodeClass*)mPreviousRxNode->mParentNode;
            mLevel--;
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
      if (mLevel != 1) return 0;

      TreeNodeClass* tNode = (TreeNodeClass*)mRootNode->detachFirstChild();
      return tNode;
   }
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
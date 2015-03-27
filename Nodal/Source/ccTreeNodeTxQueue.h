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
      mTxAttachLevel=1;
   }

   void putTxNode(TreeNodeClass* aNode)
   {
      aNode->mTxAttachLevel = 1;
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

      return mGetNode;
   }


};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
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
   TreeNodeClass* mPreviousTxNode;

   TreeNodeTxQueue()
   {
      mRootNode = &mRootNodeInstance;
      mPreviousTxNode = 0;
   }

   void putTxNode(TreeNodeClass* aNode)
   {
      if (mPreviousTxNode == 0)
      {
         mPreviousTxNode = aNode;
      }

      mRootNode->attachAfterLastChild(aNode);
   }

   TreeNodeClass* getNextTxNode()
   {
      TreeNodeClass* tNextTxNode = (TreeNodeClass*)getNextNode(mPreviousTxNode);

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
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
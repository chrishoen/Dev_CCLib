#ifndef _CCTREENODERXQUEUE_H_
#define _CCTREENODERXQUEUE_H_

#include "ccTreeNode.h"
#include "ccTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is a class template for a tree node receive queue. It is used to
// receive tree node structures that were transmitted as a sequence of 
// individual nodes. It is used in conjunction with a tree node transmit
// queue. 
//
// Structured collections are sent to a transmit queue for transmission.
// The structure is deconstructed into a sequnce of individual nodes.
// Individual nodes are gotten from the queue, one at a time, and are 
// transmitted over a communications channel. At the receiving end of the
// channel the individual blocks are put to a tree node receive queue,
// where the tree node structure is reconstructed.

template <class TreeNodeClass>
class TreeNodeRxQueue
{
public:
   // Root node, nodes that are put to the queue are attached here
   TreeNodeClass  mRootNodeInstance;
   TreeNodeClass* mRootNode;

   // Last node that was put to the queue
   TreeNodeClass* mPutNode;

   // This is an array of pointers to parent nodes. It is indexed by the
   // attachment level of nodes that are put to the queue. When a node
   // is put to the queue it is attached as a last child of a parent node
   // that is in this array.
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
   }

   void putRxNode(TreeNodeClass* aNode)
   {

      if (mRootNode->mFirstChildNode==0)
      {
         mRootNode->attachAfterLastChild(aNode);
         aNode->mTxAttachLevel = 1;
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
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
//
// A structure will not be released from a queue until all of its nodes
// have been received.
//
// The templated class must inherit from TreeNode.

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

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Put a node that was received from a communications channel to the queue.

   void putRxNode(TreeNodeClass* aNode)
   {
      // If the queue is empty
      if (mRootNode->mFirstChildNode==0)
      {
         // Attach the node to the root
         mRootNode->attachAfterLastChild(aNode);
         // Set the node level to point to the root
         aNode->mTxAttachLevel = 1;
         // Store the node
         mPutNode = aNode;
      }
      else
      {
         // If the node level is greater than the previous node level
         // then it is a first child of the previous node
         if (aNode->mTxAttachLevel > mPutNode->mTxAttachLevel)
         {
            // Store the previous node in the parent node array
            mParentAtLevel[aNode->mTxAttachLevel - 1] = mPutNode;
         }

         // Attach the node as the last child of the parent node that is 
         // indexed by the node's attachment level
         mParentAtLevel[aNode->mTxAttachLevel - 1]->attachAfterLastChild(aNode);

         // Store the node
         mPutNode = aNode;

         // Store the node's parent in the parent node array
         mParentAtLevel[aNode->mTxAttachLevel] = mPutNode->mParentNode;
      }
      // If the node is the last one of a structure that was transitted
      if (aNode->mTreeNodeTxFlags.mIsLastInStructure)
      {
         // Set the last in structure flag for the last child node of the root.
         // A structure will not be released from the queue until all nodes
         // of the structure have been received.
         mRootNode->mLastChildNode->mTreeNodeTxFlags.mIsLastInStructure = true;
      }
   }

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Get the root node of a node structure that was received. A structure will
// not be released from a queue until all of its nodes have been received.

   TreeNodeClass* getNextRxNode()
   {
      // If the queue is empty return zero
      if (mRootNode->mFirstChildNode == 0)
      {
         return 0;
      }

      // If the first child of the root has not received all of its nodes
      // then return zero
      if (!mRootNode->mFirstChildNode->mTreeNodeTxFlags.mIsLastInStructure)
      {
         return 0;
      }

      // Else detach the first child from the root and return it
      return (TreeNodeClass*)mRootNode->detachFirstChild();
   }
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
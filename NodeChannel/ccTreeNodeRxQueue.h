#ifndef _CCTREENODERXQUEUE_H_
#define _CCTREENODERXQUEUE_H_

#include "ccDefs.h"
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
   TreeNodeClass* mRootNode;

   // Last node that was put to the queue
   TreeNodeClass* mPutNodeP;

   // This is an array of pointers to parent nodes. It is indexed by the
   // attachment level of nodes that are put to the queue. When a node
   // is put to the queue it is attached as a last child of a parent node
   // that is in this array.
   TreeNode* mParentAtLevelP[cMaxLevelDepth];

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

   TreeNodeRxQueue()
   {
      mRootNode = new TreeNodeClass();
      mPutNodeP = 0;

      for (int i = 0; i < cMaxLevelDepth; i++)
      {
         mParentAtLevelP[i] = 0;
      }
      mParentAtLevelP[0] = mRootNode;
   }

  ~TreeNodeRxQueue()
   {
      delete mRootNode;
   }

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Put a node that was received from a communications channel to the queue.

   void putRxNode(TreeNodeClass* aNodeP)
   {
      // If the queue is empty
      if (mRootNode->mFirstChildNodeH == BlockHandle::nullH)
      {
         // Attach the node to the root
         mRootNode->attachAfterLastChild(aNodeP);
         // Set the node level to point to the root
         aNodeP->mTxAttachLevel = 1;
         // Store the node
         mPutNodeP = aNodeP;
      }
      else
      {
         // If the node level is greater than the previous node level
         // then it is a first child of the previous node
         if (aNodeP->mTxAttachLevel > mPutNodeP->mTxAttachLevel)
         {
            // Store the previous node in the parent node array
            mParentAtLevelP[aNodeP->mTxAttachLevel - 1] = mPutNodeP;
         }

         // Attach the node as the last child of the parent node that is 
         // indexed by the node's attachment level
         mParentAtLevelP[aNodeP->mTxAttachLevel - 1]->attachAfterLastChild(aNodeP);

         // Store the node
         mPutNodeP = aNodeP;

         // Store the node's parent in the parent node array
         mParentAtLevelP[aNodeP->mTxAttachLevel] = mPutNodeP->ptrParentNode();
      }
      // If the node is the last one of a structure that was transitted
      if (aNodeP->mTreeNodeTxFlags.mIsLastInStructure)
      {
         // Set the last in structure flag for the last child node of the root.
         // A structure will not be released from the queue until all nodes
         // of the structure have been received.
         mRootNode->ptrLastChildNode()->mTreeNodeTxFlags.mIsLastInStructure = true;
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
      if (mRootNode->mFirstChildNodeH == BlockHandle::nullH)
      {
         return 0;
      }

      // If the first child of the root has not received all of its nodes
      // then return zero
      if (!mRootNode->ptrFirstChildNode()->mTreeNodeTxFlags.mIsLastInStructure)
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
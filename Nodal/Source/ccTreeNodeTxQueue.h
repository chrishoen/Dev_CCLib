#ifndef _CCTREENODETXQUEUE_H_
#define _CCTREENODETXQUEUE_H_

#include "ccTreeNode.h"
#include "ccTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is a class template for a tree node transmit queue. It is used to
// transmit tree node structures as a sequence of individual nodes. It is
// used in conjunction with a tree node receive queue. 
//
// Structured collections are sent to the transmit queue for transmission.
// The structure is deconstructed into a sequnce of individual nodes.
// Individual nodes are gotten from the queue, one at a time, and are 
// transmitted over a communications channel. At the receiving end of the
// channel the individual blocks are put to a tree node receive queue,
// where the tree node structure is reconstructed.


template <class TreeNodeClass>
class TreeNodeTxQueue
{
public:
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Members

   // Root node, nodes that are put to the queue are attached here
   TreeNodeClass  mRootNodeInstance;
   TreeNodeClass* mRootNode;

   // Current node to get from the queue
   TreeNodeClass* mGetNode;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Constructor

   TreeNodeTxQueue()
   {
      mRootNode = &mRootNodeInstance;
      mGetNode=0;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Put the root node of a node structure to the queue for transmission.

   void putTxNode(TreeNodeClass* aNode)
   {
      // Set the attachment level to be a child of the root node
      aNode->mTxAttachLevel = 1;

      // Attach to the root node
      mRootNode->attachAfterLastChild(aNode);
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Get the next node to be transmitted from the queue.

   TreeNodeClass* getNextTxNode()
   {
      // If the queue is empty then return zero
      if (mRootNode->mFirstChildNode == 0 && mGetNode==0)
      {
         return 0;
      }

      // If the previous get node is zero
      if (mGetNode == 0)
      {
         // Detach the first child from the root node to be the get node
         mGetNode = (TreeNodeClass*)mRootNode->detachFirstChild();
      }
      // Else if the previous get node is not zero
      else
      {
         // Set the get node to be the next node of the previous get node
         mGetNode = (TreeNodeClass*)getNextNode(mGetNode);
      }

      // If the get node is zero (the above operation resulted in zero)
      if (mGetNode == 0)
      {
         // Detach the first child from the root node to be the get node
         mGetNode = (TreeNodeClass*)mRootNode->detachFirstChild();
      }

      // Return the get node
      return mGetNode;
   }


};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
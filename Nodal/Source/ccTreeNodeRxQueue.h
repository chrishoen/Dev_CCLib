#ifndef _CCTREENODERXQUEUE_H_
#define _CCTREENODERXQUEUE_H_

#include "ccTreeNode.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class TreeNodeRxQueue
{
public:
   // Constructor
   TreeNodeRxQueue();

   // Members
   TreeNode  mRootNodeInstance;
   TreeNode* mRootNode;
   TreeNode* mPreviousRxNode;

   // Methods
   void putRxNode(TreeNode* aNode);
   TreeNode* getNextRxNode();

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
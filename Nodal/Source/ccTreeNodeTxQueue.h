#ifndef _CCTREENODETXQUEUE_H_
#define _CCTREENODETXQUEUE_H_

#include "ccTreeNode.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class TreeNodeTxQueue
{
public:
   // Constructor
   TreeNodeTxQueue();

   // Members
   TreeNode  mRootNodeInstance;
   TreeNode* mRootNode;
   TreeNode* mNextTxNode;

   // Methods
   void putTxNode(TreeNode* aNode);
   TreeNode* getNextTxNode();

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
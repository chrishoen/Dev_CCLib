#ifndef _CCTREENODETXQUEUE_H_
#define _CCTREENODETXQUEUE_H_

#include "ccLabelledTreeNode.h"

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
   LabelledTreeNode  mRootNodeInstance;
   LabelledTreeNode* mRootNode;
   LabelledTreeNode* mPreviousTxNode;

   // Methods
   void putTxNode(LabelledTreeNode* aNode);
   LabelledTreeNode* getNextTxNode();

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
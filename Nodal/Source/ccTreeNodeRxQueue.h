#ifndef _CCTREENODERXQUEUE_H_
#define _CCTREENODERXQUEUE_H_

#include "ccTreeNode.h"
#include "ccLabelledTreeNode.h"

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
   LabelledTreeNode  mRootNodeInstance;
   LabelledTreeNode* mRootNode;
   LabelledTreeNode* mPreviousRxNode;

   // Methods
   void putRxNode(LabelledTreeNode* aNode);
   LabelledTreeNode* getNextRxNode();

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
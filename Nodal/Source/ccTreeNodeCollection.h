#ifndef _CCTREENODECOLLECTION_H_
#define _CCTREENODECOLLECTION_H_

#include "ccTreeNode.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class TreeNodeCollection
{
public:
   // Constructor
   TreeNodeCollection();

   // Members
   TreeNode  mRootNodeInstance;
   TreeNode* mRootNode;
   int       mSize;
   int       mMaxSize;

   // Methods
   void setMaxSize(int aMaxSize) { mMaxSize = aMaxSize; }
   int  size()                   { return mSize; }
   bool isEmpty()                { return mSize == 0; }
   bool isFull()                 { return mSize == mMaxSize; }

   // Methods
   bool putLast(TreeNode* aSubjectNode);
   TreeNode* getFirst();

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
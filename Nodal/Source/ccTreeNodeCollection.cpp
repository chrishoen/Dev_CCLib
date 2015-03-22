
#include "ccTreeNodeCollection.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

TreeNodeCollection::TreeNodeCollection()
{
   mRootNode = &mRootNodeInstance;
}

bool TreeNodeCollection::putLast(TreeNode* aSubjectNode)
{
   if (mSize < mMaxSize)
   {
      aSubjectNode->attachAfterLastChild(mRootNode);
      mSize++;
      return true;
   }
   else
   {
      return false;
   }
}

TreeNode* TreeNodeCollection::getFirst()
{
   if (mSize == 0) return 0;

   TreeNode* tSubjectNode = mRootNode->detachFirstChild();
   if (tSubjectNode)
   {
      mSize--;
   }
   return tSubjectNode;
}
}//namespace

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

bool TreeNodeCollection::putLast(TreeNode* aObjectNode)
{
   if (mSize < mMaxSize)
   {
      mRootNode->attachAfterLastChild(aObjectNode);
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

   TreeNode* tObjectNode = mRootNode->detachFirstChild();
   if (tObjectNode)
   {
      mSize--;
   }
   return tObjectNode;
}
}//namespace
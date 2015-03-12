
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccLabelledTreeNode.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor

LabelledTreeNode::LabelledTreeNode()
{
   // Empty string
   strncpy(mLabel, "/", MaxLabelSize);
   strncpy(mFullPath, "/", MaxFullPathSize);

}

LabelledTreeNode::LabelledTreeNode(int aIdentifier,char* aLabel)
{
   mIdentifier = aIdentifier;
   strncpy(mLabel, aLabel, MaxLabelSize);
   strncpy(mFullPath, aLabel, MaxFullPathSize);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is called on an object node after it is attached to a subject node

void LabelledTreeNode::onAttached()
{
   if (mParentNode==0) return;
   LabelledTreeNode* tParentNode = static_cast<LabelledTreeNode*>(mParentNode);

   strncpy(mFullPath, tParentNode->mFullPath, MaxFullPathSize);
   strncat(mFullPath, ".", MaxFullPathSize);
   strncat(mFullPath, mLabel, MaxFullPathSize);
   return;

   printf("objectNodeOnAttached %d %s %s\n", 
      this->mIdentifier,
      this->mLabel,
      this->mFullPath);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
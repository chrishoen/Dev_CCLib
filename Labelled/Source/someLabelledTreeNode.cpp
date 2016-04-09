/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <new>
#include "prnPrint.h"

#include "someLabelledTreeNode.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

LabelledTreeNode::LabelledTreeNode()
{
   // Empty string
   strncpy(mLabel, "/", MaxLabelSize);
   strncpy(mFullPath, "/", MaxFullPathSize);
}

// Constructor, it is called by create after allocation of a new block.

LabelledTreeNode::LabelledTreeNode(int aIdentifier,char* aLabel)
{
   // Empty string
   strncpy(mLabel, "/", MaxLabelSize);
   strncpy(mFullPath, "/", MaxFullPathSize);

   // Identifier
   mIdentifier = aIdentifier;

   // Label and full path
   if (aLabel)
   {
      strncpy(mLabel, aLabel, MaxLabelSize);
      strncpy(mFullPath, aLabel, MaxFullPathSize);
   }
}

void LabelledTreeNode::setLabel(char* aLabel)
{
   strncpy(mLabel, aLabel, MaxLabelSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This gets the full path label of a subject node

char* LabelledTreeNode::getFullPath()
{
   if (mParentNodeH == CC::BlockHandle::nullH)
   {
      strncpy(mFullPath, mLabel, MaxFullPathSize);
      return mFullPath;
   }
   else
   {
      LabelledTreeNode* tParentNode = static_cast<LabelledTreeNode*>(this->ptrParentNode());

      strncpy(mFullPath, tParentNode->getFullPath(), MaxFullPathSize);
      strncat(mFullPath, ".", MaxFullPathSize);
      strncat(mFullPath, mLabel, MaxFullPathSize);
      return mFullPath;
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
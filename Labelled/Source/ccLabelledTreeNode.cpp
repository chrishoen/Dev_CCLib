
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>
#include "ccLabelledTreeNode.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance of the block pool

CC::BlockPool LabelledTreeNode::mBlockPool;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create with specified member variables

LabelledTreeNode* LabelledTreeNode::create (int aIdentifier,char* aLabel)
{ 
   // Block pointer.
   LabelledTreeNode* tPointer = 0;

   // Allocate a block from the block pool.
   tPointer = (LabelledTreeNode*)mBlockPool.get();

   // Call the constructor on the allocated block using placement new.
   new(tPointer)LabelledTreeNode(aIdentifier,aLabel);

   // Return the pointer to the allocated block.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This method calls the class destructor and then deallocates the object
// from system memory or from block universe short term or long term
// memory block pools. It is analogous to delete.

void LabelledTreeNode::destroy()
{
   CC::BlockPoolBlock<LabelledTreeNode>::deallocate();
}

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
   if (mParentNode == 0)
   {
      strncpy(mFullPath, mLabel, MaxFullPathSize);
      return mFullPath;
   }
   else
   {
      LabelledTreeNode* tParentNode = static_cast<LabelledTreeNode*>(mParentNode);

      strncpy(mFullPath, tParentNode->getFullPath(), MaxFullPathSize);
      strncat(mFullPath, ".", MaxFullPathSize);
      strncat(mFullPath, mLabel, MaxFullPathSize);
      return mFullPath;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
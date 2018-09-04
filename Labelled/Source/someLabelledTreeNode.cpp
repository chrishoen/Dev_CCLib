/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "ccBlockPool.h"
#include "someBlockPoolIndex.h"
#include "someLabelledTreeNode.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate a block from the block pool at the given block pool index.
// Return a pointer to the allocated block.
// Return null if the block pool is empty.

void* LabelledTreeNode::operator new(size_t sz)
{
   // Block pointer.
   void* tBlockPointer = 0;

   // Try to allocate a block from the block pool.
   CC::allocateBlockPoolBlock(Some::cBlockPoolIndex_LabelledTreeNode, (void**)&tBlockPointer, 0);

   // Return the pointer to the allocated block.
   // Return null if the block pool is empty.
   return tBlockPointer;
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Deallocate a block from the block pool.

void LabelledTreeNode::operator delete(void* ptr)
{
   // Deallocate the block back to the block pool
   CC::deallocateBlockPoolBlock(ptr);
}

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
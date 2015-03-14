
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

// Static member block universe. It contains a short term and a long term
// block pool. These block pools, or system memory, are used to establish
// memory for all instances of this class that are created within a process.
// The block universe must be initialized at the beginning of a process, 
// prior to any block creation.

CC::BlockUniverse LabelledTreeNode::mBlockUniverse;

// This static member specifies the default memory type. If a create is
// called without a memory type parameter then this variable is used.

int LabelledTreeNode::mDefaultMemoryType = CC::MemoryType_LongTerm;

// This static method initializes the block universe. In a process, it must
// be called prior to any block creations. It initializes the block universe
// short term and long term block pools.

void LabelledTreeNode::initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks)
{
   LabelledTreeNode::mBlockUniverse.initialize(
      aAllocateShortTermBlocks,
      aAllocateLongTermBlocks,
      sizeof(LabelledTreeNode));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This static method allocates a block from system memory or from block
// universe short term or long term memory block pools. After allocation,
// it calls the class constructor on the allocated block. The memory type
// parameter specifies either system memory, or short term block pool,
// or long term block pool. It is analogous to new.

LabelledTreeNode* LabelledTreeNode::create(int aMemoryType,int aIdentifier,char* aLabel)
{
   // Block pointer
   LabelledTreeNode* tPointer = 0;

   // Allocate memory for the block
   switch (aMemoryType)
   {
   case CC::MemoryType_System :
      // Allocate a block from system memory
      tPointer = (LabelledTreeNode*)malloc(sizeof(LabelledTreeNode));
      break;
   case CC::MemoryType_ShortTerm :
      // Allocate a block from the short term block pool
      tPointer = (LabelledTreeNode*)LabelledTreeNode::mBlockUniverse.mShortTermBlockPool.get();
      break;
   case CC::MemoryType_LongTerm :
      // Allocate a block from the long term block pool
      tPointer = (LabelledTreeNode*)LabelledTreeNode::mBlockUniverse.mLongTermBlockPool.get();
      break;
   }

   // Call the constructor on the allocated block using placement new
   tPointer = new(tPointer)LabelledTreeNode(aIdentifier,aLabel);

   // Store block memory type
   tPointer->mMemoryType = aMemoryType;

   // Return the allocated block
   return tPointer;
}

//******************************************************************************
// Create with default memory type and default member variables

LabelledTreeNode* LabelledTreeNode::create()
{ 
   return LabelledTreeNode::create(LabelledTreeNode::mDefaultMemoryType, 0, 0);
}

//******************************************************************************
// Create with specifed memory type and default member variables

LabelledTreeNode* LabelledTreeNode::create (int aMemoryType)
{ 
   return LabelledTreeNode::create(aMemoryType, 0, 0);
}

//******************************************************************************
// Create with default memory type and specified member variables

LabelledTreeNode* LabelledTreeNode::create (int aIdentifier,char* aLabel)
{ 
   return LabelledTreeNode::create(LabelledTreeNode::mDefaultMemoryType, aIdentifier, aLabel);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This method calls the class destructor and then deallocates the object
// from system memory or from block universe short term or long term
// memory block pools. It is analogous to delete.

void LabelledTreeNode::destroy()
{
   // Call the block's destructor
   this->~LabelledTreeNode();

   // Deallocate memory for the block
   switch (this->mMemoryType)
   {
   case CC::MemoryType_System :
      // Deallocate the block back to system memory
      free(this);
      break;
   case CC::MemoryType_ShortTerm :
      // Deallocate the block back to the short term block pool
      break;
   case CC::MemoryType_LongTerm :
      // Deallocate the block back to the long term block pool
      LabelledTreeNode::mBlockUniverse.mLongTermBlockPool.put(this);
      break;
   }
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destructor, it is called by destroy before deallocation of a block.

LabelledTreeNode::~LabelledTreeNode()
{
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
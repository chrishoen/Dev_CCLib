
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>
#include "ccNodeBlock.h"

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

CC::BlockUniverse NodeBlock::mBlockUniverse;

// This static member specifies the default memory type. If a create is
// called without a memory type parameter then this variable is used.

int NodeBlock::mDefaultMemoryType = CC::MemoryType_LongTerm;

// This static method initializes the block universe. In a process, it must
// be called prior to any block creations. It initializes the block universe
// short term and long term block pools.

void NodeBlock::initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks)
{
   NodeBlock::mBlockUniverse.initialize(
      aAllocateShortTermBlocks,
      aAllocateLongTermBlocks,
      sizeof(NodeBlock));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This static method allocates a block from system memory or from block
// universe short term or long term memory block pools. After allocation,
// it calls the class constructor on the allocated block. The memory type
// parameter specifies either system memory, or short term block pool,
// or long term block pool. It is analogous to new.

NodeBlock* NodeBlock::create(int aMemoryType,int aIdentifier)
{
   // Block pointer
   NodeBlock* tPointer = 0;

   // Allocate memory for the block
   switch (aMemoryType)
   {
   case CC::MemoryType_System :
      // Allocate a block from system memory
      tPointer = (NodeBlock*)malloc(sizeof(NodeBlock));
      break;
   case CC::MemoryType_ShortTerm :
      // Allocate a block from the short term block pool
      tPointer = (NodeBlock*)NodeBlock::mBlockUniverse.mShortTermBlockPool.get();
      break;
   case CC::MemoryType_LongTerm :
      // Allocate a block from the long term block pool
      tPointer = (NodeBlock*)NodeBlock::mBlockUniverse.mLongTermBlockPool.get();
      break;
   }

   // Call the constructor on the allocated block using placement new
   tPointer = new(tPointer)NodeBlock(aIdentifier);

   // Store block memory type
   tPointer->mMemoryType = aMemoryType;

   // Return the allocated block
   return tPointer;
}

//******************************************************************************
// Create with default memory type and default member variables

NodeBlock* NodeBlock::create()
{ 
   return NodeBlock::create(NodeBlock::mDefaultMemoryType, 0);
}

//******************************************************************************
// Create with default memory type and specified member variables

NodeBlock* NodeBlock::create (int aIdentifier)
{ 
   return NodeBlock::create(NodeBlock::mDefaultMemoryType, aIdentifier);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This method calls the class destructor and then deallocates the object
// from system memory or from block universe short term or long term
// memory block pools. It is analogous to delete.

void NodeBlock::destroy()
{
   // Deallocate memory for the block
   switch (this->mMemoryType)
   {
   case CC::MemoryType_System :
      // Call the block's destructor
      this->~NodeBlock();
      // Deallocate the block back to system memory
      free(this);
      break;
   case CC::MemoryType_ShortTerm :
      // Deallocate the block back to the short term block pool
      break;
   case CC::MemoryType_LongTerm :
      // Call the block's destructor
      this->~NodeBlock();
      // Deallocate the block back to the long term block pool
      NodeBlock::mBlockUniverse.mLongTermBlockPool.put(this);
      break;
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

NodeBlock::NodeBlock()
{
   mData = 101;
}

// Constructor, it is called by create after allocation of a new block.

NodeBlock::NodeBlock(int aIdentifier)
{
   // Identifier
   mIdentifier = aIdentifier;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destructor, it is called by destroy before deallocation of a block.

NodeBlock::~NodeBlock()
{
   return;
   printf("NodeBlock::~NodeBlock     %5d\n",
      this->mIdentifier);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is called on an object node after it is attached to a subject node

void NodeBlock::onAttached()
{
   if (mParentNode==0) return;
#if 0
   printf("objectNodeOnAttached %5d %s\n", 
      this->mIdentifier,
      this->mFullPath);
#endif
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
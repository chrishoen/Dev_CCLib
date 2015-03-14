/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <new>
#include "prnPrint.h"

#include "someBlock2.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Static member block universe. It contains a short term and a long term
// block pool. These block pools, or system memory, are used to establish
// memory for all instances of this class that are created within a process.
// The block universe must be initialized at the beginning of a process, 
// prior to any block creation.

CC::BlockUniverse Block2A::mBlockUniverse;
CC::BlockUniverse Block2B::mBlockUniverse;

// This static method initializes the block universe. In a process, it must
// be called prior to any block creations. It initializes the block universe
// short term and long term block pools.

void Block2A::initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks)
{
   Block2A::mBlockUniverse.initialize(
      aAllocateShortTermBlocks,
      aAllocateLongTermBlocks,
      sizeof(Block2A));
}

// This static method initializes the block universe. In a process, it must
// be called prior to any block creations. It initializes the block universe
// short term and long term block pools.

void Block2B::initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks)
{
   Block2B::mBlockUniverse.initialize(
      aAllocateShortTermBlocks,
      aAllocateLongTermBlocks,
      sizeof(Block2B));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This static method allocates a block from system memory or from block
// universe short term or long term memory block pools. After allocation,
// it calls the class constructor on the allocated block. The memory type
// parameter specifies either system memory, or short term block pool,
// or long term block pool. It is analogous to new.

Block2A* Block2A::create(int aMemoryType)
{
   // Block pointer
   Block2A* tPointer = 0;

   // Allocate memory for the block
   switch (aMemoryType)
   {
   case CC::MemoryType_System :
      // Allocate a block from system memory
      tPointer = (Block2A*)malloc(sizeof(Block2A));
      break;
   case CC::MemoryType_ShortTermWithDestructor :
   case CC::MemoryType_ShortTermWithoutDestructor :
      // Allocate a block from the short term block pool
      tPointer = (Block2A*)Block2A::mBlockUniverse.mShortTermBlockPool.get();
      break;
   case CC::MemoryType_LongTerm :
      // Allocate a block from the long term block pool
      tPointer = (Block2A*)Block2A::mBlockUniverse.mLongTermBlockPool.get();
      break;
   }

   // Call the constructor on the allocated block using placement new
   tPointer = new(tPointer)Block2A;

   // Store block memory type
   tPointer->mMemoryType = aMemoryType;

   // Return the allocated block
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This method calls the class destructor and then deallocates the object
// from system memory or from block universe short term or long term
// memory block pools. It is analogous to delete.

void Block2A::destroy()
{
   // Deallocate memory for the block
   switch (this->mMemoryType)
   {
   case CC::MemoryType_System :
      // Call the block's destructor
      this->~Block2A();
      // Deallocate the block back to system memory
      free(this);
      break;
   case CC::MemoryType_ShortTermWithDestructor :
      // Call the block's destructor
      this->~Block2A();
      // Deallocate the block back to the short term block pool
      break;
   case CC::MemoryType_ShortTermWithoutDestructor :
      // Deallocate the block back to the short term block pool
      break;
   case CC::MemoryType_LongTerm :
      // Call the block's destructor
      this->~Block2A();
      // Deallocate the block back to the long term block pool
      Block2A::mBlockUniverse.mLongTermBlockPool.put(this);
      break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, it is called by create after allocation of a new block.

Block2A::Block2A()
{
   mMemoryType = 0;
   Prn::print(0, 0, "Block2A::Block2A");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destructor, it is called by destroy before deallocation of a block.

Block2A::~Block2A()
{
   Prn::print(0, 0, "Block2A::~Block2A");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This static method allocates a block from system memory or from block
// universe short term or long term memory block pools. After allocation,
// it calls the class constructor on the allocated block. The memory type
// parameter specifies either system memory, or short term block pool,
// or long term block pool. It is analogous to new.

Block2B* Block2B::create(int aMemoryType)
{
   // Block pointer
   Block2B* tPointer = 0;

   // Allocate memory for the block
   switch (aMemoryType)
   {
   case CC::MemoryType_System :
      // Allocate a block from system memory
      tPointer = (Block2B*)malloc(sizeof(Block2B));
      break;
   case CC::MemoryType_ShortTermWithDestructor :
   case CC::MemoryType_ShortTermWithoutDestructor :
      // Allocate a block from the short term block pool
      tPointer = (Block2B*)Block2B::mBlockUniverse.mShortTermBlockPool.get();
      break;
   case CC::MemoryType_LongTerm :
      // Allocate a block from the long term block pool
      tPointer = (Block2B*)Block2B::mBlockUniverse.mLongTermBlockPool.get();
      break;
   }

   // Call the constructor on the allocated block using placement new
   tPointer = new(tPointer)Block2B;

   // Store block memory type
   tPointer->mMemoryType = aMemoryType;

   // Return the allocated block
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This method calls the class destructor and then deallocates the object
// from system memory or from block universe short term or long term
// memory block pools. It is analogous to delete.

void Block2B::destroy()
{
   // Deallocate memory for the block
   switch (this->mMemoryType)
   {
   case CC::MemoryType_System :
      // Call the block's destructor
      this->~Block2B();
      // Deallocate the block back to system memory
      free(this);
      break;
   case CC::MemoryType_ShortTermWithDestructor :
      // Call the block's destructor
      this->~Block2B();
      // Deallocate the block back to the short term block pool
      break;
   case CC::MemoryType_ShortTermWithoutDestructor :
      // Deallocate the block back to the short term block pool
      break;
   case CC::MemoryType_LongTerm :
      // Call the block's destructor
      this->~Block2B();
      // Deallocate the block back to the long term block pool
      Block2B::mBlockUniverse.mLongTermBlockPool.put(this);
      break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, it is called by create after allocation of a new block.

Block2B::Block2B()
{
   Prn::print(0, 0, "Block2B::Block2B");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destructor, it is called by destroy before deallocation of a block.

Block2B::~Block2B()
{
   Prn::print(0, 0, "Block2B::~Block2B");
}


   
}//namespace
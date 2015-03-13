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

CC::BlockUniverse Block2A::mBlockUniverse;
CC::BlockUniverse Block2B::mBlockUniverse;

void Block2A::initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks)
{
   Block2A::mBlockUniverse.initialize(
      aAllocateShortTermBlocks,
      aAllocateLongTermBlocks,
      sizeof(Block2A));
}

void Block2B::initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks)
{
   Block2B::mBlockUniverse.initialize(
      aAllocateShortTermBlocks,
      aAllocateLongTermBlocks,
      sizeof(Block2A));
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

Block2A::Block2A()
{
   mMemoryType = 0;
   Prn::print(0, 0, "Block2A::Block2A");
}

Block2A::~Block2A()
{
   Prn::print(0, 0, "Block2A::~Block2A");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
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
   case CC::MemoryType_ShortTerm :
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
void Block2A::destroy()
{
   // Call the block's destructor
   this->~Block2A();

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
      Block2A::mBlockUniverse.mLongTermBlockPool.put(this);
      break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

Block2B::Block2B()
{
   Prn::print(0, 0, "Block2B::Block2B");
}

Block2B::~Block2B()
{
   Prn::print(0, 0, "Block2B::~Block2B");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
Block2B* Block2B::create(int aMemoryType)
{
   // Allocate a block from the block pool
   Block2B* tPointer = (Block2B*)Block2B::mBlockUniverse.mLongTermBlockPool.get();

   // Call the constructor on the allocated block using placement new
   tPointer = new(tPointer)Block2B;

   // Store memory type
   tPointer->mMemoryType = aMemoryType;

   // Return the allocated block
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
void Block2B::destroy()
{
   // Call the block's destructor
   this->~Block2B();

   // Deallocate the block back to the block pool
   Block2B::mBlockUniverse.mLongTermBlockPool.put(this);
}

   
}//namespace
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

CC::LongTermBlockPool Block2A::mLongTermBlockPool;
CC::LongTermBlockPool Block2B::mLongTermBlockPool;

void Block2A::initializeMemory(int aAllocate)
{
   int tBlockSize = sizeof(Block2A);
   Block2A::mLongTermBlockPool.initialize(aAllocate, tBlockSize);
}

void Block2B::initializeMemory(int aAllocate)
{
   int tBlockSize = sizeof(Block2B);
   Block2B::mLongTermBlockPool.initialize(aAllocate, tBlockSize);
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
   // Allocate a block from the block pool
   Block2A* tPointer = (Block2A*)Block2A::mLongTermBlockPool.get();

   // Call the constructor on the allocated block using placement new
   tPointer = new(tPointer)Block2A;

   // Store memory type
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

   // Deallocate the block back to the block pool
   Block2A::mLongTermBlockPool.put(this);
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
   Block2B* tPointer = (Block2B*)Block2B::mLongTermBlockPool.get();

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
   Block2B::mLongTermBlockPool.put(this);
}

   
}//namespace
/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "someBlock2.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

CC::LongTermBlockPool Block2A::mLongTermBlockPool;
int Block2A::mMemoryType = 0;

void Block2A::initializeMemory(int aAllocate)
{
   int tBlockSize = sizeof(Block2A);
   mLongTermBlockPool.initialize(aAllocate, tBlockSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

Block2A::Block2A()
{
   Prn::print(0, 0, "Block2A::Block2A");
}

Block2A::~Block2A()
{
   Prn::print(0, 0, "Block2A::~Block2A");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void* Block2A::operator new(size_t sz)
{
   Prn::print(0, 0, "Block2A::new");

   if (mMemoryType == 0)
   {
      return ::operator new(sz);
   }
   else if (mMemoryType == 1)
   {
      Block2A* tPointer = (Block2A*)mLongTermBlockPool.get();
      return ::operator new(sz,tPointer);
   }
   return 0;
}

void Block2A::operator delete(void* ptr)
{
   Prn::print(0, 0, "Block2A::delete");

   if (mMemoryType == 0)
   {
      ::operator delete(ptr);
   }
   else if (mMemoryType == 1)
   {
      Block2A* tPointer = (Block2A*)mLongTermBlockPool.get();
      mLongTermBlockPool.put(ptr);
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

   
}//namespace
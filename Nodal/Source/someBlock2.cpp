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
// return mLongTermBlockPool.get();
   return ::operator new(sz);
}
  
void Block2A::operator delete(void* ptr)
{
   Prn::print(0, 0, "Block2A::delete");
// mLongTermBlockPool.put(ptr);
   ::operator delete(ptr);
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
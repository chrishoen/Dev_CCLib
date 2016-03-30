/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "someMyBlock.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MyBlock::MyBlock()
{
   Prn::print(0, "MyBlock::MyBlock");
   mCode1A=101;
}

MyBlock::~MyBlock()
{
   Prn::print(0, "MyBlock::~MyBlock");
}

void MyBlock::method1A()
{
   Prn::print(0, "MyBlock::method1A %d",mCode1A);
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// This allocates a block from the block pool and uses placement new
// to call the class constructor. It is analogous to new.

MyBlock* MyBlock::allocate()
{
   // Block pointer.
   MyBlock* tBlockPointer = 0;
   // Block handle.
   CC::MemHandle tMemHandle;

   // Allocate a block from the block pool.
   CC::allocateMemPoolBlock(CC::cMemPoolIndex_MyBlock,(void**)&tBlockPointer,&tMemHandle);

   // Call the constructor on the allocated block using placement new.
   new(tBlockPointer)MyBlock();

   // Set the allocated block memory handle.
   tBlockPointer->mMemHandle = tMemHandle;

   // Return the pointer to the allocated block.
   return tBlockPointer;
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// This deallocates the object back to the block pool. It does not call
// a destructor for the object.
void MyBlock::deallocate()
{
   // Deallocate the block back to the block pool
   deallocateMemPoolBlock(this->mMemHandle);
}

}//namespace
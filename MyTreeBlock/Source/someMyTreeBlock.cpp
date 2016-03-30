/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "someBlockPoolIndex.h"
#include "someMyTreeBlock.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MyTreeBlock::MyTreeBlock()
{
   Prn::print(0, "MyTreeBlock::MyTreeBlock");
   mCode1A=101;
}

MyTreeBlock::~MyTreeBlock()
{
   Prn::print(0, "MyTreeBlock::~MyTreeBlock");
}

void MyTreeBlock::method1A()
{
   Prn::print(0, "MyTreeBlock::method1A %d",mCode1A);
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// This allocates a block from the block pool and uses placement new
// to call the class constructor. It is analogous to new.

MyTreeBlock* MyTreeBlock::allocate()
{
   // Block pointer.
   MyTreeBlock* tBlockPointer = 0;
   // Block handle.
   CC::BlockHandle tBlockHandle;

   // Allocate a block from the block pool.
   CC::allocateBlockPoolBlock(cBlockPoolIndex_MyTreeBlock,(void**)&tBlockPointer,&tBlockHandle);

   // Call the constructor on the allocated block using placement new.
   new(tBlockPointer)MyTreeBlock();

   // Set the allocated block memory handle.
   tBlockPointer->mBlockHandle = tBlockHandle;

   // Return the pointer to the allocated block.
   return tBlockPointer;
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// This deallocates the object back to the block pool. It does not call
// a destructor for the object.
void MyTreeBlock::deallocate()
{
   // Deallocate the block back to the block pool
   deallocateBlockPoolBlock(this->mBlockHandle);
}

}//namespace
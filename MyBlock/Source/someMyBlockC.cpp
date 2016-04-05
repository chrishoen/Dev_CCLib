/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "someBlockPoolIndex.h"
#include "someMyBlockC.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MyBlockC::MyBlockC()
{
   Prn::print(0, "MyBlockC::MyBlockC");
   mCode1A=101;
}

MyBlockC::~MyBlockC()
{
   Prn::print(0, "MyBlockC::~MyBlockC");
}

void MyBlockC::method1C()
{
   Prn::print(0, "MyBlockC::method1C %d",mCode1A);
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// This allocates a block from the block pool and uses placement new
// to call the class constructor. It is analogous to new.

MyBlockC* MyBlockC::allocateC()
{
   // Block pointer.
   MyBlockC* tBlockPointer = 0;
   // Block handle.
   CC::BlockHandle tBlockHandle;

   // Allocate a block from the block pool.
   CC::allocateBlockPoolBlock(cBlockPoolIndex_MyBlockC,(void**)&tBlockPointer,&tBlockHandle);

   // Call the constructor on the allocated block using placement new.
   new(tBlockPointer)MyBlockC();

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
void MyBlockC::deallocateC()
{
   // Deallocate the block back to the block pool
   deallocateBlockPoolBlock(this->mBlockHandle);
}

}//namespace
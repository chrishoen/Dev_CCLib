/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "someBlockPoolIndex.h"
#include "someMyBlockB.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MyBlockB::MyBlockB()
{
   Prn::print(0, "MyBlockB::MyBlockB");
   mCode1B=101;
}

MyBlockB::~MyBlockB()
{
   Prn::print(0, "MyBlockB::~MyBlockB");
}

void MyBlockB::method1B()
{
   Prn::print(0, "MyBlockB::method1B %d",mCode1B);
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// This allocates a block from the block pool and uses placement new
// to call the class constructor. It is analogous to new.

MyBlockB* MyBlockB::allocate()
{
   // Block pointer.
   MyBlockB* tBlockPointer = 0;
   // Block handle.
   CC::BlockHandle tBlockHandle;

   // Bllocate a block from the block pool.
   CC::allocateBlockPoolBlock(cBlockPoolIndex_MyBlockB,(void**)&tBlockPointer,&tBlockHandle);

   // Call the constructor on the allocated block using placement new.
   new(tBlockPointer)MyBlockB();

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
void MyBlockB::deallocate()
{
   // Deallocate the block back to the block pool
   deallocateBlockPoolBlock(this->mBlockHandle);
}

}//namespace
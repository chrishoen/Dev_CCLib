/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <new>
#include "prnPrint.h"

#include "ccBlockPoolList.h"
#include "someBlockPoolIndex.h"
#include "someBlockPoolIndex.h"
#include "someMyTestBlock.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create with specified member variables

MyTestBlock* MyTestBlock::create (int aIdentifier)
{ 
   // Block pointer.
   MyTestBlock* tBlockPointer = 0;
   // Block handle.
   CC::BlockHandle tBlockHandle;

   // Allocate a block from the block pool.
   CC::allocateBlockPoolBlock(cBlockPoolIndex_MyTestBlock,(void**)&tBlockPointer,&tBlockHandle);

   // Call the constructor on the allocated block using placement new.
   new(tBlockPointer)MyTestBlock(aIdentifier);

   // Set the allocated block memory handle.
   tBlockPointer->mBlockHandle = tBlockHandle;

   // Return the pointer to the allocated block.
   return tBlockPointer;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

MyTestBlock::MyTestBlock()
{
   mIdentifier = 0;
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;
}

// Constructor, it is called by create after allocation of a new block.

MyTestBlock::MyTestBlock(int aIdentifier)
{
   mIdentifier = aIdentifier;
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void MyTestBlock::method1A()
{
   Prn::print(0, "MyTestBlock::method1A %d",mCode1);
}
}//namespace
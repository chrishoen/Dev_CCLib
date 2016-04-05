/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <new>
#include "prnPrint.h"

#include "ccBlockPoolCentral.h"
#include "ccBlockPoolBlockIntrusive.h"
#include "someBlockPoolIndex.h"
#include "someMyTreeBlock.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate a block from the block pool and call its constructor.

MyTreeBlock* MyTreeBlock::create (int aIdentifier)
{ 
   // Allocate a block from the block pool.
   // Call the constructor on the allocated block using placement new.
   // Set the allocated block memory handle.
   // Return a pointer to the allocated block.

   return CC::createBlockIntrusive<MyTreeBlock,cBlockPoolIndex_MyTreeBlock>(aIdentifier);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Default Constructor.

MyTreeBlock::MyTreeBlock()
{
   mIdentifier = 0;
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

MyTreeBlock::MyTreeBlock(int aIdentifier)
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

void MyTreeBlock::method1A()
{
   Prn::print(0, "MyTreeBlock::method1A %d",mCode1);
}

}//namespace
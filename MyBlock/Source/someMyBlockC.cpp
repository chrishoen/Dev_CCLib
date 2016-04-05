/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <new>
#include "prnPrint.h"

#include "ccBlockPoolCentral.h"
#include "ccBlockPoolBlockNonIntrusive.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockC.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate a block from the block pool and call its constructor.

MyBlockC* MyBlockC::create ()
{ 
   // Allocate a block from the block pool.
   // Call the constructor on the allocated block using placement new.
   // Set the allocated block memory handle.
   // Return a pointer to the allocated block.

   return CC::createBlockNonIntrusive<MyBlockC,cBlockPoolIndex_MyBlockC>();
}

MyBlockC* MyBlockC::create (int aIdentifier)
{ 
   // Allocate a block from the block pool.
   // Call the constructor on the allocated block using placement new.
   // Set the allocated block memory handle.
   // Return a pointer to the allocated block.

   return CC::createBlockNonIntrusive<MyBlockC,cBlockPoolIndex_MyBlockC>(aIdentifier);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This method deallocates the object from the block pool from which it was
// created. It does not call a class destructor.

void MyBlockC::destroy()
{
   // Deallocate the block back to the block pool
   CC::deallocateBlockPoolBlock(this);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Default Constructor.

MyBlockC::MyBlockC()
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

MyBlockC::MyBlockC(int aIdentifier)
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

void MyBlockC::method1()
{
   Prn::print(0, "MyBlockC::method1 %d",mIdentifier);
}

}//namespace
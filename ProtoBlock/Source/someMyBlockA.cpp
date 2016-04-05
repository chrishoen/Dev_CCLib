/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "ccBlockPoolCentral.h"
#include "ccBlockPoolBlockIntrusive.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockA.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate a block from the block pool and call its constructor.

MyBlockA* MyBlockA::create ()
{ 
   // Allocate a block from the block pool.
   // Call the constructor on the allocated block using placement new.
   // Set the allocated block memory handle.
   // Return a pointer to the allocated block.

   return CC::createBlockIntrusive<MyBlockA,cBlockPoolIndex_MyBlockA>();
}

MyBlockA* MyBlockA::create (int aIdentifier)
{ 
   // Allocate a block from the block pool.
   // Call the constructor on the allocated block using placement new.
   // Set the allocated block memory handle.
   // Return a pointer to the allocated block.

   return CC::createBlockIntrusive<MyBlockA,cBlockPoolIndex_MyBlockA>(aIdentifier);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This method deallocates the object from the block pool from which it was
// created. It does not call a class destructor.

void MyBlockA::destroy()
{
   // Deallocate the block back to the block pool
   CC::deallocateBlockPoolBlock(this->mBlockHandle);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Default Constructor.

MyBlockA::MyBlockA()
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

MyBlockA::MyBlockA(int aIdentifier)
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

void MyBlockA::method1()
{
   Prn::print(0, "MyBlockA::method1 %d",mIdentifier);
}

}//namespace
/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "ccBlockPoolCentral.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockS.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate a block from the block pool at the given block pool index.
// Return a pointer to the allocated block.
// Return null if the block pool is empty.

void* MyBlockS::operator new(size_t sz)
{
   Prn::print(0, "MyBlockS::new   %d",(int)sz);

   // Block pointer.
   void* tBlockPointer = 0;

   // Try to allocate a block from the block pool.
   CC::allocateBlockPoolBlock(Some::cBlockPoolIndex_MyBlockS, (void**)&tBlockPointer, 0);

   // Return the pointer to the allocated block.
   // Return null if the block pool is empty.
   return tBlockPointer;
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Deallocate a block from the block pool.

void MyBlockS::operator delete(void* ptr)
{
   Prn::print(0, "MyBlockS::delete");
   // Deallocate the block back to the block pool
   CC::deallocateBlockPoolBlock(ptr);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Default Constructor.

MyBlockS::MyBlockS()
{
   Prn::print(0, "MyBlockS::constructor");

   mIdentifier = 0;
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;

   mBlockHandle.set(this);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

MyBlockS::MyBlockS(int aIdentifier)
{
   Prn::print(0, "MyBlockS::constructor %d",aIdentifier);

   mIdentifier = aIdentifier;
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;

   mBlockHandle.set(this);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

MyBlockS::~MyBlockS()
{
   Prn::print(0, "MyBlockS::destuctor   %d",mIdentifier);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void MyBlockS::method1()
{
   Prn::print(0, "MyBlockS::method1     %d",mIdentifier);
}

}//namespace
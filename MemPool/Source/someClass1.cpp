/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "someClass1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Class1A::Class1A()
{
   Prn::print(0, "Class1A::Class1A");
   mCode1A=101;
}

Class1A::~Class1A()
{
   Prn::print(0, "Class1A::~Class1A");
}

void Class1A::method1A()
{
   Prn::print(0, "Class1A::method1A %d",mCode1A);
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// This allocates a block from the block pool and uses placement new
// to call the class constructor. It is analogous to new.

Class1A* Class1A::allocate()
{
   // Block pointer.
   Class1A* tBlockPointer = 0;
   // Block handle.
   CC::MemHandle tMemHandle;

   // Allocate a block from the block pool.
   CC::allocateMemPoolBlock(CC::cMemPoolIndex_Class1A,(void**)&tBlockPointer,&tMemHandle);

   // Call the constructor on the allocated block using placement new.
   new(tBlockPointer)Class1A();

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
void Class1A::deallocate()
{
   // Deallocate the block back to the block pool
   deallocateMemPoolBlock(this->mMemHandle);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

Class1B::Class1B()
{
   Prn::print(0, "Class1B::Class1B");
   mCode1B=102;
}

Class1B::~Class1B()
{
   Prn::print(0, "Class1B::~Class1B");
}

void Class1B::method1B()
{
   Prn::print(0, "Class1B::method1B %d",mCode1B);
}
}//namespace
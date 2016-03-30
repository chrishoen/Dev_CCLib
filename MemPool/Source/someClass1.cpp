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
   Class1A* tPointer = 0;

   // Allocate a block from the block pool.
   tPointer = (Class1A*)CC::getMemPoolBlock(CC::cMemPoolIndex_Class1A);

   // Call the constructor on the allocated block using placement new.
   new(tPointer)Class1A();

   // Return the pointer to the allocated block.
   return tPointer;
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// This deallocates the object back to the block pool. It does not call
// a destructor for the object.
void Class1A::deallocate()
{
   // Deallocate the block back to the block pool
   putMemPoolBlock(this);
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
#ifndef _SOMECLASS1_H_
#define _SOMECLASS1_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <new>
#include "ccMemHandle.h"
#include "ccMemPoolIndex.h"
#include "ccMemPool.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class  Class1A : public CC::HasMemHandle
{
public:

   Class1A();
  ~Class1A();

   void method1A();

   int mCode1A;
  
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // This allocates a block from the block pool and uses placement new
   // to call the class constructor. It is analogous to new.

   static Class1A* allocate()
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
   void deallocate()
   {
      // Deallocate the block back to the block pool
      putMemPoolBlock(this);
   }

};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class  Class1B : public Class1A
{
public:

   Class1B();
  ~Class1B();

   void method1B();

   int mCode1B;
  
};

//******************************************************************************
}//namespace

#endif


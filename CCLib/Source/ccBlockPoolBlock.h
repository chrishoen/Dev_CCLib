#ifndef _CCBLOCKPOOLBLOCK_H_
#define _CCBLOCKPOOLBLOCK_H_

#include <new>
#include <stdio.h>

#include "ccBlockhandle.h"
#include "ccBlockPoolList.h"

/*==============================================================================

This is a template that defines a base class that can be inherited by classes
that are members of a memory block pool, instances of the inheriting classes
use block pools for memory management.

The class template provides static member variables that instantiate and 
initialize the memory pool, and also methods that provide access to it. 
The static variables establish global variables that instantiate the
memory pools.

==============================================================================*/

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is a class template for classes whose instances use a block pool 
// for memory management.

template <class BlockClass,int BlockPoolIndex>
class BlockPoolBlock
{
public:

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // This allocates a block from the block pool and uses placement new
   // to call the class constructor. It is analogous to new.

   static BlockClass* allocate()
   {
      // Block pointer.
      BlockClass* tBlockPointer = 0;
      // Block handle.
      CC::BlockHandle tBlockHandle;

      // Allocate a block from the block pool.
      CC::allocateBlockPoolBlock(BlockPoolIndex,(void**)&tBlockPointer,&tBlockHandle);

      // Call the constructor on the allocated block using placement new.
      new(tBlockPointer)BlockClass();

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
#if 0
   void deallocate()
   {
      // Deallocate the block back to the block pool
//    deallocateBlockPoolBlock(this->mBlockHandle);
   }
#endif

   static void deallocate(BlockClass* aBlock)
   {
      // Deallocate the block back to the block pool
      deallocateBlockPoolBlock(aBlock->mBlockHandle);
   }

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
/*==============================================================================

Here's an example:

   In SomeClass.h>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

   class SomeClass : public CC::BlockPoolBlock<SomeClass>
   {
   public:

      SomeClass();
      {
         printf("SomeClass::SomeClass\n");
      }

      void sayHello()
      { 
         printf("hello\n"); 
      }

   };

   In SomeClass.cpp>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

   CC::BlockPool Some::Class6A::mBlockPool;

   In SomeClassCaller.cpp>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

   SomeClass::initializeShortTermBlockPool(1000);
   SomeClass* object = SomeClass::create();
   object->sayHello();
   object->destroy();

==============================================================================*/

#endif
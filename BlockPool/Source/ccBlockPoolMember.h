#ifndef _CCBLOCKPOOLMEMBER_H_
#define _CCBLOCKPOOLMEMBER_H_

#include <new>
#include <stdio.h>

#include "ccTreeNode.h"
#include "ccDefs.h"
#include "ccBlockPool.h"

/*==============================================================================

This is a template that defines a base class that can be inherited by classes
that are members of a memory block pool, instances of the inheriting classes
use block pools for memory management.

The class template provides static member variables that instantiate and 
initialize the memory pool, and also methods that provide access to it. 
The static variables establish global variables that instantiate the
memory pools.

Here's a simple example:

   In SomeClass.h>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

   class SomeClass : public CC::BlockPoolMember<SomeClass>
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

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is a class template for classes whose instances use a block pool 
// for memory management.

template <class MemberClass>
class BlockPoolMember
{
public:

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Static member which provides a global variable for the memory block 
   // pool.
   static CC::BlockPool mBlockPool;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------

   // This initializes the memory block pool to be short term lifetime,
   // non persistent, circular buffer based. It is passed the number of
   // blocks to allocate from system heap memory.
   static void initializeShortTermBlockPool(int aAllocate)
   {
      mBlockPool.initializeShortTerm(aAllocate, sizeof(MemberClass));
   }

   // This initializes the memory block pool to be long term lifetime,
   // persistent, stack based. It is passed the number of blocks to
   // allocate from system heap memory.
   static void initializeLongTermBlockPool(int aAllocate)
   {
      mBlockPool.initializeLongTerm(aAllocate, sizeof(MemberClass));
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // This allocates a block from the block pool and uses placement new
   // to call the class constructor. It is analogous to new.
   static MemberClass* create()
   {
      // Block pointer.
      MemberClass* tPointer = 0;

      // Allocate a block from the block pool.
      tPointer = (MemberClass*)mBlockPool.get();

      // Call the constructor on the allocated block using placement new.
      new(tPointer)MemberClass();

      // Return the pointer to the allocated block.
      return tPointer;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // This deallocates the object back to the block pool. It does not call
   // a destructor for the object.
   void destroy()
   {
      // Deallocate the block back to the block pool
      mBlockPool.put(this);
   }

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
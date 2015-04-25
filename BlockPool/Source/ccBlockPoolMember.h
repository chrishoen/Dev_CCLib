#ifndef _CCBLOCKPOOLMEMBER_H_
#define _CCBLOCKPOOLMEMBER_H_

#include <new>
#include <stdio.h>

#include "ccTreeNode.h"
#include "ccDefs.h"
#include "ccBlockPool.h"

/*==============================================================================
This is class template for classes whose instances will be members of a 
memory block pool.


This defines class template that other classes inherit from. Instances of 
inheriting classes are established to be members of a block memory pool that is 
of a fixed number of blocks of fixed size.

Instances of classes that inherit from this base class template are members
of a memory block pool. The class template provides static member variables
that establish the block pool and it provides access methods to it.
==============================================================================*/

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is a class template for classes whose instances are members of a 
// memory block pool. 

template <class MemberClass>
class BlockPoolMember
{
public:

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Memory management, constructors and destructors

   // Static member block universe. It contains a short term and a long term
   // block pool. These block pools, or system memory, are used to establish
   // memory for all instances of this class that are created within a process.
   // The block universe must be initialized at the beginning of a process, 
   // prior to any block creation.

   static CC::BlockPool mBlockPool;

   // This static method initializes the block universe. In a process, it must
   // be called prior to any block creations. It initializes the block universe
   // short term and long term block pools.

   static void initializeShortTermBlockPool(
      int aAllocate)
   {
      mBlockPool.initializeShortTerm(aAllocate, sizeof(MemberClass));
   }

   static void initializelongTermBlockPool(
      int aAllocate)
   {
      mBlockPool.initializeLongTerm(aAllocate, sizeof(MemberClass));
   }

   // This static method allocates a block from system memory or from block
   // universe short term or long term memory block pools. After allocation,
   // it calls the class constructor on the allocated block. The memory type
   // parameter specifies either system memory, or short term block pool,
   // or long term block pool. It is analogous to new.

   // Create with default memory type and default member variables
   static MemberClass* create()
   {
      // Block pointer
      MemberClass* tPointer = 0;

      // Allocate a block from the short term block pool
      tPointer = (MemberClass*)mBlockPool.get();

      // Call the constructor on the allocated block using placement new
      new(tPointer)MemberClass();

      // Return the allocated block
      return tPointer;
   }

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete.

   static void destroy()
   {

   }

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif
#ifndef _CCBLOCKPOOLBLOCKNONINTRUSIVE_H_
#define _CCBLOCKPOOLBLOCKNONINTRUSIVE_H_

#include <new>
#include <stdio.h>

#include "ccBlockPoolCentral.h"

/*==============================================================================

This is a template that defines a base class that can be inherited by classes
that are members of a memory block pool, instances of the inheriting classes
use block pools for memory management.

The class template provides static member variables that instantiate and 
initialize the memory pool, and also methods that provide access to it. 
The static variables establish global variables that instantiate the
memory pools.

This is used for nonintrusive blocks, those that do not contain a block handle
member variable.
==============================================================================*/

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class template for classes whose instances use a block pool 
// for memory management. This is used for nonintrusive blocks, those that do
// not contain a block handle member variable.

template <class BlockClass,int BlockPoolIndex>
class BlockPoolBlockNonIntrusive
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Create a block. Allocate the block from the block pool and call the
   // class constructor on the block. This is used for nonintrusive blocks,
   // those that do not contain a block handle member variable.

   static BlockClass* create()
   {
      // Block pointer.
      BlockClass* tBlockPointer = 0;

      // Try to allocate a block from the block pool.
      if (CC::allocateBlockPoolBlock(BlockPoolIndex, (void**)&tBlockPointer, 0))
      {
         // Call the constructor on the allocated block using placement new.
         new(tBlockPointer)BlockClass();
      }
      // Return the pointer to the allocated block.
      // Return null if the block pool is empty.
      return tBlockPointer;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This deallocates the object back to the block pool. It does not call
   // a destructor for the object.

   void destroy()
   {
      // Deallocate the block back to the block pool
      deallocateBlockPoolBlock(this);
   }

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is a function template used to create classes that use the block pool
// for memory management. This is used for nonintrusive blocks, those that do
// not contain a block handle member variable.

template <class BlockClass,int BlockPoolIndex>
BlockClass* createBlockNonIntrusive()
{
   // Block pointer.
   BlockClass* tBlockPointer = 0;

   // Try to allocate a block from the block pool.
   if (CC::allocateBlockPoolBlock(BlockPoolIndex, (void**)&tBlockPointer, 0))
   {
      // Call the constructor on the allocated block using placement new.
      new(tBlockPointer)BlockClass();
   }
   // Return the pointer to the allocated block.
   // Return null if the block pool is empty.
   return tBlockPointer;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class BlockClass,int BlockPoolIndex,typename Parm1>
BlockClass* createBlockNonIntrusive(Parm1 P1)
{
   // Block pointer.
   BlockClass* tBlockPointer = 0;

   // Try to allocate a block from the block pool.
   if (CC::allocateBlockPoolBlock(BlockPoolIndex, (void**)&tBlockPointer, 0))
   {
      // Call the constructor on the allocated block using placement new.
      new(tBlockPointer)BlockClass(P1);
   }
   // Return the pointer to the allocated block.
   // Return null if the block pool is empty.
   return tBlockPointer;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class BlockClass,int BlockPoolIndex,typename Parm1,typename Parm2>
BlockClass* createBlockNonIntrusive(Parm1 P1,Parm1 P2)
{
   // Block pointer.
   BlockClass* tBlockPointer = 0;

   // Try to allocate a block from the block pool.
   if (CC::allocateBlockPoolBlock(BlockPoolIndex, (void**)&tBlockPointer))
   {
      // Call the constructor on the allocated block using placement new.
      new(tBlockPointer)BlockClass(P1,P2);
   }
   // Return the pointer to the allocated block.
   // Return null if the block pool is empty.
   return tBlockPointer;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class BlockClass,int BlockPoolIndex,typename Parm1,typename Parm2,typename Parm3>
BlockClass* createBlockNonIntrusive(Parm1 P1,Parm1 P2,Parm1 P3)
{
   // Block pointer.
   BlockClass* tBlockPointer = 0;

   // Try to allocate a block from the block pool.
   if (CC::allocateBlockPoolBlock(BlockPoolIndex, (void**)&tBlockPointer, 0))
   {
      // Call the constructor on the allocated block using placement new.
      new(tBlockPointer)BlockClass(P1,P2,P3);
   }
   // Return the pointer to the allocated block.
   // Return null if the block pool is empty.
   return tBlockPointer;
}

//****************************************************************************


//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace

#endif
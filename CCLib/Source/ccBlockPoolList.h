#ifndef _CCBLOCKPOOLLIST_H_
#define _CCBLOCKPOOLLIST_H_

/*==============================================================================

A block pool is a memory management mechanism that provides a preallocated
memory region for a fixed number of blocks of a fixed size. It provides
methods to allocate and deallocate blocks from it.

Block pools are used in programs that have a bounded number of specific
objects allocated at any given time. The memory for the objects is allocated
at program initialization and allocation/deallocation of the objects
throughout the program lifetime is much faster than system heap
malloc/free operations (new/delete). To use this, the maximum number of 
blocks that can be allocated at any given time must be known apriori.

A class that uses a block pool for memory management in place of system heap
new/delete must create a specific block pool for that class at program
initialization. Creation and destruction of instances of the class must
then be done via block pool allocate/deallocate calls, new/delete cannot
be used.

There can be different types of block pools. They differ in terms of block
lifetimes (short term and long term), thread safety and concurrent access,
and where block memory is located (system heap or shared memory).

Short term blocks are non persistent and have short term lifetimes. Long
term blocks are persistent and have long lifetimes. Short term blocks are
not deallocated, they are simply reused. Long term blocks are deallocated.

The block pools for a program are contained in a global store that contains
an array of block pool pointers. When a block pool is created, a pointer to
it is stored in the array. Accesses to the block pool (allocate or deallocate
a block, perform a handle to pointer conversion) are done via the global
block pool array.

Blocks in a block pool are accessed via a block handle. A block handle
contains a pool index and a block index. The pool index indicates which pool
a block belongs to and a block index indicates which block within the pool 
it is. Methods are provided to convert between block pointers and block
handles.

The pool index value of zero is reserved to indicate a null pool and the
block index value of zero is reserved to indicate a null block. Block
box array entry zero is a dummy block and is never used.

Classes that use block pools must contain a block handle as a member
variable. This means that the block pools are what is known as an intrusive
memory management scheme.

Block pools use block box arrays for the block memory. They allocates storage
for the blocks on the system heap or in shared memory and provides pointer 
access to the allocated blocks.

A block box contains a block header and a block body. The header is invisible
to the user and is used for things like resource counting and pointer to
handle conversions. The block body is visible to the user as a pointer to the
block.

Specific block pool classes inherit from a block pool base class.

==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockHandle.h"

namespace CC
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   void resetBlockPoolList();

   void addToBlockPoolList(int aNumBlocks,int aBlockSize,int aPoolIndex);

   void initializeBlockPoolList();
   void finalizeBlockPoollist();

   
   void allocateBlockPoolBlock(int aPoolIndex,void** aBlockPointer,BlockHandle* aBlockHandle);
   void deallocateBlockPoolBlock(BlockHandle aBlockHandle);

   void showBlockPool(int aPoolIndex);

   void* getBlockPoolBlockPtr(BlockHandle aBlockHandle);

}//namespace
#endif


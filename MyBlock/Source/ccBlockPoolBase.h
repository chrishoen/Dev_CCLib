#ifndef _CCBLOCKPOOLBASE_H_
#define _CCBLOCKPOOLBASE_H_
/*==============================================================================

This defines a memory pool of a fixed number of blocks that are of a fixed
size.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockBoxArray.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a pool of memory blocks. At initialization, a fixed
// number of blocks of fixed size are allocated on the system heap. Methods
// are provided to allocate and deallocate blocks from the pool. These methods
// are thread safe because they use critical sections.
//
// This is used in programs that will have a bounded number of specific
// objects allocated at any given time. The memory for the objects is allocated
// at program initialization and allocation/deallocation of the objects
// throughout the programs lifetime is much faster than system heap
// malloc/free operations (new/delete). To use this, the maximum number of 
// blocks that can be allocated at any given time must be known apriori.
// 
// There are two types of memory block pool: short term and long term. Short
// term blocks are non persistent and have short term lifetimes. Long term
// blocks are persistent and have long lifetimes. The type of the block pool
// is set at initialization and there can only be one type for a specific
// instance.
//
// Blocks that are allocated from long term pools must be deallocated once
// their lifetimes have expired. Blocks that are allocated from short term 
// pools are not deallocated, they are simply reused. 

class BlockPoolBase
{
public:
   //---------------------------------------------------------------------------
   // Methods

   //---------------------------------------------------------------------------
   // Constructor
   BlockPoolBase();

   // Allocate memory for the block array. It is passed the number of blocks to
   // allocate, the size of the block body, and the memory pool index for the
   // block array.
   virtual void initialize(int aNumBlocks,int aBlockSize,int aPoolIndex);

   // Deallocate memory for the block array.
   virtual void finalize();

   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block. If the block pool is 
   // short term, it gets a pointer from the circular array of pointers and 
   // advances the index into the array. If the block pool is long term, it 
   // pops a pointer from the pointer stack.
   virtual void allocate(void** aBlockPointer,BlockHandle* aBlockHandle)=0;

   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block. If the block pool
   // is short term, it does nothing. If the block pool is long term, it pushes
   // the pointer back onto the pointer stack.
   virtual void deallocate(BlockHandle aBlockHandle)=0;

   //---------------------------------------------------------------------------
   // Return a pointer to a block, given its memoryhandle.
   virtual void* getBlockPtr(BlockHandle aBlockHandle)=0;

   //---------------------------------------------------------------------------
   // Members

   // This allocates storage for the blocks on the system heap and provides
   // pointer access to the allocated blocks.
   BlockBoxArray mBlocks;

   // Number of blocks allocated
   int mNumBlocks;

   // Size of each block body
   int mBlockSize;

   // Memory pool index for the block array
   int mPoolIndex;

   // Block count, remaining blocks available.
   int mCount;

   //---------------------------------------------------------------------------
   // Helpers

   void show();
   virtual int size()=0;
};

//******************************************************************************

}//namespace
#endif


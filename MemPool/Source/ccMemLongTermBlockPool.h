#ifndef _CCMEMLONGTERMBLOCKPOOL_H_
#define _CCMEMLONGTERMBLOCKPOOL_H_
/*==============================================================================

This defines a memory pool of a fixed number of blocks that are of a fixed
size.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccMemBaseBlockPool.h"
#include "ccValueStack.h"

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

class LongTermBlockPool : public MemBaseBlockPool
{
public:
   typedef MemBaseBlockPool BaseClass;

   //---------------------------------------------------------------------------
   // Methods

   //---------------------------------------------------------------------------
   // Constructor
   LongTermBlockPool();
  ~LongTermBlockPool();

   // Allocate memory for the block array. It is passed the number of blocks to
   // allocate, the size of the block body, and the memory pool index for the
   // block aarray.
   void initialize(int aNumBlocks,int aBlockBodySize);

   // Deallocate memory for the block array.
   void finalize();

   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block. If the block pool is 
   // short term, it gets a pointer from the circular array of pointers and 
   // advances the index into the array. If the block pool is long term, it 
   // pops a pointer from the pointer stack.
   void* get();

   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block. If the block pool
   // is short term, it does nothing. If the block pool is long term, it pushes
   // the pointer back onto the pointer stack.
   void put(void* aBlockPointer);


   // This is a stack of pointers. This is used if the block pool has long
   // term blocks. It is a stack of pointers into the above allocated memory
   // block array. To allocate a block, a pointer is popped off of the stack.
   // To free a block, a pointer is pushed back onto the stack. To deallocate
   // a block, a pointer is pushed back onto the stack. Pushes and Pops are
   // locked with critical sections, making tehm thread safe.

   ValueStack<int> mBlockIndexStack;

};

//******************************************************************************

}//namespace
#endif


#ifndef _CCBLOCKPOOLLONGTERM_H_
#define _CCBLOCKPOOLLONGTERM_H_
/*==============================================================================
Long term block pool class
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockPoolBase.h"
#include "ccValueStack.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a long term block pool.
// 
// There are two types of block pool: short term and long term. Short
// term blocks are non persistent and have short term lifetimes. Long term
// blocks are persistent and have long lifetimes. The type of the block pool
// is set at initialization and there can only be one type for a specific
// instance.
//
// Blocks that are allocated from long term pools must be deallocated once
// their lifetimes have expired. Blocks that are allocated from short term 
// pools are not deallocated, they are simply reused. 
//
// The long term block pool is a free list of blocks. It contains a block
// array and a stack of indices into the array. When a block is allocated,
// an index is popped off of the stack. When a block is deallocated, its
// index is pushed onto the stack.
   
// At initialization, all of the indices are pushed onto the stack. The 
// pool starts out with a full stack.
//
// It allocates memory for the block array and initializes the index stack.
// It is passed the number of blocks to allocate and the size of the blocks. 
// Memory for one dummy block is allocated because index zero is reserved to
// indicate a null block.
//
// For aNumBlocks==10 blocks will range 0,1,2,3,4,5,6,7,8,9,10
// An index of zero is reserved for null index, so block 0 is unused.
// So usable blocks will range 1,2,3,4,5,6,7,8,9,10
//
// An index stack is used to manage free list access to the blocks
// The stack is initialized for a free list by pushing indices onto it.
// For aAllocate==10 this will push 10,9,8,7,6,5,4,3,2,1
//

class BlockPoolLongTerm : public BlockPoolBase
{
public:
   typedef BlockPoolBase BaseClass;

   //---------------------------------------------------------------------------
   // Methods

   //---------------------------------------------------------------------------
   // Constructor
   BlockPoolLongTerm();
  ~BlockPoolLongTerm();

   // Allocate memory for the block array. It is passed the number of blocks to
   // allocate, the size of the block body, and the memory pool index for the
   // block array.
   void initialize(int aNumBlocks,int aBlockSize,int aPoolIndex);

   // Deallocate memory for the block array.
   void finalize();

   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block. If the block pool is 
   // short term, it gets a pointer from the circular array of pointers and 
   // advances the index into the array. If the block pool is long term, it 
   // pops a pointer from the pointer stack.
   void allocate(void** aBlockPointer,BlockHandle* aBlockHandle);

   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block. If the block pool
   // is short term, it does nothing. If the block pool is long term, it pushes
   // the pointer back onto the pointer stack.
   void deallocate(BlockHandle aBlockHandle);

   //---------------------------------------------------------------------------
   // Return a pointer to a block, given its memory handle.
   void* getBlockPtr(BlockHandle aBlockHandle);

   //---------------------------------------------------------------------------
   // This is a free list stack of indices into the block array.
   // When a block is allocated, an index is popped off of the stack.
   // When a block is deallocated, its index is pushed back onto the stack.

   ValueStack<int> mBlockIndexStack;

   //---------------------------------------------------------------------------
   // Size, the number of blocks that are available to be allocated.
   int size(){ return mBlockIndexStack.mCount; }
};

//******************************************************************************

}//namespace
#endif


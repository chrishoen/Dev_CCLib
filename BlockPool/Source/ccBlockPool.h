#ifndef _BLOCKPOOL_H_
#define _BLOCKPOOL_H_
/*==============================================================================

This defines a pool of memory blocks that have a lifetime that is long term.
The blocks are persistent. Blocks are allocated and deallocated from the pool.
This is similar to a system heap. Calls to this class are thread safe, it 
uses critical sections.

The blocks are termed to be persistent in the sense that they can have a
lifetime that is long term. This is in contrast to blocks that are have short
term lifetimes. Blocks that are allocated from long term pools must be 
deallocated once their lifetimes have expired. Blocks that are allocated from 
short term pools are not dellocated, they are simply reused. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockArray.h"
#include "ccPointerStack.h"
#include "ccPointerCircular.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a pool of persistent memory blocks. At 
// initialization, it allocates an array of blocks and it allocates a stack
// of pointers into the blocks. To allocate a block from the pool, a pointer is 
// popped from the stack. To free a block, a pointer is pushed back onto the
// stack. This is thread safe because it the stack accesses use critical
// sections.

class BlockPool
{
public:
   //---------------------------------------------------------------------------
   // Methods

   //---------------------------------------------------------------------------
   // Constructor
   BlockPool();
  ~BlockPool();

   //---------------------------------------------------------------------------
   // This initializes the block pool for short term blocks.
   // Allocate memory for the block array and initialize the pointer array.
   // It is passed the number of blocks to allocate and the size of the blocks.
   void initializeShortTerm(int aAllocate,int aBlockSize);

   // This initializes the block pool for long term blocks.
   // Allocate memory for the block array and initialize the pointer array.
   // It is passed the number of blocks to allocate and the size of the blocks.
   void initializeLongTerm(int aAllocate,int aBlockSize);

   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block.
   // If the block pool is short term, it gets a pointer from the circular
   // array of pointers and advances the index into the array.
   // If the block pool is long term, it pops a pointer from the pointer
   // stack.
   void* get();

   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block.
   // If the block pool is short term, it does nothing.
   // If the block pool is long term, it pushes the pointer back onto the
   // pointer stack.
   void put(void* aBlockPointer);

   //---------------------------------------------------------------------------
   // Members

   // This allocates storage for the blocks on the system heap. It provides
   // pointer access to the allocated blocks.
   BlockArray mBlocks;

   // The two types of block pool, short term and long term lifetimes. Short
   // term blocks are non persistent and long term blocks are persistent.
   enum
   {
      BlockPoolType_ShortTerm = 1, 
      BlockPoolType_LongTerm  = 2, 
   };

   // This variable determines which of the two following pointer arrays are
   // used, short term or long term.
   int mBlockPoolType;

   // This is a circular buffer of pointers. This is used if the block pool
   // has short term blocks. It is an array of pointers into the above
   // allocated memory block array. To allocate a block, a pointer is gotten
   // from the array and its index is incremented. Allocations are locked with
   // critical sections.
   PointerCircular mShortTermPointerCircular;

   // This is a stack of pointers. This is used if the block pool has long
   // term blocks. It is a stack of pointers into the above allocated memory
   // block array. To allocate a block, a pointer is popped off of the stack.
   // To free a block, a pointer is pushed back onto the stack. Pushes and
   // Pops are locked with critical sections.
   PointerStack mLongTermPointerStack;
};

//******************************************************************************

}//namespace
#endif


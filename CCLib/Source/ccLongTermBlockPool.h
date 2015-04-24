#ifndef _LongTermBlockPOOL_H_
#define _LongTermBlockPOOL_H_
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

class LongTermBlockPool
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   LongTermBlockPool();
  ~LongTermBlockPool();

   // Allocate memory for the block array and initialize the pointer stack.
   // It is passed the number of blocks to allocate and the size of the blocks.
   void initialize(int aAllocate,int aBlockSize);

   // Get a block from the pool, this allocates a block. It pops a pointer
   // from the pointer stack.
   void* get();

   // Put a block back to the pool, this deallocates a block. It pushes a 
   // pointer onto the pointer stack.
   void put(void* aBlockPointer);

   //---------------------------------------------------------------------------
   // Members

   // Array of allocated memory blocks. The blocks are allocated on the 
   // system heap and this maintains a pointer to the blocks.
   BlockArray mBlocks;

   // Stack of pointers into the block array. To allocate a block, a pointer 
   // is popped off of the stack. To free a block, a pointer is pushed back
   // onto the stack. Pushes and Pops are locked with critical sections.
   PointerStack mPointerStack;
};

//******************************************************************************

}//namespace
#endif


#ifndef _CCSHORTTERMBLOCKPOOL_H_
#define _CCSHORTTERMBLOCKPOOL_H_
/*==============================================================================

This defines an array of memory blocks that are dynamically allocated.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockArray.h"
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
// stack.

class ShortTermBlockPool
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   ShortTermBlockPool();
  ~ShortTermBlockPool();

   // Allocate memory for the block array and initialize the pointer stack.
   void initialize(int aAllocate,int aBlockSize);

   // Get a block from the pool, allocate
   void* get();

   //---------------------------------------------------------------------------
   // Members

   // Array of allocated memory blocks
   BlockArray mBlocks;

   // Stack of pointers into the block array. To allocate a block, a pointer 
   // is popped off of the stack. To free a block, a pointer is pushed back
   // onto the stack.
   PointerCircular mPointerCircular;
};

//******************************************************************************

}//namespace
#endif


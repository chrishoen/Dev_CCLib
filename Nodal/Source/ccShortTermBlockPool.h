#ifndef _CCSHORTTERMBLOCKPOOL_H_
#define _CCSHORTTERMBLOCKPOOL_H_
/*==============================================================================

This defines a pool of memory blocks that have a lifetime that is short term.
The blocks are not persistent. Blocks are allocated from the pool but they are
not deallocated, they are simply reused. The pool operates in a circular
manner.

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
// This class encapsulates a pool of non persistent memory blocks. At 
// initialization, it allocates an array of blocks and it allocates a circular
// array of pointers into the blocks. To allocate a block from the pool, a 
// pointer is gotten from the circular array. Blocks are not deallocated, they
// are simply reused.

class ShortTermBlockPool
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   ShortTermBlockPool();
  ~ShortTermBlockPool();

   // Allocate memory for the block array and initialize the pointer array.
   void initialize(int aAllocate,int aBlockSize);

   // Get a block from the pool, allocate
   void* get();

   //---------------------------------------------------------------------------
   // Members

   // Array of allocated memory blocks
   BlockArray mBlocks;

   // Array of pointers into the block array. To allocate a block, a pointer 
   // is gotten from the array and its index is incremented.
   PointerCircular mPointerCircular;
};

//******************************************************************************

}//namespace
#endif


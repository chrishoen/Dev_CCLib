#ifndef _CCSHORTTERMBLOCKPOOL_H_
#define _CCSHORTTERMBLOCKPOOL_H_
/*==============================================================================

This establishes a circular buffer of memory blocks fixed size memory blocks.
It is thread safe because access is locked via critical sections.

It defines a pool of memory blocks that have a lifetime that is short term.
The blocks are not persistent. Blocks are allocated from the pool but they are
not deallocated, they are simply reused. The pool operates in a circular
manner.

The blocks are termed to be non persistent in the sense that they will have a
lifetime that is short term. This is in contrast to blocks that are have long
term lifetimes. Blocks that are allocated from long term pools must be 
deallocated once their lifetimes have expired. Blocks that are allocated from 
short term pools are not dellocated, they are simply reused. 

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

   // Get a block from the pool, this allocates a block. It gets a pointer
   // from the circular array of pointers and advances the index into the 
   // array.
   void* get();

   //---------------------------------------------------------------------------
   // Members

   // Array of allocated memory blocks of fixed size. The blocks are allocated
   // on the system heap. They are accessed via the circular pointer array.
   BlockArray mBlocks;

   // Array of pointers into the above allocated memory block array. To allocate
   // a block, a pointer is gotten from the array and its index is incremented.
   PointerCircular mPointerCircular;
};

//******************************************************************************

}//namespace
#endif


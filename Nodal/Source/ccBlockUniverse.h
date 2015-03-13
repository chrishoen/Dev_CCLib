#ifndef _CCBLOCKUNIVERSE_H_
#define _CCBLOCKUNIVERSE_H_
/*==============================================================================

This defines an array of memory blocks that are dynamically allocated.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccShortTermBlockPool.h"
#include "ccLongTermBlockPool.h"

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

class BlockUniverse
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   BlockUniverse();
  ~BlockUniverse();

   // Allocate memory for the block array and initialize the pointer stack.
   void initialize(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks,
      int aBlockSize);

   //---------------------------------------------------------------------------
   // Members

   // Array of short term allocated memory blocks
   ShortTermBlockPool mShortTermBlockPool;

   // Array of long term allocated memory blocks
   LongTermBlockPool mLongTermBlockPool;
};

//******************************************************************************

}//namespace
#endif


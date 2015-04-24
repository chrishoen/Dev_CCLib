#ifndef _CCBLOCKUNIVERSE_H_
#define _CCBLOCKUNIVERSE_H_

/*==============================================================================

This establishes a memory block universe. It provides memory management for 
instances of classes that are based on fixed size memory blocks. It maintains
two block pools, one for block lifetimes that are short term and one for
lifetimes that are long term. Short term blocks are non persistent and long
term blocks are persistent.

When instances of memory block classes are created, they allocate from one of 
the block pools contained in the universe. If a block is long term, then when
it is destroyed, it is deallocated back to its pool.

This is similar to using a system heap with new and delete, but it is
optimized for speed, at the expense of added code complexity and memory
allocation. The speed increase is because the only operating system calls
made are for critical sections.

Memory block classes have static members that are instances
of this class.

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
// Block universe, contains a short term and a long term memory block pool.
// Instances of this class provide memory storage for classes that are based
// on memory blocks.

class BlockUniverse
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   BlockUniverse();
  ~BlockUniverse();

   // Initialize the short term and the long term block pools. It is passed
   // The numbers of blocks to allocate and the size of the blocks.
   void initialize(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks,
      int aBlockSize);

   //---------------------------------------------------------------------------
   // Members

   // Short term memory block pool
   ShortTermBlockPool mShortTermBlockPool;

   // Long term memory block pool
   LongTermBlockPool mLongTermBlockPool;

   // Show
   void show(char* aLabel);
};

//******************************************************************************

}//namespace
#endif


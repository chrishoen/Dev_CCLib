#ifndef _CCBLOCKUNIVERSE_H_
#define _CCBLOCKUNIVERSE_H_
/*==============================================================================

This establishes a memory block universe. It provides memory management for 
instances of classes that are based on memory blocks. It maintains two block 
pools, one for block lifetimes that are short term and one for long term.
When instances of memory block classes are created, they allocate from the
block pools. Memory block classes have static members that are instances
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
// Block universe, contains a short term and a long term memory block pools.
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

   // Initialize the short term and the long term block pools
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


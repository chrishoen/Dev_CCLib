#ifndef _CCBLOCKPOOLFREELIST_H_
#define _CCBLOCKPOOLFREELIST_H_
/*==============================================================================
Free list block pool class
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockPoolBase.h"
#include "ccBlockPoolBaseIndexStack.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a block pool that is based on a free list paradigm.
// It is long term.
//
// It contains a free list of blocks, which is a block array and a stack of
// indices into the array. When a block is allocated, an index is popped off of
// the stack. When a block is deallocated, its index is pushed onto the stack.
//   
// At initialization, all of the indices are pushed onto the stack. The 
// pool starts out with a full stack.
//
// It allocates memory for the block array and initializes the index stack.
// It is passed the number of blocks to allocate and the size of the blocks. 
//
// For aNumBlocks==10 blocks will range 0,1,2,3,4,5,6,7,8,9
// So block indices will range 0,1,2,3,4,5,6,7,8,9
//
// An index stack is used to manage free list access to the blocks
// The stack is initialized for a free list by pushing indices onto it.
// For aAllocate==10 this will push 9,8,7,6,5,4,3,2,1,0 onto the stack
// so that block zero will be the first one popped.
//
// The index stack can be configured to be thread safe that uses a lock free
// atomic cas treiber stack. It can also configured to be a normal stack
// which is not thread safe, but is faster.

class BlockPoolFreeList : public BlockPoolBase
{
public:
   typedef BlockPoolBase BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize(BlockPoolParms* aParms);

   class MemorySize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Constructor
   BlockPoolFreeList();
  ~BlockPoolFreeList();

   // Initialize the block pool. It is passed block pool parameters.
   void initialize(BlockPoolParms* aParms);

   // Deallocate memory for the block array.
   void finalize();

   // Get a block from the pool, this allocates a block.
   // Return true if successful, false if the block pool is empty.
   bool allocate(void** aBlockPointer,BlockHandle* aBlockHandle);

   // Put a block back to the pool, this deallocates a block.
   void deallocate(BlockHandle aBlockHandle);

   // Get a pointer to a block, given its memory handle.
   void* getBlockPtr(BlockHandle aBlockHandle);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // If this flag is false then the memory for this object was created
   // externally. If it is true then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mFreeMemoryFlag;

   // Pointer to memory for which the stack resides. This is either created
   // externally and passed as an initialization parameter or it is created
   // on the system heap at initialization.
   void* mMemory;

   // This is a free list stack of indices into the block array.
   // When a block is allocated, an index is popped off of the stack.
   // When a block is deallocated, its index is pushed back onto the stack.
   // Based on the pool type this will be instantiated with a normal stack
   // or a lock free treiber stack.
   BlockPoolBaseIndexStack* mBlockIndexStack;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helpers

   // Size, the number of blocks that are available to be allocated.
   int size();
};

//******************************************************************************

}//namespace
#endif


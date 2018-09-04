#pragma once

/*==============================================================================
Free list block pool class, short term
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <atomic>
#include "ccBlockPoolBase.h"
#include "ccBlockBoxArray.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// State variables for the block pool. These are located in a separate 
// class so that they can be located in external memory.

class BlockPoolShortTermState
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Class.

   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.
   static int getMemorySize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Number of blocks allocated.
   int mNumBlocks;

   // Index counter. This is incremented for each block allocate.
   std::atomic<unsigned long long> mIndexCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   BlockPoolShortTermState();

   // Initialize.
   void initialize(BlockPoolParms* aParms);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a block pool that is based on a free list paradigm.
// It is short term term and it is thread safe.
//
// There are two types of memory block pool: short term and long term. Short
// term blocks are non persistent and have short lifetimes. Long term
// blocks are persistent and have long lifetimes.
// instance.
//
// Blocks that are allocated from long term pools must be deallocated once
// their lifetimes have expired. Blocks that are allocated from short term 
// pools are not deallocated, they are simply reused. 
// 
// This is short term. It does not deallocate blocks. 
//
// For block allocations, it uses a 64 bit atomic counter that increments
// with each allocate. A cyclic 0..mNumBlocks-1 block index derived from
// this is used to get a block from the block array.
// 
// The block index counter has never yet been observed to rollover, but if it
// does then erroneous results will occur. An allocation once every
// microsecond will rollover after 584942 years.

class BlockPoolShortTerm : public BlockPoolBase
{
public:
   typedef BlockPoolBase BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Class.

   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.
   static int getMemorySize(BlockPoolParms* aParms);

   class MemorySize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If this flag is false then the memory for this object was created
   // externally. If it is true then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mOwnMemoryFlag;

   // Pointer to memory for which the stack resides. This is either created
   // externally and passed as an initialization parameter or it is created
   // on the system heap at initialization.
   void* mMemory;

   // State variables for the stack. These are located in a separate class
   // so that they can be located in externale memory.
   BlockPoolShortTermState* mX;

   // A pointer to the parameters that were passed in at initialization.
   // Whoever owns this block pool (creates and initializes it) must maintain
   // storage for these parameters for the lifetime of the block pool.
   // The owner creates an instance of the parameters and fills in some of
   // them and passes them to the block pool at initialization. The block pool
   // then also fills in some of them during its initiialization and the 
   // owner might use some of them after the initialization. Memory storage
   // for these must be maintained my the owner throughout the lifetime of
   // the block pool.
   BlockPoolParms* mParms;

   // This allocates storage for the blocks on the system heap or in shared
   // memory and provides pointer access to the allocated blocks. This is a block
   // box array. A block box contains a block header and a block body. The
   // header is invisible to the user and is used for things like resource
   // counting and pointer to handle conversions. The block body is visible to 
   // the user as a pointer to the block.
   BlockBoxArray mBlocks;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor
   BlockPoolShortTerm();
  ~BlockPoolShortTerm();

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
   // Helper methods.

   // Size, the number of blocks that are available to be allocated.
   int size();

   // Show status and metrics for the block pool.
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


#ifndef _CCBLOCKPOOLSHORTTERM_H_
#define _CCBLOCKPOOLSHORTTERM_H_
/*==============================================================================
Free list block pool class
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <atomic>
#include "ccBlockPoolBase.h"

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

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize();

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   // Number of blocks allocated.
   int mNumBlocks;

   // Index counter. This is incremented for each block allocate.
   std::atomic<unsigned long long> mIndexCount;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
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
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize(BlockPoolParms* aParms);

   class MemorySize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   //---------------------------------------------------------------------------
   // Constructor
   BlockPoolShortTerm();
  ~BlockPoolShortTerm();

   //---------------------------------------------------------------------------
   // Initialize the block pool. It is passed block pool parameters.
   void initialize(BlockPoolParms* aParms);

   //---------------------------------------------------------------------------
   // Deallocate memory for the block array.
   void finalize();

   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block.
   // Return true if successful, false if the block pool is empty.
   bool allocate(void** aBlockPointer,BlockHandle* aBlockHandle);

   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block.
   void deallocate(BlockHandle aBlockHandle);

   //---------------------------------------------------------------------------
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

   // State variables for the stack. These are located in a separate class
   // so that they can be located in externale memory.
   BlockPoolShortTermState* mX;

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


#ifndef _CCBLOCKPOOLBASE_H_
#define _CCBLOCKPOOLBASE_H_
/*==============================================================================

This defines a base class for block pools. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockpoolParms.h"
#include "ccBlockBoxArray.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is a base class for a pool of memory blocks. It provides a common
// interface for block pools and it provides a block box array member.

class BlockPoolBase
{
public:
   //---------------------------------------------------------------------------
   // Constructor
   BlockPoolBase();

   //---------------------------------------------------------------------------
   // Methods

   // Allocate memory for the block array. It is passed the number of blocks to
   // allocate, the size of the block body, and the memory pool index for the
   // block array.
   virtual void initialize(BlockPoolParms* aParms);

   // Deallocate memory for the block array.
   virtual void finalize();

   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block.
   virtual void allocate(void** aBlockPointer,BlockHandle* aBlockHandle)=0;

   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block.
   virtual void deallocate(BlockHandle aBlockHandle)=0;

   //---------------------------------------------------------------------------
   // Return a pointer to a block, given its memory handle.
   virtual void* getBlockPtr(BlockHandle aBlockHandle)=0;

   //---------------------------------------------------------------------------
   // Members

   // This allocates storage for the blocks on the system heap or in shared
   // memory and provides pointer access to the allocated blocks. This is a block
   // box array. A block box contains a block header and a block body. The
   // header is invisible to the user and is used for things like resource
   // counting and pointer to handle conversions. The block body is visible to 
   // the user as a pointer to the block.
   BlockBoxArray mBlocks;

   // Number of blocks allocated
   int mNumBlocks;

   // Size of each block body
   int mBlockSize;

   // Pool index for the specific block pool contained in the global block
   // pool array.
   int mPoolIndex;

   // Block count, remaining blocks available.
   int mCount;

   //---------------------------------------------------------------------------
   // Helpers

   void show();
   virtual int size()=0;
};

//******************************************************************************

}//namespace
#endif

// There are two types of memory block pool: short term and long term. Short
// term blocks are non persistent and have short lifetimes. Long term
// blocks are persistent and have long lifetimes.
// instance.
//
// Blocks that are allocated from long term pools must be deallocated once
// their lifetimes have expired. Blocks that are allocated from short term 
// pools are not deallocated, they are simply reused. 

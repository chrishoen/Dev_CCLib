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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Abstract Methods

   // Constructor
   BlockPoolBase();

   // Initialize the block pool. It is passed block pool parameters.
   virtual void initialize(BlockPoolParms* aParms)=0;

   // Deallocate memory for the block array.
   virtual void finalize()=0;

   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block.
   virtual void allocate(void** aBlockPointer,BlockHandle* aBlockHandle)=0;

   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block.
   virtual void deallocate(BlockHandle aBlockHandle)=0;

   //---------------------------------------------------------------------------
   // Return a pointer to a block, given its memory handle.
   virtual void* getBlockPtr(BlockHandle aBlockHandle)=0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods called by inheriting classes

   // Initialize the block pool. It is passed block pool parameters.
   void initializeBase(BlockPoolParms* aParms,void* aMemory);

   // Deallocate memory for the block array.
   void finalizeBase();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // If this flag is true then the memory for this object was created
   // externally. If it is false then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mBaseClassExternalMemoryFlag;

   // Pointer to memory for which the stack resides. This is either created
   // externally and passed as an initialization parameter or it is created
   // on the system heap at initialization.
   void* mBaseClassMemory;

   // This allocates storage for the blocks on the system heap or in shared
   // memory and provides pointer access to the allocated blocks. This is a block
   // box array. A block box contains a block header and a block body. The
   // header is invisible to the user and is used for things like resource
   // counting and pointer to handle conversions. The block body is visible to 
   // the user as a pointer to the block.
   BlockBoxArray mBlocks;

   // Copy of parameters that were passed in at initialization.
   BlockPoolParms* mParms;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helpers

   void show();
   virtual int size()=0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize(BlockPoolParms* aParms);
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

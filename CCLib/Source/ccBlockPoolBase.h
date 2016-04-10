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
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize(BlockPoolParms* aParms);

   class MemorySize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Abstract Methods

   // Constructor
   BlockPoolBase();

   // Initialize the block pool. It is passed block pool parameters.
   virtual void initialize(BlockPoolParms* aParms)=0;

   // Deallocate memory for the block pool.
   virtual void finalize()=0;

   // Get a block from the pool, this allocates a block.
   // Return true if successful, false if the block pool is empty.
   virtual bool allocate(void** aBlockPointer,BlockHandle* aBlockHandle)=0;

   // Put a block back to the pool, this deallocates a block.
   virtual void deallocate(BlockHandle aBlockHandle)=0;

   // Get a pointer to a block, given its memory handle.
   virtual void* getBlockPtr(BlockHandle aBlockHandle)=0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods called by inheriting classes

   // Initialize the block pool base class. It is passed block pool parameters.
   void initializeBase(BlockPoolParms* aParms,void* aMemory);

   // Deallocate memory for the block pool base class.
   void finalizeBase();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // If this flag is false then the memory for this object was created
   // externally. If it is true then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mBaseClassFreeMemoryFlag;

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helpers

   void show();
   virtual int size()=0;
};

//******************************************************************************

}//namespace
#endif


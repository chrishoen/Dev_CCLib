/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cc_functions.h"
#include "ccMemoryPtr.h"
#include "ccBlockPoolShortTerm.h"

using namespace std;

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

int BlockPoolShortTermState::getMemorySize()
{
   return cc_round_upto16(sizeof(BlockPoolShortTermState));
}

BlockPoolShortTermState::BlockPoolShortTermState()
{
   // All null
   mNumBlocks=0;
   mIndexCount=0;
}

void BlockPoolShortTermState::initialize(BlockPoolParms* aParms)
{
   // Do not initialize, if already initialized.
   if (!aParms->mConstructorFlag) return;

   // Store members.
   mNumBlocks    = aParms->mNumBlocks;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This local class calculates and stores the memory sizes needed by the class.

class BlockPoolShortTerm::MemorySize
{
public:
   // Members.
   int mStateSize;
   int mBlockBoxArraySize;
   int mMemorySize;

   // Calculate and store memory sizes.
   MemorySize::MemorySize(BlockPoolParms* aParms)
   {
      mStateSize     = BlockPoolShortTermState::getMemorySize();
      mBlockBoxArraySize = BlockBoxArray::getMemorySize(aParms);
      mMemorySize = mStateSize + mBlockBoxArraySize;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockPoolShortTerm::getMemorySize(BlockPoolParms* aParms)
{
   MemorySize tMemorySize(aParms);
   return tMemorySize.mMemorySize;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockPoolShortTerm::BlockPoolShortTerm()
{
   // All null.
   mOwnMemoryFlag = false;
   mMemory = 0;
}

BlockPoolShortTerm::~BlockPoolShortTerm()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the block pool for long term blocks. It allocates memory
// for the block array and initializes the index stack. It is passed the
// number of blocks to allocate and the size of the blocks. Memory for one
// dummy block is allocated because index zero is reserved to indicate a
// null block.
//
// For aNumBlocks==10 blocks will range 0,1,2,3,4,5,6,7,8,9
// A block index of cInvalid indicates an invalid block.
//
// An index stack is used to manage free list access to the blocks
// The stack is initialized for a free list by pushing indices onto it.
// For aAllocate==10 this will push 0,1,2,3,4,5,6,7,8,9
//
// When a block is allocated, an index is popped off of the stack.
// When a block is deallocated, its index is pushed back onto the stack.
//

void BlockPoolShortTerm::initialize(BlockPoolParms* aParms)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize memory.

   // Deallocate memory, if any exists.
   finalize();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aParms->mMemory == 0)
   {
      mMemory = malloc(BlockPoolShortTerm::getMemorySize(aParms));
      mOwnMemoryFlag = true;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aParms->mMemory;
      mOwnMemoryFlag = false;
   }

   // Calculate memory sizes.
   MemorySize tMemorySize(aParms);

   // Calculate memory addresses.
   MemoryPtr tMemoryPtr(mMemory);

   char* tStateMemory         = tMemoryPtr.cfetch_add(tMemorySize.mStateSize);
   char* tBlockBoxArrayMemory = tMemoryPtr.cfetch_add(tMemorySize.mBlockBoxArraySize);
   
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Construct the state.
   if (aParms->mConstructorFlag)
   {
      // Call the constructor.
      mX = new(tStateMemory)BlockPoolShortTermState;
   }
   else
   {
      // The constructor has already been called.
      mX = (BlockPoolShortTermState*)tStateMemory;
   }
   // Initialize the state.
   mX->initialize(aParms);

   // Store the pointer to the parameters.
   mParms = aParms;

   // Initialize the block box array.
   mBlocks.initialize(aParms,tBlockBoxArrayMemory);

   // Mark this block pool initialization as valid.
   aParms->mValidFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Deallocate memory for the block pool.

void BlockPoolShortTerm::finalize()
{
   mBlocks.finalize();

   if (mOwnMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
   }
   mMemory = 0;
   mOwnMemoryFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Size, the number of blocks that are available to be allocated.

int BlockPoolShortTerm::size()
{ 
   return (int)(mX->mIndexCount & 0x7FFFFFFF);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a block from the pool, this allocates a block.
// Return true if successful, false if the block pool is empty.

bool BlockPoolShortTerm::allocate(void** aBlockPointer,BlockHandle* aBlockHandle)
{
   // Guard.
   if (mX->mNumBlocks==0) return false;

   // Increment atomic 64 bit counter. This will last for years before it rolls over.
   unsigned long long tIndexCount = mX->mIndexCount.fetch_add(1,memory_order_relaxed);

   // Calculate the block index so that it cycles 0..mNumBlocks-1.
   int tBlockIndex = tIndexCount % mX->mNumBlocks;

   // Return a pointer to the block at that index.
   if (aBlockPointer)
   {
      *aBlockPointer = mBlocks.getBlockPtr(tBlockIndex);
   }

   // Return the memory handle for the block.
   if (aBlockHandle)
   {
      aBlockHandle->set(mParms->mPoolIndex, tBlockIndex);
   }

   // Done
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a block back to the pool, this deallocates a block.
// This does nothing, because it is short term.
// This should not get called.

void BlockPoolShortTerm::deallocate(BlockHandle aBlockHandle)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a block, given its memory handle.

void* BlockPoolShortTerm::getBlockPtr(BlockHandle aBlockHandle)
{
   // Return the address of the block within the block array.
   return mBlocks.getBlockPtr(aBlockHandle.mBlockIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers

void BlockPoolShortTerm::show()
{
   printf("BlockPoolShorTerm size %d $ %d\n", mParms->mPoolIndex,size());
}

}//namespace
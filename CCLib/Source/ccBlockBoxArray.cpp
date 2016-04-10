/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "cc_functions.h"
#include "ccDefs.h"
#include "ccMemoryPtr.h"
#include "ccBlockBoxArray.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.
 
int BlockBoxArrayState::getMemorySize()
{
   return cc_round_upto16(sizeof(BlockBoxArrayState));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

BlockBoxArrayState::BlockBoxArrayState()
{
   // All null
   mNumBlocks=0;
   mBlockSize=0;
   mBlockBoxSize=0;
   mPoolIndex=0;
}

void BlockBoxArrayState::initialize(BlockPoolParms* aParms)
{
   // Do not initialize, if already initialized.
   if (!aParms->mConstructorFlag) return;

   // Store members.
   mNumBlocks    = aParms->mNumBlocks;
   mBlockSize    = cc_round_upto16(aParms->mBlockSize);
   mBlockBoxSize = mBlockSize + cBlockHeaderSize;;
   mPoolIndex    = aParms->mPoolIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This sub class calculates and stores the memory sizes needed by the class.

class BlockBoxArray::MemorySize
{
public:
   // Members.
   int mStateSize;
   int mBlockSize;
   int mBlockBoxSize;
   int mArraySize;
   int mMemorySize;

   // Calculate and store memory sizes.
   MemorySize::MemorySize(BlockPoolParms* aParms)
   {
      mStateSize    = BlockBoxArrayState::getMemorySize();
      mBlockSize    = cc_round_upto16(aParms->mBlockSize);
      mBlockBoxSize = cBlockHeaderSize + mBlockSize;
      mArraySize    = cc_round_upto16(cNewArrayExtraMemory + aParms->mNumBlocks*mBlockBoxSize);
      mMemorySize   = mStateSize + mArraySize;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockBoxArray::getMemorySize(BlockPoolParms* aParms)
{
   MemorySize tMemorySize(aParms);
   return tMemorySize.mMemorySize;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockBoxArray::BlockBoxArray()
{
   // All null
   mX = 0;
   mFreeMemoryFlag = false;
   mMemory = 0;
   mArray=0;
}

BlockBoxArray::~BlockBoxArray()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate memory for the block array. It is passed the number of blocks to 
// allocate and the size of the blocks.

void BlockBoxArray::initialize(BlockPoolParms* aParms,void* aMemory)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize memory.

   // Deallocate memory, if any exists.
   finalize();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mMemory = malloc(BlockBoxArray::getMemorySize(aParms));
      mFreeMemoryFlag = true;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mFreeMemoryFlag = false;
   }

   // Calculate memory sizes.
   MemorySize tMemorySize(aParms);

   // Calculate memory addresses.
   MemoryPtr tMemoryPtr(mMemory);

   char* tStateMemory = tMemoryPtr.cfetch_add(tMemorySize.mStateSize);
   char* tArrayMemory = tMemoryPtr.cfetch_add(tMemorySize.mArraySize);

   // Construct the state.
   if (aParms->mConstructorFlag)
   {
      // Call the constructor.
      mX = new(tStateMemory)BlockBoxArrayState;
   }
   else
   {
      // The constructor has already been called.
      mX = (BlockBoxArrayState*)tStateMemory;
   }
   // Initialize the state.
   mX->initialize(aParms);

   // Set the array pointer value.
   mArray = tArrayMemory;

   // Initialize the block headers, if they have not
   // already been initialized.
   if (aParms->mConstructorFlag)
   {
      // Initialize block headers.
      for (int i = 0; i < mX->mNumBlocks; i++)
      {
         // Header pointer.
         BlockHeader* tHeader = header(i);
         // Call Header constructor.
         new(tHeader)BlockHeader;
         // Set header variables.
         tHeader->mBlockHandle.set(mX->mPoolIndex, i);
      }
   }

   // Store block array parameters. These can be used elsewhere.
   aParms->mBlockHeaderSize = cBlockHeaderSize;
   aParms->mBlockBoxSize    = tMemorySize.mBlockBoxSize;
   aParms->mBlockBoxPtr     = mArray;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void BlockBoxArray::finalize()
{
   if (mFreeMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
   }
   mMemory = 0;
   mFreeMemoryFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a block, based on block array index

char* BlockBoxArray::blockBox(int aIndex)
{
   char*  tBlockBox = &mArray[mX->mBlockBoxSize*aIndex];
   return tBlockBox;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a header, based on block array index

BlockHeader* BlockBoxArray::header(int aIndex)
{
   char*  tBlockBox = &mArray[mX->mBlockBoxSize*aIndex];
   BlockHeader* tHeader = (BlockHeader*)tBlockBox;
   return tHeader;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a body, based on block array index

char* BlockBoxArray::block(int aIndex)
{
   char*  tBlockBox = &mArray[mX->mBlockBoxSize*aIndex];
   char*  tBlock = tBlockBox + cBlockHeaderSize;
   return tBlock;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the handle of a block, given its address.

BlockHandle BlockBoxArray::getBlockHandle(void* aBlockPtr)
{
   BlockHandle tBlockHandle;
   if (aBlockPtr==0) return tBlockHandle;

   char*  tBlock = (char*)aBlockPtr;
   BlockHeader* tHeader = (BlockHeader*)(tBlock - cBlockHeaderSize);

   tBlockHandle = tHeader->mBlockHandle;
   return tBlockHandle;
}

}//namespace
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
#include "ccBlockBoxArray.h"

namespace CC
{

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Constructor, initialize members for an empty stack of size zero 

BlockBoxArrayState::BlockBoxArrayState()
{
   // All null
   mNumBlocks=0;
   mBlockSize=0;
   mBlockBoxSize=0;
   mPoolIndex=0;
}

void BlockBoxArrayState::initialize(int aNumBlocks,int aBlockSize,int aPoolIndex)
{
   // Round block size to to 16 byte boundary.
   int tBlockSize = cc_round_upto16(aBlockSize);

   // Store members.
   mNumBlocks    = aNumBlocks;
   mBlockSize    = tBlockSize;
   mBlockBoxSize = mBlockSize + cHeaderSize;;
   mPoolIndex    = aPoolIndex;
}

int BlockBoxArrayState::getMemorySize()
{
   return cc_round_upto16(sizeof(BlockBoxArrayState));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockBoxArray::BlockBoxArray()
{
   // All null
   mX = 0;
   mExternalMemoryFlag = false;
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

void BlockBoxArray::initialize(int aNumBlocks,int aBlockSize,int aPoolIndex,void* aMemory)
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
      mMemory = malloc(BlockBoxArray::getMemorySize(aNumBlocks,aBlockSize));
      mExternalMemoryFlag = false;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mExternalMemoryFlag = true;
   }

   // Calculate memory sizes.
   int tStateSize = BlockBoxArrayState::getMemorySize();

   int tBlockSize    = cc_round_upto16(aBlockSize);
   int tBlockBoxSize = cHeaderSize + tBlockSize;

   int tArraySize    = aNumBlocks*tBlockBoxSize;

   // Calculate memory addresses.
   char* tStateMemory = (char*)mMemory;
   char* tArrayMemory = tStateMemory + tStateSize;

   // Initialize the state.
   mX = new(tStateMemory) BlockBoxArrayState;
   mX->initialize(aNumBlocks,aBlockSize,aPoolIndex);

   // Initialize the array.
   mArray = tArrayMemory;

   // Initialize block headers.
   for (int i = 0; i < mX->mNumBlocks; i++)
   {
      // Header pointer.
      BlockHeader* tHeader = header(i);
      // Call Header constructor.
      new(tHeader) BlockHeader;
      // Set header variables.
      tHeader->mBlockHandle.set(mX->mPoolIndex,i);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void BlockBoxArray::finalize()
{
   if (!mExternalMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
      mMemory = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockBoxArray::getMemorySize(int aNumBlocks,int aBlockSize)
{
   // Calculate memory sizes.
   int tStateSize = BlockBoxArrayState::getMemorySize();

   int tBlockSize    = cc_round_upto16(aBlockSize);
   int tBlockBoxSize = cHeaderSize + tBlockSize;

   int tArraySize    = aNumBlocks*tBlockBoxSize;
   int tMemorySize   = tStateSize + tArraySize;

   return tMemorySize;
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
   char*  tBlock = tBlockBox + cHeaderSize;
   return tBlock;
}

}//namespace
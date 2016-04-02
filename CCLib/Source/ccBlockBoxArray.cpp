/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "ccBlockBoxArray.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockBoxArray::BlockBoxArray()
{
   // All null
   mNumBlocks=0;
   mBlockSize=0;
   mHeaderSize=0;
   mBlockBoxSize=0;
   mPoolIndex=0;
   mMemory=0;
}

BlockBoxArray::~BlockBoxArray()
{
   // Deallocate the array
   if (mMemory) free(mMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate memory for the block array. It is passed the number of blocks to 
// allocate and the size of the blocks.

void BlockBoxArray::initialize(int aNumBlocks,int aBlockSize,int aPoolIndex)
{
   finalize();

   // Round block size to to 16 byte boundary.
   int tBlockSize = ((aBlockSize & 0xF) != 0) ? ((aBlockSize & ~0xF) + 0x10) : aBlockSize;

   // Store members.
   mNumBlocks    = aNumBlocks;
   mBlockSize    = tBlockSize;
   mHeaderSize   = cHeaderSize;
   mBlockBoxSize = mBlockSize + cHeaderSize;;
   mPoolIndex = aPoolIndex;

   // Allocate memory for the array.
   mMemory = (char*)malloc(mNumBlocks*mBlockBoxSize);

   // Initialize block headers.
   for (int i = 0; i < mNumBlocks; i++)
   {
      BlockHeader* tHeader = header(i);
      tHeader->mBlockHandle.set(mPoolIndex,i);
   }
}

void BlockBoxArray::finalize()
{
   // Deallocate the array
   if (mMemory)
   {
      free(mMemory);
      mMemory = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a block, based on block array index

char* BlockBoxArray::blockBox(int aIndex)
{
   char*  tBlockBox = &mMemory[mBlockBoxSize*aIndex];
   return tBlockBox;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a header, based on block array index

BlockHeader* BlockBoxArray::header(int aIndex)
{
   char*  tBlockBox = &mMemory[mBlockBoxSize*aIndex];
   BlockHeader* tHeader = (BlockHeader*)tBlockBox;
   return tHeader;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a body, based on block array index

char* BlockBoxArray::block(int aIndex)
{
   char*  tBlockBox = &mMemory[mBlockBoxSize*aIndex];
   char*  tBlock = tBlockBox + cHeaderSize;
   return tBlock;
}

}//namespace
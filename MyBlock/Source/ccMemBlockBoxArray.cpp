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

#include "ccMemBlockBoxArray.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MemBlockBoxArray::MemBlockBoxArray()
{
   // All null
   mNumBlocks=0;
   mBlockSize=0;
   mHeaderSize=0;
   mBlockBoxSize=0;
   mMemPoolIndex=0;
   mMemory=0;
}

MemBlockBoxArray::~MemBlockBoxArray()
{
   // Deallocate the array
   if (mMemory) free(mMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate memory for the block array. It is passed the number of blocks to 
// allocate and the size of the blocks.

void MemBlockBoxArray::initialize(int aNumBlocks,int aBlockSize,int aMemPoolIndex)
{
   finalize();
   // Store members.
   mNumBlocks    = aNumBlocks;
   mBlockSize    = aBlockSize;
   mHeaderSize   = cHeaderSize;
   mBlockBoxSize = aBlockSize + cHeaderSize;;
   mMemPoolIndex = aMemPoolIndex;

   // Allocate memory for the array.
   mMemory = (char*)malloc(mNumBlocks*mBlockBoxSize);

   // Initialize block headers.
   for (int i = 0; i < mNumBlocks; i++)
   {
      MemBlockHeader* tHeader = header(i);
      tHeader->mMemHandle.set(mMemPoolIndex,i);
   }
}

void MemBlockBoxArray::finalize()
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

char* MemBlockBoxArray::blockBox(int aIndex)
{
   char*  tBlockBox = &mMemory[mBlockBoxSize*aIndex];
   return tBlockBox;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a header, based on block array index

MemBlockHeader* MemBlockBoxArray::header(int aIndex)
{
   char*  tBlockBox = &mMemory[mBlockBoxSize*aIndex];
   MemBlockHeader* tHeader = (MemBlockHeader*)tBlockBox;
   return tHeader;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a body, based on block array index

char* MemBlockBoxArray::block(int aIndex)
{
   char*  tBlockBox = &mMemory[mBlockBoxSize*aIndex];
   char*  tBlock = tBlockBox + cHeaderSize;
   return tBlock;
}

}//namespace
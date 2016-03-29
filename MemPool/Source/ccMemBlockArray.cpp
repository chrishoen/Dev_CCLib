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

#include "ccMemBlockArray.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MemBlockArray::MemBlockArray()
{
   // All null
   mNumBlocks=0;
   mBlockSize=0;
   mHeaderSize=0;
   mBodySize=0;
   mMemPoolIndex=0;
   mMemory=0;
}

MemBlockArray::~MemBlockArray()
{
   // Deallocate the array
   if (mMemory) free(mMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate memory for the block array. It is passed the number of blocks to 
// allocate and the size of the blocks.

void MemBlockArray::initialize(int aNumBlocks,int aBlockBodySize,int aMemPoolIndex)
{
   finalize();
   // Store members.
   mNumBlocks    = aNumBlocks;
   mBlockSize    = aBlockBodySize + cHeaderSize;
   mHeaderSize   = cHeaderSize;
   mBodySize     = aBlockBodySize;
   mMemPoolIndex = aMemPoolIndex;

   // Allocate memory for the array.
   mMemory = (char*)malloc(mNumBlocks*mBlockSize);

   // Initialize block headers.
   for (int i = 0; i < mNumBlocks; i++)
   {
      MemBlockHeader* tHeader = header(i);
      tHeader->mMemHandle.set(mMemPoolIndex,i);
   }
}

void MemBlockArray::finalize()
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

char* MemBlockArray::block(int aIndex)
{
   char* tBlock = &mMemory[mBlockSize*aIndex];
   return tBlock;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a header, based on block array index

MemBlockHeader* MemBlockArray::header(int aIndex)
{
   char*  tBlock = &mMemory[mBlockSize*aIndex];
   MemBlockHeader* tHeader = (MemBlockHeader*)tBlock;
   return tHeader;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to a body, based on block array index

char* MemBlockArray::body(int aIndex)
{
   char*  tBlock = &mMemory[mBlockSize*aIndex];
   char*  tBody = tBlock + cHeaderSize;
   return tBody;
}

}//namespace
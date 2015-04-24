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

#include "ccBlockArray.h"

namespace CC
{
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   BlockArray::BlockArray()
   {
      // All null
      mAllocate = 0;
   }

   BlockArray::~BlockArray()
   {
      // Deallocate the array
      if (mMemory) free(mMemory);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Allocate memory for the block array. It is passed the number of blocks to 
   // allocate and the size of the blocks.

   void BlockArray::initialize(int aAllocate, int aBlockSize)
   {
      // Store members
      mAllocate = aAllocate;
      mBlockSize = aBlockSize;

      // Allocate memory for the array
      mMemory = (char*)malloc(mAllocate*mBlockSize);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Return a pointer to a block, based on block array index

   char* BlockArray::e(int aIndex)
   {
      return &mMemory[mBlockSize*aIndex];
   }

}//namespace
/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "ccBlockPoolBase.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

BlockPoolBase::BlockPoolBase()
{
   // All null.
   mBaseClassExternalMemoryFlag = false;
   mBaseClassMemory=0;
   mParms=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate memory for the block array. It is passed the number of blocks to
// allocate, the size of the block body, and the memory pool index for the
// block aarray.

void BlockPoolBase::initializeBase(BlockPoolParms* aParms,void* aMemory)
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
      mBaseClassMemory = malloc(BlockPoolBase::getMemorySize(aParms));
      mBaseClassExternalMemoryFlag = false;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mBaseClassMemory = aMemory;
      mBaseClassExternalMemoryFlag = true;
   }

   // Calculate memory sizes.
   int tParmSize   = BlockPoolParms::getMemorySize();
   int tArraySize  = BlockBoxArray::getMemorySize(aParms->mNumBlocks,aParms->mBlockSize);

   // Calculate memory addresses.
   char* tParmMemory = (char*)mBaseClassMemory;
   char* tArrayMemory = tParmMemory + tParmSize;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Initialize the copy of the parameters.
   mParms = new(tParmMemory)BlockPoolParms(*aParms);

   // Initialize the block box array.
   mBlocks.initialize(aParms->mNumBlocks,aParms->mBlockSize,aParms->mPoolIndex,tArrayMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void BlockPoolBase::finalizeBase()
{
   if (!mBaseClassExternalMemoryFlag)
   {
      if (mBaseClassMemory)
      {
         free(mBaseClassMemory);
      }
      mBaseClassMemory = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockPoolBase::getMemorySize(BlockPoolParms* aParms)
{
   int tParmSize   = BlockPoolParms::getMemorySize();
   int tArraySize  = BlockBoxArray::getMemorySize(aParms->mNumBlocks,aParms->mBlockSize);
   int tMemorySize = tParmSize + tArraySize;
   return tMemorySize;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers

void BlockPoolBase::show()
{
   printf("MemBlockPool size %d\n", size());
}






}//namespace
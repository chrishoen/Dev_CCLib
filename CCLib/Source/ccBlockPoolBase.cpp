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
   mBaseClassFreeMemoryFlag = false;
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
   finalizeBase();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mBaseClassMemory = malloc(BlockPoolBase::getMemorySize(aParms));
      mBaseClassFreeMemoryFlag = true;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mBaseClassMemory = aMemory;
      mBaseClassFreeMemoryFlag = false;
   }

   // Calculate memory sizes.
   int tArraySize  = BlockBoxArray::getMemorySize(aParms);

   // Calculate memory addresses.
   char* tArrayMemory = (char*)mBaseClassMemory;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Store the pointer to the parameters.
   mParms = aParms;

   // Initialize the block box array.
   mBlocks.initialize(aParms,tArrayMemory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void BlockPoolBase::finalizeBase()
{
   mBlocks.finalize();

   if (mBaseClassFreeMemoryFlag)
   {
      if (mBaseClassMemory)
      {
         free(mBaseClassMemory);
      }
   }
   mBaseClassMemory = 0;
   mBaseClassFreeMemoryFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int BlockPoolBase::getMemorySize(BlockPoolParms* aParms)
{
   int tArraySize  = BlockBoxArray::getMemorySize(aParms);
   int tMemorySize = tArraySize;
   return tMemorySize;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers

void BlockPoolBase::show()
{
   printf("MemBlockPool size %d $ %d\n", mParms->mPoolIndex,size());
}






}//namespace
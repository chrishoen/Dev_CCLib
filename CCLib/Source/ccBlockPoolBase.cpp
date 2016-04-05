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
   int tParmSize   = BlockPoolParms::getMemorySize();
   int tArraySize  = BlockBoxArray::getMemorySize(aParms);

   // Calculate memory addresses.
   char* tParmMemory = (char*)mBaseClassMemory;
   char* tArrayMemory = tParmMemory + tParmSize;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   // Construct the copy of the parameters.
   if (aParms->mConstructorFlag)
   {
      // Call the constructor.
      mParms = new(tParmMemory)BlockPoolParms(*aParms);
   }
   else
   {
      // The constructor has already been called.
      mParms = (BlockPoolParms*)tParmMemory;
   }
   // Mark that these are not the original parameters, they are a copy.
   mParms->mOriginalFlag = false;

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
   int tParmSize   = BlockPoolParms::getMemorySize();
   int tArraySize  = BlockBoxArray::getMemorySize(aParms);
   int tMemorySize = tParmSize + tArraySize;
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
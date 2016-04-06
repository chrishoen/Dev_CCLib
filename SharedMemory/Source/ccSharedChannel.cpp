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


#define  _CCSHAREDCHANNEL_CPP_
#include "ccSharedChannel.h"

using namespace std;

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

SharedChannel::SharedChannel()
{
   // All null.
   mFreeMemoryFlag = false;
   mMemory = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destructor, deallocate the array

SharedChannel::~SharedChannel()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the stack to a fixed size. It initializes member
// variables and and the stack array, given external memory.

void SharedChannel::initialize(void* aMemory)
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
      mMemory = malloc(SharedChannel::getMemorySize());
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
   int tQueueSize = LFValueQueue<int>::getMemorySize(cNumElements);

   // Calculate memory addresses.
   char* tQueueMemory = (char*)mMemory;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   mQueue.initialize(cNumElements,tQueueMemory);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SharedChannel::finalize()
{
   mQueue.finalize();

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
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int SharedChannel::getMemorySize()
{
   int tQueueSize = LFValueQueue<int>::getMemorySize(cNumElements);
   int tMemorySize = tQueueSize;
   return tMemorySize;
}

}//namespace
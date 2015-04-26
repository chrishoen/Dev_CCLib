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

#include "ccCriticalSection.h"
#include "ccPointerCircular.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

PointerCircular::PointerCircular()
{
   // All null
   mArray    = 0;
   mPutIndex = 0;
   mGetIndex = 0;
   mAllocate = 0;
   mCount    = 0;
}

PointerCircular::~PointerCircular()
{
   // Deallocate the array
   if (mArray) delete mArray;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Allocate memory for the pointer array and initialize the indices. 
// aAllocate is the number of pointers to allocate, the size of the array.

void PointerCircular::initialize(int aAllocate)
{
   // Allocate memory for the array
   mArray = new void*[aAllocate];

   // Initialize variables
   mPutIndex    = 0;
   mGetIndex    = 0;
   mAllocate = aAllocate;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a pointer into the circular array. This is used during initialization
// of short term memory pools by filling up the pointer array with allocated
// block addresses. It cycles through the array via the PutIndex.

bool PointerCircular::put (void* aPointer)
{
   // Guard
   if (mPutIndex == mAllocate) return false;

   // Critical section
   enterCriticalSection();

   // Copy the pointer into the array.
   mArray[mPutIndex] = aPointer;

   // Increment the index
   ++mPutIndex;

   // Critical section
   leaveCriticalSection();

   // Done
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a pointer from the circular array. This is used to allocate a block
// from a short term memory pool. It returns the address of an allocated
// block. It does so in a circular manner by indexing through the pointer
// array, via the GetIndex.

void* PointerCircular::get ()
{
   // Critical section
   enterCriticalSection();

   // Get the pointer at the current index
   void* tPointer = mArray[mGetIndex];

   // Increment the index
   if (++mGetIndex == mAllocate) mGetIndex = 0;

   // Increment the usage counter
   mCount++;

   // Critical section
   leaveCriticalSection();

   // Return the pointer
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is called by an owner to indicate that it is done with its current
// element. It decrements the usage counter. It is used to track usage of
// the circular buffer.

void PointerCircular::done ()
{
   // Critical section
   enterCriticalSection();

   // Decrement the usage counter
   mCount--;

   // Critical section
   leaveCriticalSection();

}

}//namespace


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
#include "my_functions.h"

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

PointerCircular::PointerCircular()
{
   // All null
   mArray    = 0;
   mPutIndex    = 0;
   mGetIndex    = 0;
   mAllocate = 0;
}

PointerCircular::~PointerCircular()
{
   // Deallocate the array
   if (mArray) delete mArray;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void PointerCircular::initialize(int aAllocate)
{
   // Allocate memory for the array
   mArray    = new void*[aAllocate];

   // Initialize variables
   mPutIndex    = 0;
   mGetIndex    = 0;
   mAllocate = aAllocate;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a pointer into the circular array.

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
// Get a pointer from the array.

void* PointerCircular::get ()
{
   // Critical section
   enterCriticalSection();

   // Get the pointer at the current index
   void* tPointer = mArray[mGetIndex];

   // Increment the index
   if (++mGetIndex == mAllocate) mGetIndex = 0;

   // Critical section
   leaveCriticalSection();

   // Return the pointer
   return tPointer;
}

}//namespace


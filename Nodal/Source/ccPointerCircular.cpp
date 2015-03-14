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

   // initialize variables
   mPutIndex    = 0;
   mGetIndex    = 0;
   mAllocate = aAllocate;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Push an element onto the stack. Return false if stack is full.

bool PointerCircular::put (void* aPointer)
{
   // Guard
   if (mPutIndex == mAllocate) return false;

   //Copy the source element to the element at the stack index
   mArray[mPutIndex] = aPointer;
   // Increment the index
   ++mPutIndex;

   // Done
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Pop an element off of the stack. Return null if stack is empty.

void* PointerCircular::get ()
{
   // Get the pointer at the current index
   void* tPointer = mArray[mGetIndex];

   // Increment the index
   if (++mGetIndex == mAllocate) mGetIndex = 0;

   // Return the pointer
   return tPointer;
}

}//namespace


/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccMessageHeap.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

MessageHeap::MessageHeap ()
{
   // Null values
   mHeapBeginPtr = 0;
   mHeapEndPtr = 0;
   mWorkingPtr = 0;
}

MessageHeap::~MessageHeap ()
{
   // It the heap was initialized and allocated system memory
   if (mHeapBeginPtr != 0)
   {
      // Deallocate the system memory
      free(mHeapBeginPtr);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void MessageHeap::initialize(size_t aAllocate)
{
   // Allocate system memory for the message heap. The malloc call returns a 
   // pointer that is aligned on an 8 byte boundary for 32 bit systmes or
   // returns a pointer that is aligned a 16 byte boundary for 64 bit systems.
   mHeapBeginPtr = (char*)malloc(aAllocate);

   // Set the heap end pointer.
   mHeapEndPtr = mHeapBeginPtr + aAllocate;

   // Set the working pointer to point to the start of the message heap.
   mWorkingPtr = mHeapBeginPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This allocates a sub segment of the message memory heap.

void* MessageHeap::allocate(size_t aSize)
{
   // To allocate from the heap, store a copy of the current working pointer.
   char* tAllocatePtr = mWorkingPtr;

   // Advance the current working pointer by the size to allocate.
   mWorkingPtr += aSize;

   // If this advancement goes past the end of the memory allocated for the
   // heap, then there is a rollover.
   if (mWorkingPtr >= mHeapEndPtr)
   {
      // Set the current working pointer back to the start of the heap
      mWorkingPtr = mHeapBeginPtr;
      // Allocate to the current working pointer.
      tAllocatePtr = mHeapBeginPtr;
   }

   // Return the pointer
   return tAllocatePtr;
}

}//namespace




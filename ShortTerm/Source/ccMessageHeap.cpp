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

}

}//namespace




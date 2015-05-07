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
// This is an inline function that aligns a size to round up to an eight
// byte boundary for 32 byte systems or rounds up to a sixteen byte boundary
// for 64 bit systems. It is used below. NOTE: I tested this independently.

// For example, for 32 bit systems
//    MessageHeap_alignSize(0) == 0
//    MessageHeap_alignSize(1) == 8
//    MessageHeap_alignSize(7) == 8
//    MessageHeap_alignSize(8) == 8
//    MessageHeap_alignSize(9) == 16


inline size_t MessageHeap_roundUpSize(size_t aSize)
{
   // If this is a 32 bit system
   if (sizeof(int*) == 4)
   {
      // Align the size to be on an eight byte boundary
      if ((aSize & 7) == 0) return aSize;
      else return ((aSize >> 3) << 3) + 8;
   }
   else
   // Else this is a 64 bit system
   {
      // Align the size to be on a sixteen byte boundary
      if ((aSize & 15) == 0) return aSize;
      else return ((aSize >> 4) << 4) + 16;
   }
}



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
   // It the heap was initialized and has allocated system memory
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
   // Round up the size to be on an eight byte boundary for 32 bit systems
   // or a sixteen byte bounday for 64 bit systems. In other words, for a 32
   // bit system, if you want to allocate one byte, this will allocate eight
   // bytes. This keeps everything on byte boundaries so as to be consistent
   // with calls to malloc.
   size_t tSize = MessageHeap_roundUpSize(aAllocate);

   // Allocate system memory for the message heap. NOTE: the malloc call
   // returns a  pointer that is aligned on an 8 byte boundary for 32 bit
   // systems or returns a pointer that is aligned a 16 byte boundary for 64
   // bit systems.
   mHeapBeginPtr = (char*)malloc(tSize);

   // Set the heap end pointer. This should point to one byte after the
   // allocated region.
   mHeapEndPtr = mHeapBeginPtr + tSize;

   // Set the working pointer to point to the start of the message heap.
   mWorkingPtr = mHeapBeginPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This allocates a sub segment of the message memory heap.

void* MessageHeap::allocate(size_t aSize)
{
   // Round up the size to be on an eight byte boundary for 32 bit systems
   // or a sixteen byte bounday for 64 bit systems. In other words, for a 32
   // bit system, if you want to allocate one byte, this will allocate eight
   // bytes. This keeps everything on byte boundaries so as to be consistent
   // with calls to malloc.
   size_t tSize = MessageHeap_roundUpSize(aSize);

   // To allocate from the heap, store a copy of the current working pointer.
   // This is the address on the message heap that will be allocated.
   char* tAllocatePtr = mWorkingPtr;

   // Advance the current working pointer by the size to allocate.
   mWorkingPtr += aSize;

   // If this advancement goes past the end of the memory allocated for the
   // heap, then there is a rollover. This should be infrequent.
   if (mWorkingPtr >= mHeapEndPtr)
   {
      // Set the current working pointer back to the start of the heap
      mWorkingPtr = mHeapBeginPtr;
      // Allocate to the current working pointer.
      tAllocatePtr = mHeapBeginPtr;
   }

   // Return the pointer to the allocated memory.
   return (void*)tAllocatePtr;
}

}//namespace




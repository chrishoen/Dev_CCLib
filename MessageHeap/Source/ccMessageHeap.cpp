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

   mSequenceNumber = 0;
   mPreviousMessageHeader = 0;
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
   //--------------------------------------------------------------------------
   // Calculate the size to allocate.

   // Round up the size to be on an eight byte boundary for 32 bit systems
   // or a sixteen byte bounday for 64 bit systems. In other words, for a 32
   // bit system, if you want to allocate one byte, this will allocate eight
   // bytes. This keeps everything on byte boundaries so as to be consistent
   // with calls to malloc.
   size_t tSize = MessageHeap_roundUpSize(aSize);

   // Increase the allocated size to include the header. This means that the
   // allocated size will include size for the requested number of bytes for
   // the message and for the heap header and that it will be on the correct
   // byte boundary.
   tSize += HeaderAllocate;

   //--------------------------------------------------------------------------
   // Calculate the pointer for the allocated segment.

   // To allocate from the heap, store a copy of the current working pointer.
   // This is the address on the message heap that will be allocated.
   char* tAllocatePtr = mWorkingPtr;

   // Advance the current working pointer by the size to allocate.
   mWorkingPtr += tSize;

   // If this advancement goes past the end of the memory allocated for the
   // heap, then there is a rollover. This should be infrequent.
   if (mWorkingPtr >= mHeapEndPtr)
   {
      // Set the current working pointer back to the start of the heap
      mWorkingPtr = mHeapBeginPtr;
      // Allocate to the current working pointer.
      tAllocatePtr = mHeapBeginPtr;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Pointer and header management

   // Set a header pointer to point to the beginning of the allocated region.
   Header* tHeaderPtr = (Header*)tAllocatePtr;

   // Set a body pointer to point after the header pointer.
   char* tBodyPtr   = tAllocatePtr + HeaderAllocate;

   // Set the allocated region header previous pointer to point to the header
   // of the previous message that was allocated.
   tHeaderPtr->mPreviousMessageHeader = mPreviousMessageHeader;

   // Set the sequence number for the allocated message.
   tHeaderPtr->mSequenceNumber = mSequenceNumber++;

   // Store the pointer to the allocated message for the next allocation.
   mPreviousMessageHeader = tHeaderPtr;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Return the pointer to the allocated memory for the message body.

   return (void*)tBodyPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This checks a memory segment for consistency, it should show if a message
// in the heap has been overrun. It returns true if the memory seqgment was
// found to be consistent.

bool MessageHeap::check(void* aMessage)
{
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Convert the input pointer to point to the message body.

   char* tBodyCharPtr = (char*)aMessage;

   // Calculate pointers to the message header. These should point to the 
   // beginning of the memory that was allocated for the message.

   char*    tHeaderCharPtr = tBodyCharPtr - HeaderAllocate;
   Header*  tHeaderPtr     = (Header*)tHeaderCharPtr;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Check the validity of the pointer.

   // Check the range of the header pointer.
   if ((tHeaderCharPtr < mHeapBeginPtr) || (tHeaderCharPtr >= mHeapEndPtr))
   {
      return false;
   }

   // Check the sync word of the header
   if (tHeaderPtr->mSyncWord != HeaderSyncWord)
   {
      return false;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Check the validty of the message with the previous message.

   // Extract pointers to the previous message header. 
   Header*  tPreviousHeaderPtr     = tHeaderPtr->mPreviousMessageHeader;
   char*    tPreviousHeaderCharPtr = (char*)tPreviousHeaderPtr;

   // Check the range of the previous header pointer.
   if ((tPreviousHeaderCharPtr < mHeapBeginPtr) || (tPreviousHeaderCharPtr >= mHeapEndPtr))
   {
      return false;
   }

   // Check the sync word of the previous header
   if (tPreviousHeaderPtr->mSyncWord != HeaderSyncWord)
   {
      return false;
   }

   // Check the sequence number of the previous message.
   if (tHeaderPtr->mSequenceNumber != tPreviousHeaderPtr->mSyncWord + 1)
   {
      return false;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // All validity checks have passed.

   return true;
}

}//namespace




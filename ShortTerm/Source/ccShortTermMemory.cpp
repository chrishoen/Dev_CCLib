/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccShortTermMemory.h"

namespace CC
{

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Regional variables. These variables have scope only within this file.
// They maintain storage as global variables, but they are only visible to
// code that is contained in this file.

// This is a pointer to the begining of the system memory that is allocated
// for the message heap.
static char* rHeapBeginPtr = 0;

// This is a pointer to one byte after the end of the message heap. It is 
// equal to mmHeapBeginPtr + mAllocate.
static char* rHeapEndPtr = 0;

// This is a pointer that cycles through the message heap memory, when
// messages are allocated. Its current value points at the next available 
// section of the heap. When memory is allocated from the heap, the current
// value is returned and the pointer is incremented apprpriately. If there 
// is a rollover, then it is set back to point to the beginining of the heap.
static char* rWorkingPtr = 0;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// This is a header that is placed at the start of every message that is 
// allocated from the message heap. This header is only used by message
// heap processing and has nothing to do with actual message headers.
// Values of this structure are set when a message is allocated and they
// are tested when a message is checked for consistency.

typedef struct Header
{
   // This is a synch word, if it is not correct then the message has been
   // corrupted, the message heap has been overrun.
   unsigned mSyncWord;
      
   // This is a sequence number for the message. It is assigned when the
   // message is allocated.
   unsigned mSequenceNumber;

   // This is a pointer to the previous message in the message heap, the
   // last message that was allocated before this message. The sequence 
   // number of the previous message should be one more than the sequence
   // number of a message that is being checked.
   Header* mPreviousMessageHeader;

} Header;

// This structure must not take up more than sixteen bytes.
enum { HeaderAllocate = 16 };

// This is the value for the sync word.
enum { HeaderSyncWord = 0xAAAABBBB };

// This is a sequence number that is inserted into the header of any
// message that is allocated. It is used for consistency checks.
static unsigned rSequenceNumber;

// This is a pointer to the header of the previous message that was 
// allocated. It is used to compare its sequence number with that of a
// a message that is being checked.
static Header* rPreviousMessageHeader;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a function that aligns a size to round up to an eight byte boundary
// for 32 byte systems or rounds up to a sixteen byte boundary for 64 bit
// systems. It is used below. NOTE: I have tested this independently.

// For example, for 32 bit systems
//    MessageHeap_alignSize(0) == 0
//    MessageHeap_alignSize(1) == 8
//    MessageHeap_alignSize(7) == 8
//    MessageHeap_alignSize(8) == 8
//    MessageHeap_alignSize(9) == 16

static size_t roundUpSize(size_t aSize)
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

void initializeShortTermMemory(size_t aAllocate)
{
   // Round up the size to be on an eight byte boundary for 32 bit systems
   // or a sixteen byte bounday for 64 bit systems. In other words, for a 32
   // bit system, if you want to allocate one byte, this will allocate eight
   // bytes. This keeps everything on byte boundaries so as to be consistent
   // with calls to malloc.
   size_t tSize = roundUpSize(aAllocate);

   // If memory for the message heap has already been allocated then free it.
   // This provides a mechanism to override previous initializations. The
   // message heap is initialized to a default size at program initialization,
   // See below at the end of this file.
   if (rHeapBeginPtr != 0)
   {
      free(rHeapBeginPtr);
   }

   // Allocate system memory for the message heap. NOTE: the malloc call
   // returns a  pointer that is aligned on an 8 byte boundary for 32 bit
   // systems or returns a pointer that is aligned a 16 byte boundary for 64
   // bit systems.
   rHeapBeginPtr = (char*)malloc(tSize);

   // Set the heap end pointer. This should point to one byte after the
   // allocated region.
   rHeapEndPtr = rHeapBeginPtr + tSize;

   // Set the working pointer to point to the start of the message heap.
   rWorkingPtr = rHeapBeginPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This allocates a sub segment of the message memory heap.

void* allocateFromShortTermMemory(size_t aSize)
{
   //--------------------------------------------------------------------------
   // Calculate the size to allocate.

   // Round up the size to be on an eight byte boundary for 32 bit systems
   // or a sixteen byte bounday for 64 bit systems. In other words, for a 32
   // bit system, if you want to allocate one byte, this will allocate eight
   // bytes. This keeps everything on byte boundaries so as to be consistent
   // with calls to malloc.
   size_t tSize = roundUpSize(aSize);

   // Increase the allocated size to include the header. This means that the
   // allocated size will include size for the requested number of bytes for
   // the message and for the heap header and that it will be on the correct
   // byte boundary.
   tSize += HeaderAllocate;

   //--------------------------------------------------------------------------
   // Calculate the pointer for the allocated segment.

   // To allocate from the heap, store a copy of the current working pointer.
   // This is the address on the message heap that will be allocated.
   char* tAllocatePtr = rWorkingPtr;

   // Advance the current working pointer by the size to allocate.
   rWorkingPtr += tSize;

   // If this advancement goes past the end of the memory allocated for the
   // heap, then there is a rollover. This should be infrequent.
   if (rWorkingPtr >= rHeapEndPtr)
   {
      // Set the current working pointer back to the start of the heap
      rWorkingPtr = rHeapBeginPtr;
      // Allocate to the current working pointer.
      tAllocatePtr = rHeapBeginPtr;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Pointer and header management

   // Set a header pointer to point to the beginning of the allocated region.
   Header* tHeaderPtr = (Header*)tAllocatePtr;

   // Set a body pointer to point after the header pointer.
   char* tBodyPtr   = tAllocatePtr + HeaderAllocate;

   // Set the header sync word.
   tHeaderPtr->mSyncWord = HeaderSyncWord;

   // Set the sequence number for the allocated message.
   tHeaderPtr->mSequenceNumber = rSequenceNumber++;

   // Set the allocated region header previous pointer to point to the header
   // of the previous message that was allocated.
   tHeaderPtr->mPreviousMessageHeader = rPreviousMessageHeader;

   // Store the pointer to the allocated message for the next allocation.
   rPreviousMessageHeader = tHeaderPtr;

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

bool checkSTM(void* aMessage)
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
   if ((tHeaderCharPtr < rHeapBeginPtr) || (tHeaderCharPtr >= rHeapEndPtr))
   {
      printf("checkShortTermMemory1\n");
      return false;
   }

   // Check the sync word of the header
   if (tHeaderPtr->mSyncWord != HeaderSyncWord)
   {
      printf("checkShortTermMemory2\n");
      return false;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Check the validty of the message with the previous message.

   // If this is the first message, then there is no previous message.
   if (tHeaderPtr->mSequenceNumber == 0)
   {
      // Pass
      return true;
   }

   // Extract pointers to the previous message header. 
   Header*  tPreviousHeaderPtr     = tHeaderPtr->mPreviousMessageHeader;
   char*    tPreviousHeaderCharPtr = (char*)tPreviousHeaderPtr;

   // Check the range of the previous header pointer.
   if ((tPreviousHeaderCharPtr < rHeapBeginPtr) || (tPreviousHeaderCharPtr >= rHeapEndPtr))
   {
      return false;
   }

   // Check the sync word of the previous header
   if (tPreviousHeaderPtr->mSyncWord != HeaderSyncWord)
   {
      return false;
   }

   // Check the sequence number of the previous message.
   if (tHeaderPtr->mSequenceNumber != tPreviousHeaderPtr->mSequenceNumber + 1)
   {
      return false;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // All validity checks have passed.

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a global variable that initializes the short term memory heap to
// a default size. It is executed at program initialization, before main.
// Further calls to initializeShortTermMemory will override the default size.

class ShortTermMemoryInitClass
{
public:

   ShortTermMemoryInitClass()
   {
      initializeShortTermMemory(16*1024);
   }
};

ShortTermMemoryInitClass rShortTermMemoryInitInstance;

}//namespace




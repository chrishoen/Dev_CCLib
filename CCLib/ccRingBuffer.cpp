/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"
#include <limits.h>

#include "ccRingBuffer.h"

using namespace std;

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// No constructor. 

void RingBufferState::initialize(int aNumElements, size_t aElementSize, int aReadGap)
{
   mNumElements = aNumElements;
   mElementSize = aElementSize;
   mReadGap = aReadGap;
   mNextWriteIndex.store(0,std::memory_order_relaxed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor. 

HeapRingBuffer::HeapRingBuffer()
{
   mElementArrayMemory = 0;
}

HeapRingBuffer::~HeapRingBuffer()
{
   finalize();
}

void HeapRingBuffer::initialize(int aNumElements, size_t aElementSize, int aReadGap)
{
   BaseClass::initialize(aNumElements, aElementSize, aReadGap);
   finalize();
   mElementArrayMemory = malloc(aNumElements * aElementSize);
}

void HeapRingBuffer::finalize()
{
   if (mElementArrayMemory)
   {
      free(mElementArrayMemory);
      mElementArrayMemory = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

RingBufferWriter::RingBufferWriter()
{
   mRB = 0;
   resetVars();
}

void RingBufferWriter::initialize(RingBufferState* aRingBufferState, void* aElementArrayMemory)
{
   resetVars();
   mRB = aRingBufferState;
   mElementArrayMemory = aElementArrayMemory;
}

void RingBufferWriter::resetVars()
{
   resetTest();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element, based on an index modulo the number
// of elements.

void* RingBufferWriter::elementAt(long long aIndex)
{
   aIndex %= mRB->mNumElements;
   return (void*)((char*)mElementArrayMemory + mRB->mElementSize * aIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an element to the array at the write index, copying it from
// the function argument. Increment the write index state variable so 
// that it contains the index of the next element to write to.

void RingBufferWriter::doWrite(void* aElement)
{
   // Get the index of the next element to write to.
   long long tWriteIndex = mRB->mNextWriteIndex.load(std::memory_order_relaxed);

   // Get the address of the next element to write to.
   void* tPtr = elementAt(tWriteIndex);

   // Copy the element into the array.
   memcpy(tPtr, aElement, mRB->mElementSize);

   // Internal test function that can be used by inheritors to perform
   // ring buffer performance tests.
   doTest(tWriteIndex, tPtr);

   // Increment the write index to the next element to write to.
   mRB->mNextWriteIndex.fetch_add(1, std::memory_order_relaxed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to the next element to write to, which is the element
// at the write index. Do not increment the  write index state. The caller
// can then execute its own write operation.

void* RingBufferWriter::startWrite()
{
   // Get the index of the next element to write to.
   long long tWriteIndex = mRB->mNextWriteIndex.load(std::memory_order_relaxed);

   // Get the address of the next element to write to.
   void* tPtr = elementAt(tWriteIndex);

   // Return the address of the next element to write to.
   return tPtr;
}

// Increment the write index state variable after a started write is
// finished so that it contains the index of the last element written to.
void RingBufferWriter::finishWrite()
{
   // Get the index of the next element to write to.
   long long tWriteIndex = mRB->mNextWriteIndex.load(std::memory_order_relaxed);

   // Get the address of the next element to write to.
   void* tPtr = elementAt(tWriteIndex);

   // Internal test function that can be used by inheritors to perform
   // ring buffer consistency tests. This is called with the index of
   // the write and the element that was written.
   doTest(tWriteIndex, tPtr);

   // Increment the write index to the next element to write to.
   mRB->mNextWriteIndex.fetch_add(1, std::memory_order_relaxed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

RingBufferReader::RingBufferReader()
{
   mRB = 0;
   resetVars();
}

void RingBufferReader::initialize(RingBufferState* aRingBufferState, void* aElementArrayMemory)
{
   resetVars();
   mRB = aRingBufferState;
   mElementArrayMemory = aElementArrayMemory;
}

void RingBufferReader::resetVars()
{
   mFirstFlag = true;
   mLastReadIndex = 0;
   mNotReadyCount1 = 0;
   mNotReadyCount2 = 0;
   mNotReadyCount3 = 0;
   mErrorCount = 0;
   mDropCount = 0;
   mOverwriteCount = 0;
   resetTest();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element, based on an index modulo the number
// of elements.

void* RingBufferReader::elementAt(long long aIndex)
{
   aIndex %= mRB->mNumElements;
   return (void*)((char*)mElementArrayMemory + mRB->mElementSize * aIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return the number of elements that are available to be read.

int RingBufferReader::available()
{
   long long tMaxAvailable = mRB->mNextWriteIndex.load(std::memory_order_relaxed) - 1 - mRB->mReadGap;
   return  tMaxAvailable - mLastReadIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read an element from the array, copying it to the function argument.
// Return true if successful.

bool RingBufferReader::doRead(void* aElement)
{
   long long tMinAvailable = 0;
   long long tMaxAvailable = 0;
   long long tNextReadIndex = 0;

   // Get the initial write index. This might change asynchronously during
   // the read. The write index is the index of the next element to write to.
   long long tNextWriteIndex = mRB->mNextWriteIndex.load(std::memory_order_relaxed);

   // Test for invalid data. This means that the writer has not yet
   // written any elements or is resetting the buffer.
   if (tNextWriteIndex == 0)
   {
      // The writer is not ready.
      mFirstFlag = true;
      mNotReadyCount1++;
      return false;
   }

   // Calculate limits.
   tMinAvailable = tNextWriteIndex - (mRB->mNumElements - 1);
   tMaxAvailable = tNextWriteIndex - 1 - mRB->mReadGap;

   // If the max available is negative no elements are available, so exit.
   if (tMaxAvailable < 0)
   {
      // Set the read for the behind the maximum available element.
      mLastReadIndex = tMaxAvailable - 1;
      mNotReadyCount2++;
      return false;
   }

   // Here's an example of a buffer with NumElements = 8 and ReadGap = 3.
   // 
   // The buffer contains written elements on the closed interval [123 .. 130].
   // Elements can be read on [124 .. 127]. While the reader is reading, the
   // writer could possibly write to 131 == 123.
   // 
   // 122 2
   // 123 3  zzzz
   // 124 4  xxxx  WriteIndex - (NumElements - 1) oldest available
   // 125 5  xxxx
   // 126 6  xxxx
   // 127 7  xxxx  WriteIndex - ReadGap + 1       youngest available
   // 128 0  yyyy
   // 129 1  yyyy
   // 130 2  yyyy  WriteIndex - 1
   // 131 3  zzzz  WriteIndex

   // Test for the first read.
   if (mFirstFlag)
   {
      mFirstFlag = false;
      // Set the read for the behind the maximum available element.
      mLastReadIndex = tMaxAvailable - 1;
   }

   // If the maximum available element has already been read then
   // no elements are available, so exit.
   if (mLastReadIndex == tMaxAvailable)
   {
      // There's nothing to read.
      mNotReadyCount3++;
      return false;
   }

   // If the next element to read is behind the minimum available, 
   // then read from the minimum available.
   if (mLastReadIndex < tMinAvailable)
   {
      tNextReadIndex = tMinAvailable;
   }
   else
   {
      tNextReadIndex = mLastReadIndex + 1;
   }

   // This should never happen.
   if (tNextReadIndex < 0)
   {
      mErrorCount++;
      return false;
   }

   // Get the address of the next element to read from.
   void* tPtr = elementAt(tNextReadIndex);

   // Copy that element into the argument element.
   memcpy(aElement, tPtr, mRB->mElementSize);

   // At this point ReadIndex is the index of the last element that was
   // read from.

   // If, during the read, the ring buffer was written to asynchronously
   // by the writer, then test if the read was possibly or actually
   // overwritten. If it was then drop the read.
   //   
   // Here's an example of this.
   // 
   // ReadIndex is the index of the last element that was read.
   // Final WriteIndex is the index of the next element to write to,
   // taken after the read occurred.

   // 122 2
   // 123 3  ReadIndex the read occurred here
   // 124 4  OK
   // 125 5  OK
   // 126 6  OK
   // 127 7  OK
   // 128 0  OK 
   // 129 1  OK
   // 130 2  OK
   // 131 3  Final WriteIndex could possibly overwrite the read
   // 132 4  Final WriteIndex has overwritten the read
   // 133 5  Final WriteIndex has overwritten the read

   // Get the final write index. If a write occurred during the read then
   // this will be different than the write index at the beginning of the
   // read.
   tNextWriteIndex = mRB->mNextWriteIndex.load(std::memory_order_relaxed);
   tMinAvailable = tNextWriteIndex - (mRB->mNumElements - 1);
   tMaxAvailable = tNextWriteIndex - 1 - mRB->mReadGap;

   // If the read was or might have been overwritten then drop it.
   if (tNextReadIndex < tMinAvailable)
   {
      mOverwriteCount++;
      return false;
   }

   // Internal test function that can be used by inheritors to perform
   // ring buffer consistency tests. This is called with the index of
   // the read and the element that was read.
   doTest(tNextReadIndex, aElement);

   // Increment the drop count. If none were dropped then the read index
   // should be the index of the last succesful read plus one.
   if (mLastReadIndex > 0)
   {
      mDropCount += (int)(tNextReadIndex - (mLastReadIndex + 1));
   }

   // Store the index for the last successful read.
   mLastReadIndex = tNextReadIndex;

   // Success. 
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
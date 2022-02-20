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
// Constants.

static const long long cInvalidValue = -9223372036854775807;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor. 

RingBufferState::RingBufferState()
{
   mNumElements = 0;
   mElementSize = 0;
   mReadGap = 0;
   mWriteIndex = cInvalidValue;
}

void RingBufferState::initialize(int aNumElements, size_t aElementSize, int aReadGap)
{
   mNumElements = aNumElements;
   mElementSize = aElementSize;
   mReadGap = aReadGap;
   mWriteIndex.store(cInvalidValue,std::memory_order_relaxed);
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
// Return a pointer to an element, based on an index modulo
// the number of elements.

void* RingBufferWriter::elementAt(long long aIndex)
{
   aIndex %= mRB->mNumElements;
   return (void*)((char*)mElementArrayMemory + mRB->mElementSize * aIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an element to the array at the next element to write to, copying
// it from the function argument. Update the write index state variable
// so that it contains the index of the last element written to.

void RingBufferWriter::doWrite(void* aElement)
{
   // Index of the last element that was written to.
   long long tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // Advance the index to the next element to write to.
   if (tWriteIndex < 0)
   {
      tWriteIndex = 0;
   }
   else
   {
      tWriteIndex++;
   }

   // Get the address of the next element to write to.
   void* tPtr = elementAt(tWriteIndex);

   // Copy the element into the array.
   memcpy(tPtr, aElement, mRB->mElementSize);

   // Internal test function that can be used by inheritors to perform
   // ring buffer performance tests.
   doTest(tWriteIndex, tPtr);

   // Update the global state. This should be the only place that this
   // happens.
   mRB->mWriteIndex.store(tWriteIndex, std::memory_order_relaxed);
}

// Return a pointer to the next element to write to. Do not update the
// write index state variable.
void* RingBufferWriter::startWrite()
{
   // Index of the last element that was written to.
   long long tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // Advance the index to the next element to write to.
   if (tWriteIndex < 0)
   {
      tWriteIndex = 0;
   }
   else
   {
      tWriteIndex++;
   }

   // Get the address of the next element to write to.
   void* tPtr = elementAt(tWriteIndex);

   // Return the address of the next element to write to.
   return tPtr;
}

// Update the write index state variable after a started write is finished
// so that it contains the index of the last element written to.
void RingBufferWriter::finishWrite()
{
   // Index of the last element that was written to.
   long long tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // Advance the index to the next element to write to.
   if (tWriteIndex < 0)
   {
      tWriteIndex = 0;
   }
   else
   {
      tWriteIndex++;
   }

   // Get the address of the next element to write to.
   void* tPtr = elementAt(tWriteIndex);

   // Internal test function that can be used by inheritors to perform
   // ring buffer performance tests.
   doTest(tWriteIndex, tPtr);

   // Update the global state. This should be the only place that this
   // happens.
   mRB->mWriteIndex.store(tWriteIndex, std::memory_order_relaxed);
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
   mNotReadyCount1 = 0;
   mNotReadyCount2 = 0;
   mNotReadyCount3 = 0;
   mDropCount1 = 0;
   mDropCount2 = 0;
   mRetryCount = 0;
   mReadIndex = cInvalidValue;
   mLastReadIndex = cInvalidValue;
   mTail = cInvalidValue;
   mReady = cInvalidValue;
   mHead = cInvalidValue;
   resetTest();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element, based on an index modulo
// the number of elements.

void* RingBufferReader::elementAt(long long aIndex)
{
   aIndex %= mRB->mNumElements;
   return (void*)((char*)mElementArrayMemory + mRB->mElementSize * aIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read an element from the array, copying it to the function argument.
// Return true if successful.

bool RingBufferReader::doRead(void* aElement)
{
   // Get the initial write index. This might change asynchronously during
   // the read. The write index is the index of the last element that was
   // written to.
   long long tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // Store the last successful read index.
   mLastReadIndex = mReadIndex;

   // Test for invalid data. This means that the writer has not yet
   // written any elements or is resetting the buffer.
   if (tWriteIndex == cInvalidValue)
   {
      // The writer is not ready.
      mFirstFlag = true;
      mNotReadyCount1++;
      return false;
   }

   // Here's an example of a buffer with NumElements = 8 and ReadGap = 3.
   // 
   // The buffer contains written elements on the closed interval [123 .. 130].
   // Elements can be read on [124 .. 127]. While the reader is reading, the
   // writer could possible write to 131 == 123.
   // 
   // 122 2
   // 123 3  zzzz
   // 124 4  xxxx  Tail  = WriteIndex - (NumElements - 2)
   // 125 5  xxxx
   // 126 6  xxxx
   // 127 7  xxxx  Ready = WriteIndex - ReadGap
   // 128 0  yyyy
   // 129 1  yyyy
   // 130 2  yyyy  Head  = WriteIndex
   // 131 3  zzzz

   // Test for the first read.
   if (mFirstFlag)
   {
      mFirstFlag = false;
      // Calulate the state variables.
      mTail = tWriteIndex - (mRB->mNumElements - 2);
      mReady = tWriteIndex - mRB->mReadGap;
      mHead = tWriteIndex;
      mLastReadIndex = cInvalidValue;
      mReadIndex = mReady;
   }
   else
   {
      // Calulate the state variables.
      mTail = tWriteIndex - (mRB->mNumElements - 2);
      mReady = tWriteIndex - mRB->mReadGap;
      mHead = tWriteIndex;

      // Ready is the youngest element that can be read. If it has already
      // been read then no elements are available to be read, so exit.
      if (mLastReadIndex == mReady)
      {
         // There's nothing to read.
         //mReadIndex = mReady; //????
         mNotReadyCount2++;
         return false;
      }

      // If the last element read is behind the tail then read from
      // the tail.
      if (mLastReadIndex < mTail)
      {
         mReadIndex = mTail;
      }
      // Else read the next element.
      else
      {
         mReadIndex = mLastReadIndex + 1;
      }
   }

   // Test for negative ReadIndex. This can happen when the buffer
   // isn't full yet.
   if (mReadIndex < 0)
   {
      // There's nothing to read.
      mNotReadyCount3++;
      return false;
   }

   // At this point ReadIndex is the index of the next element to read from.
   // Get the address of the next element to read from.
   void* tPtr = elementAt(mReadIndex);

   // Copy that element into the argument element.
   memcpy(aElement, tPtr, mRB->mElementSize);

   // If, during the read, the ring buffer was written to asynchronously
   // by the writer, so the read was overwritten, then drop the read.
   //   
   // Here's an example of this.
   // 
   // ReadIndex is the index of the last element that was read.
   // WriteIndex is the index of the last element that was written.

   // 122 2
   // 123 3  ReadIndex
   // 124 4  OK
   // 125 5  OK
   // 126 6  OK
   // 127 7  OK
   // 128 0  OK 
   // 129 1  OK
   // 130 2  Final WriteIndex is OK                     Write 
   // 131 3  Final WriteIndex has overwritten the read  Write - Read = 8
   // 132 4  Final WriteIndex has overwritten the read  Write - Read = 9

   // Get the final write index. 
   tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);
   
   // If the read was or might have been overwritten then drop it.
// if (tWriteIndex - mReadIndex >= mRB->mNumElements - 1) original
   if (tWriteIndex > mReadIndex + (mRB->mNumElements - 1))
      {
      // Increment the drop count. If none were dropped then the
      // read index should be the previous read index plus one.
      if (mLastReadIndex > 0)
      {
         mDropCount1 += (int)(mReadIndex - (mLastReadIndex + 1));
      }
      return false;
   }

   // Internal test function that can be used by inheritors to perform
   // ring buffer performance tests.
   doTest(mReadIndex, aElement);

   // Increment the drop count. If none were dropped then the
   // read index should be the previous read index plus one.
   if (mLastReadIndex > 0)
   {
      mDropCount2 += (int)(mReadIndex - (mLastReadIndex + 1));
   }

   // Success. 
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
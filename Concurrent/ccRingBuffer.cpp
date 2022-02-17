/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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

void BaseRingBuffer::reset()
{
   mNumElements = 0;
   mElementSize = 0;
   mElementArray = 0;
   mReadyGuard = 0;
   mWriteIndex = LLONG_MIN;
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
}

void RingBufferWriter::initialize(BaseRingBuffer* aRingBuffer)
{
   mRB = aRingBuffer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element, based on an index modulo
// the number of elements.

void* RingBufferWriter::elementAt(long long aIndex)
{
   aIndex %= mRB->mNumElements;
   return (void*)((char*)mRB->mElementArray + mRB->mElementSize * aIndex);
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
   tWriteIndex++;

   // Get the address of the next element to write to.
   void* tPtr = elementAt(tWriteIndex);

   // Copy the element into the array.
   memcpy(tPtr, aElement, mRB->mElementSize);

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
   tWriteIndex++;

   // Return the address of the next element to write to.
   return elementAt(tWriteIndex);
}

// Update the write index state variable after a started write is finished
// so that it contains the index of the last element written to.
void RingBufferWriter::finishWrite()
{
   // Increment the global state. This should be the only other place that this
   // happens.
   mRB->mWriteIndex.fetch_add(1, std::memory_order_relaxed);
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
   mTempElement = 0;
   mTestFunction = 0;
   resetVars();
}

void RingBufferReader::resetVars()
{
   mFirstFlag = false;
   mDropCount = 0;
   mNotReadyCount = 0;
   mRetryCount = 0;
   mReadIndex = LLONG_MIN;
   mLastReadIndex = LLONG_MIN;
   mTail = LLONG_MIN;
   mReady = LLONG_MIN;
   mHead = LLONG_MIN;
}

void RingBufferReader::initialize(BaseRingBuffer* aRingBuffer)
{
   resetVars();
   mRB = aRingBuffer;
   mTempElement = (void*)new char[mRB->mElementSize];
}

RingBufferReader::~RingBufferReader()
{
   if (mTempElement) delete mTempElement;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element, based on an index modulo
// the number of elements.

void* RingBufferReader::elementAt(long long aIndex)
{
   aIndex %= mRB->mNumElements;
   return (void*)((char*)mRB->mElementArray + mRB->mElementSize * aIndex);
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

restart:

   // Test for invalid data. This means that the writer has not yet
   // written any elements or is resetting the buffer.
   if (tWriteIndex == LLONG_MIN)
   {
      // The writer is not ready.
      mFirstFlag = true;
      mNotReadyCount++;
      return false;
   }

   // Here's an example of a buffer with NumElements = 8 and ReadyGuard = 3.
   // All elements have been written to. The buffer is full.
   // 
   // The buffer contains written elements on the closed interval [123 .. 130].
   // Elements can be read on [123 .. 127]
   // 122 2
   // 123 3  xxxx  Tail = WriteIndex - (NumElements - 1)
   // 124 4  xxxx
   // 125 5  xxxx
   // 126 6  xxxx
   // 127 7  xxxx  Ready = WriteIndex - ReadyGuard
   // 128 0  yyyy
   // 129 1  yyyy
   // 130 2  yyyy  Head  = WriteIndex
   // 131 3

   // Test for the first read.
   if (mFirstFlag)
   {
      mFirstFlag = false;
      // Calulate the state variables.
      mTail = tWriteIndex - (mRB->mNumElements - 1);
      mReady = tWriteIndex - mRB->mReadyGuard;
      mHead = tWriteIndex;
      mLastReadIndex = LLONG_MIN;
      mReadIndex = mReady;
   }
   else
   {
      // Calulate the state variables.
      mTail = tWriteIndex - (mRB->mNumElements - 1);
      mReady = tWriteIndex - mRB->mReadyGuard;
      mHead = tWriteIndex;

      // Ready is the youngest element that can be read. If it has already
      // been read then no elements are available to be read, so exit.
      if (mLastReadIndex == mReady)
      {
         // There's nothing to read.
         mReadIndex = mReady; //????
         mNotReadyCount++;
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
      mNotReadyCount++;
      return false;
   }

   // At this point ReadIndex is the index of the next element to read from.
   // Get the address of the next element to read from.
   void* tPtr = elementAt(mReadIndex);

   // Copy that element into the temp element.
   memcpy(mTempElement, tPtr, mRB->mElementSize);

   // If, during the read, the ring buffer was written to asynchronously
   // by the writer and the read was overwritten, then retry the read.
   //  
   // Here's an example of this.
   // 
   // ReadIndex is the index of the last element that was read.
   // WriteIndex is the index of the last element that was written.

   // 122 2
   // 123 3   ReadIndex
   // 124 4   Initial WriteIndex
   // 125 5  
   // 126 6  
   // 127 7  
   // 128 0  
   // 129 1  
   // 130 2  Final WriteIndex is OK                     Write - Read = 7
   // 131 3  Final WriteIndex has overwritten the read  Write - Read = 8
   // 132 4  Final WriteIndex has overwritten the read  Write - Read = 9

   // Get the final write index. 
   tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // If the read was overwritten then retry it. The final write index
   // becomes the next initial write index at the top of the loop.
   if (tWriteIndex - mReadIndex >= mRB->mNumElements)
   {
      mRetryCount++;
      goto restart;
   }

   // The read of the temp element was successful so copy the temp
   // element into the argument element.
   memcpy(aElement, mTempElement, mRB->mElementSize);

   // Increment the drop count. If none were dropped then the
   // read index should be the previous read index plus one.
   mDropCount += (int)(mReadIndex - mLastReadIndex + 1);

   // Internal test function that can be used by inheritors to perform
   // ring buffer performance tests.
   if(mTestFunction) mTestFunction(mReadIndex, mTempElement);

   // Success. 
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
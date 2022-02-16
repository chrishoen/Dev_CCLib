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
   mWriteIndex = -1;
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
// Write an element to the array, updating the write index state variable.

void RingBufferWriter::doWriteElement(void* aElement)
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
   mRB->mWriteIndex.store(tWriteIndex,std::memory_order_relaxed);
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
   mReadIndex = 0;
   mTempElement = 0;
   mDropCount = 0;
   mNotReadyCount = 0;
   mRetryCount = 0;
}

RingBufferReader::~RingBufferReader()
{
   if (mTempElement) delete mTempElement;
}

void RingBufferReader::initialize(BaseRingBuffer* aRingBuffer)
{
   mRB = aRingBuffer;
   mTempElement = (void*)new char[mRB->mElementSize];
   mDropCount = 0;
   mNotReadyCount = 0;
   mRetryCount = 0;
   mReadIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);
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
// Read an element from the array, updating state variables. Return
// true if successful. 

bool RingBufferReader::doReadElement(void* aElement)
{
   // Get the initial write index. This might change asynchronously during
   // the read. The write index is the index of the last element that was
   // written to.
   long long tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // Store the initial read index. This will be used to calculate
   // the drop count.
   long long tLastReadIndex = mReadIndex;

restart:

   // Test for invalid data. This means that the writer has not yet
   // written any elements or is resetting the buffer.
   if (tWriteIndex < 0)
   {
      // The writer is not ready.
      mNotReadyCount++;
      return false;
   }

   // Test for the first read being uninitialized.
   if (mReadIndex < 0)
   {
      // This might still be less than zero.
      mReadIndex = tWriteIndex - 1;
   }
    
   // Calculate the head and tail indices of the buffer memory region.
   // The indices that contain valid data are in the closed interval
   // [Tail .. Head] where 0 <= Head - Tail <= NumElements - 1
   // 
   // Here's an example of a buffer with NumElements = 4 that is still
   // in the initialization stage. It only has three elements written to it,
   // so it is not full.
   // 
   //   0  0 xxxx  Tail
   //   1  1 xxxx
   //   2  2 xxxx  Head  so Head - Tail = 2, which is less than NumElements - 1
   //   3  3
   //   4  0
   // 
   // Here's an example of a buffer with NumElements = 4 that is past the
   // initialization stage. It is full.
   // 122 2
   // 123 3  xxxx  Tail
   // 124 0  xxxx
   // 125 1  xxxx
   // 126 2  xxxx  Head  so Head - Tail = 3 = NumElements - 1
   // 127 3

   long long tTail = 0;
   long long tHead = 0;

   // If in the initialization stage and the buffer is not full.
   if (tWriteIndex < mRB->mNumElements - 1)
   {
      tTail = 0;
      tHead = tWriteIndex;
   }
   // Else the buffer is full.
   else
   {
      // Tail + NumElements - 1 = Head
      tTail = tWriteIndex - (mRB->mNumElements - 1);
      tHead = tWriteIndex;
   }

   // Calculate the forward distance from the tail to the head,
   // Tail + Dist = Head
   long long tDist = tHead - tTail;

   // Test for no elements available for read.
   if (tDist == 0)
   {
      // There's nothing to read. The reader has already caught up with
      // the writer. 
      mNotReadyCount++;
      return false; 
   }

   // Test if the distance puts the read outside of the buffer range.
   // Here's an example of this, where ReadIndex is behind Tail
   // and the number of dropped elements is Tail - ReadIndex + 1.
   // 
   // 120          ReadIndex      is less than Tail
   // 121  dropped
   // 122  dropped
   // 123  xxxx    Tail
   // 124  xxxx
   // 125  xxxx
   // 126  xxxx    Head
   // 127
   else if (tDist >= mRB->mNumElements)
   {
      // Set the read index to the last element included in the buffer range.
      mReadIndex = tTail;
   }
   else
   {
      // Advance to the next element to read from.
      mReadIndex++;
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
   // 
   // 122 
   // 123  3  ReadIndex
   // 124  0  Initial WriteIndex
   // 125  1  
   // 126  2  Final WriteIndex     is OK
   // 127  3  Final WriteIndex     has overwritten the read
   // 128  0  

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
   mDropCount += (int)(mReadIndex - tLastReadIndex + 1);

   // Success. 
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
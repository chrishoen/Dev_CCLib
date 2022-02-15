/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "ccCriticalSection.h"
#include "cc_functions.h"
#include "ccDefs.h"
#include "ccMemoryPtr.h"
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
   mElements = 0;
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
// Return a pointer to an element, based on an index.

void* RingBufferWriter::elementAt(long long aIndex)
{
   return (void*)((char*)mRB->mElements + mRB->mElementSize * aIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy to the array element after the current major index, modulo the
// minor modulus. Increment the major index, modulo the major modulus.

void RingBufferWriter::doWriteElement(void* aElement)
{
   // Index of the last element that was written to.
   long long tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // Test for the first write.
   if (tWriteIndex == -1)
   {
      // This is the first element written to. 
      tWriteIndex = 0;
   }
   else
   {
      // Advance the index to the next element to write to.
      ++tWriteIndex;
   }

   // Memory index of the next element to write to.
   long long tMemIndex = tWriteIndex % mRB->mNumElements;

   // Address of the next element to write to.
   void* tPtr = elementAt(tMemIndex);

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
// Return a pointer to an element, based on an index.

void* RingBufferReader::elementAt(long long aIndex)
{
   return (void*)((char*)mRB->mElements + (size_t)mRB->mElementSize * aIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy to the array element after the current major index, modulo the
// minor modulus. Increment the major index, modulo the major modulus.
//

bool RingBufferReader::doReadElement(void* aElement)
{
   // Get the initial write index. This might change asynchronously
   // during the read.
   long long tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

restart:

   // Test for invalid data.
   if (tWriteIndex < 0)
   {
      // The writer is not ready.
      mNotReadyCount++;
      return false;
   }

   // Calculate the end points of the buffer memory region. The memory
   // region that contains valid data is in the closed interval
   // [Tail .. Head]
   // 
   // Here's an example of a buffer with NumElements = 4 at the beginning,
   // with only three elements, so it is not full.
   // 
   // 0    xxxx  Tail
   // 1    xxxx
   // 2    xxxx  Head  so Head - Tail = 2, which is less than NumElements - 1
   // 3
   // 
   // Here's an example of a buffer with NumElements = 4 that is full.
   // 122
   // 123  xxxx  Tail
   // 124  xxxx
   // 125  xxxx
   // 126  xxxx  Head  so Head - Tail = 3 = NumElements - 1
   // 127

   long long tTail = 0;
   long long tHead = 0;
   if (tWriteIndex < mRB->mNumElements - 1)
   {
      tTail = 0;
      tHead = tWriteIndex;
   }
   else
   {
      // Tail + NumElements - 1 = Head
      tTail = tWriteIndex - (mRB->mNumElements - 1);
      tHead = tWriteIndex;
   }

   // Forward distance from the tail to the head,
   // Tail + Dist = Head
   long long tDist = tHead - tTail;

   // Test for no elements available for read.
   if (tDist == 0)
   {
      // There's nothing to read. The reader is caught up with the writer. 
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
      // Increment the drop count.
      mDropCount += (int)(tTail - mReadIndex + 1);

      // Set the read index to the last element included in the buffer range.
      mReadIndex = tTail;
   }
   else
   {
      // Advance to the next element to read from.
      mReadIndex++;
   }

   // Memory index of the next element to read from.
   long long tMemIndex = mReadIndex % mRB->mNumElements;

   // Address of the next element to read from.
   void* tPtr = elementAt(tMemIndex);

   // Copy the array element into the temp element.
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
   // 126  2  Final WriteIndex is OK
   // 127  3  Final WriteIndex has overwritten the read
   // 128  0  

   // Get the final write index. 
   tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // If the read was overwritten then retry it.
   if (tWriteIndex - mReadIndex >= mRB->mNumElements)
   {
      mRetryCount++;
      goto restart;
   }

   // The read of the temp element was successful so copy the temp
   // element into the argument element.
   memcpy(aElement, mTempElement, mRB->mElementSize);
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
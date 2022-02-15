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

void* RingBufferWriter::elementAt(int aIndex)
{
   return (void*)((char*)mRB->mElements + (size_t)mRB->mElementSize * aIndex);
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
   int tMemIndex = tWriteIndex % mRB->mNumElements;

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
   mNoReadCount = 0;
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
   mNoReadCount = 0;
   mRetryCount = 0;
   mReadIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element, based on an index.

void* RingBufferReader::elementAt(int aIndex)
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
restart:
   // Store a copy of the write index because it might be changed
   // asynchronously by the writer.
   long long tWriteIndex = mRB->mWriteIndex.load(std::memory_order_relaxed);

   // Calculate the end points of the buffer memory region. The memory
   // region that contains valid data is in the closed interval
   // [Tail .. Head]
   long long tTail = 0;
   long long tHead = 0;
   if (tWriteIndex < mRB->mNumElements)
   {
      tTail = 0;
      tHead = tWriteIndex;
   }
   else
   {
      // Tail + MinorMod - 1 = Head
      tTail = tWriteIndex - ((long long)mRB->mNumElements - 1);
      tHead = tWriteIndex;
   }

   // Forward distance from the tail to the head,
   // Tail + Dist = Head
   long long tDist = tHead - tTail;

   // Test for no elements available for read.
   if (tDist == 0)
   {
      // There's nothing to read. The reader is caught up with the writer. 
      mNoReadCount++;
      return false; 
   }

   // Test if the distance puts the read outside of the buffer range.
   else if (tDist >= mRB->mNumElements)
   {
      // Set the read index to the element at the end of the buffer range.
      mReadIndex = tTail;
   }
   else
   {
      // Advance to the next element to read from.
      mReadIndex++;
   }

   // Memory index of the next element to read from.
   int tMemIndex = mReadIndex % mRB->mNumElements;

   // Address of the next element to read from.
   void* tPtr = elementAt(tMemIndex);

   // Copy the array element into the temp element.
   memcpy(mTempElement, tPtr, mRB->mElementSize);

   // If the write index changed during the read then the ring buffer 
   // was written to asynchronously by the writer so retry the read.
   if (tWriteIndex != mRB->mWriteIndex.load(std::memory_order_relaxed))
   {
      mRetryCount++;
      goto restart;
   }

   // Copy the temp element into the argument element.
   memcpy(aElement, mTempElement, mRB->mElementSize);
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
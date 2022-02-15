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
   mMajorMod = 0;
   mMinorMod = 0;
   mElementSize = 0;
   mElements = 0;
   mMajorWriteIndex = -1;
   mFullFlag = false;
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
   // Major index of the last element that was written to.
   int tMajorIndex = mRB->mMajorWriteIndex;

   // Test for the first write.
   if (tMajorIndex == -1)
   {
      // This is the first element written to. 
      tMajorIndex = 0;
   }
   else
   {
      // Advance the major index to the next element to write to.
      ++tMajorIndex %= mRB->mMajorMod;
   }

   // Minor index of the next element to write to.
   int tMinorIndex = tMajorIndex % mRB->mMinorMod;

   // Address of the next element to write to.
   void* tPtr = elementAt(tMinorIndex);

   // Copy the element into the array.
   memcpy(tPtr, aElement, mRB->mElementSize);

   // Update the global state. This should be the only place that this
   // happens.
   mRB->mMajorWriteIndex = tMajorIndex;

   // Test for buffer full.
   if (tMajorIndex == mRB->mMinorMod - 1) mRB->mFullFlag = true;
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
   mMajorReadIndex = 0;
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
   mMajorReadIndex = mRB->mMajorWriteIndex;
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
   int tMajorWriteIndex = mRB->mMajorWriteIndex;

   // Calculate the end points of the buffer memory region.
   int tTail = 0;
   int tHead = 0;
   if (!mRB->mFullFlag)
   {
      tTail = 0;
      tHead = tMajorWriteIndex;
   }
   else
   {
      // Tail + MinorMod - 1 = Head
      tTail = (tMajorWriteIndex - (mRB->mMinorMod - 1)) % mRB->mMajorMod;
      tHead = tMajorWriteIndex;
   }

   // Forward distance from the tail to the head,
   // Tail + Dist = Head
   int tDist = tHead - tTail % mRB->mMajorMod;

   // Test for no elements available for read.
   if (tDist == 0)
   {
      // There's nothing to read. The reader is caught up with the writer. 
      mNoReadCount++;
      return false; 
   }

   // Test if the distance puts the read outside of the buffer range.
   else if (tDist >= mRB->mMinorMod)
   {
      // Set the read index to the element at the end of the buffer range.
      mMajorReadIndex = tTail;
   }
   else
   {
      // Advance the major index to the next element to read from.
      ++mMajorReadIndex %= mRB->mMajorMod;
   }

   // Minor index of the next element to read from.
   int tMinorIndex = mMajorReadIndex % mRB->mMinorMod;

   // Address of the next element to read from.
   void* tPtr = elementAt(tMinorIndex);

   // Copy the array element into the temp element.
   memcpy(mTempElement, tPtr, mRB->mElementSize);

   // If the write index changed during the read then the ring buffer 
   // was written to asynchronously by the writer so retry the read.
   if (tMajorWriteIndex != mRB->mMajorWriteIndex)
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
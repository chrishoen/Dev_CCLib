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
   mMajorIndex = -1;
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
   int tMajorIndex = mRB->mMajorIndex;

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
   mRB->mMajorIndex = tMajorIndex;
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
}

RingBufferReader::~RingBufferReader()
{
   if (mTempElement) delete mTempElement;
}

void RingBufferReader::initialize(BaseRingBuffer* aRingBuffer)
{
   mRB = aRingBuffer;
   mTempElement = (void*)new char[mRB->mElementSize];
   mMajorReadIndex = mRB->mMajorIndex;
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

bool RingBufferReader::doReadElement(void* aElement)
{
   return false;
   // Major index of the last element that was written to.
   int tMajorIndex = mRB->mMajorIndex;

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
   mRB->mMajorIndex = tMajorIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
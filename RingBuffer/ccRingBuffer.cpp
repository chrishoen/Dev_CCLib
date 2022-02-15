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
   // All null
   mMajorMod = 0;
   mMinorMod = 0;
   mElementSize = 0;
   mElements = 0;
   mMajorIndex = 0;
   mEmpty = 0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element, based on an index modulo the minor
// modulus.

void* BaseRingBuffer::elementAt(int aIndex)
{
   return (void*)((char*)mElements + (size_t)mElementSize*(aIndex % mMinorMod));
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
   mMajorMod = 0;
   mMinorMod = 0;
   mElementSize = 0;
   mElements = 0;
}


void RingBufferWriter::initialize(BaseRingBuffer* aRingBuffer)
{
   mRB = aRingBuffer;
   mMajorMod = aRingBuffer->mMajorMod;
   mMinorMod = aRingBuffer->mMinorMod;
   mElementSize = aRingBuffer->mElementSize;
   mElements = aRingBuffer->mElements;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element, based on an index.

void* RingBufferWriter::elementAt(int aIndex)
{
   return (void*)((char*)mElements + (size_t)mElementSize * aIndex);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy an element to the element array at the current major index modulo
// the minor modulus. Increment the major index modulo the major modulus.
// Set the empty flag false.

void RingBufferWriter::doWriteElement(void* aElement)
{
   // Index of the next element to write to.
   int tMajorIndex = mRB->mMajorIndex;
   int tMinorIndex = tMajorIndex % mMinorMod;

   // Address of the next element to write to.
   void* tPtr = elementAt(tMinorIndex);

   // Copy the element into the array.
   memcpy(tPtr, aElement, mElementSize);

   // Advance the index so that it points to the next element to write to.
   ++tMajorIndex %= mMajorMod;

   // Update the global state. This should be the only place that this
   // happens.
   mRB->mMajorIndex = tMajorIndex;
   mRB->mEmpty = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
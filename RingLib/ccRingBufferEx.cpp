/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "ccRingBufferEx.h"

namespace CC
{

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
#if 0
   BaseClass::initialize(aNumElements, aElementSize, aReadGap);
   finalize();
   mElementArrayMemory = malloc(aNumElements * aElementSize);
#endif
}

void HeapRingBuffer::finalize()
{
#if 0
   if (mElementArrayMemory)
   {
      free(mElementArrayMemory);
      mElementArrayMemory = 0;
   }
#endif
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
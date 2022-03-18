#pragma once

/*==============================================================================
Ring buffer extensions.
=============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccRingBuffer.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Heap ring buffer. This provides a ring buffer that has memory for an
// element array on the heap. This class is not shared memory safe.

class HeapRingBuffer : public RingBufferState
{
public:
   typedef RingBufferState BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.
    
   // Memory for the ring buffer element array. This is created on the heap at 
   // initialization.
   void* mElementArrayMemory;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HeapRingBuffer();
   ~HeapRingBuffer();
   void initialize(int aNumElements, size_t aElementSize, int aReadGap);
   void finalize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory ring buffer. This provides a ring buffer that has static memory
// for an element array. This class is shared memory safe.

template <class Element, int NumElements, int ReadGap>
class MemoryRingBuffer : public RingBufferState
{
public:
   typedef RingBufferState BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Memory for the ring buffer element array.
   Element mElementArrayMemory[NumElements];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   void initialize()
   {
      BaseClass::initialize(NumElements, sizeof(Element), ReadGap);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


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

template <class Element, int NumElements>
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
   Element* mElementArrayMemory;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor.

   HeapRingBuffer()
   {
      mElementArrayMemory = 0;
   }

   ~HeapRingBuffer()
   {
      finalize();
   }

   void initialize()
   {
#if 0
      finalize();
      BaseClass::initialize();
      mElementArrayMemory = (Element*)malloc(NumElements * sizeof(ElementSize));
#endif
   }

   void finalize()
   {
#if 0
      if (mElementArrayMemory)
      {
         free(mElementArrayMemory);
         mElementArrayMemory = 0;
      }
#endif
   }

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory ring buffer. This provides a ring buffer that has static memory
// for an element array. This class is shared memory safe as long as
// the indivual elements are shared memory safe. 

template <class Element, int NumElements>
class MemoryRingBuffer : public RingBufferState
{
public:
   typedef RingBufferState BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Memory for the ring buffer element array.
   alignas(16) Element mElementArrayMemory[NumElements];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   void initialize()
   {
      BaseClass::initialize();
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


#pragma once

/*==============================================================================

Ring buffer of fixed size opaque objects.

It is single writer multiple reader thread safe.
It is non blocking
It is shared memory safe.

This implements a ring buffer of fixed size objects, where the ring buffer
provides the memory allocation for the objects (memory for the objects is contained
within the ring buffer). The ring buffer is thread safe. It uses mutexes to guard 
against concurrency contentions.

It is thread safe for separate single writer and multiple reader threads.

=============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <atomic>

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base ring buffer. This contains variables that describe a ring buffer
// and its state.

class BaseRingBuffer
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. All of these must be set by an inheriting class.

   // Number of elements in the ring buffer.
   long long mNumElements;

   // Size of each element in the ring buffer.
   size_t mElementSize;

   // The address of the first element in the buffer element array.
   // Inheriting classes supply the element array.
   void* mElements;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. State variables.

   // The index of the last element that was written to. If this is equal to
   // negative one then no writes have occured and the ring buffer is empty.
   // This single variable encapsulates the state of the ring buffer. It
   // can only be written to by a single writer thread and it can be read
   // by multiple reader threads. Buffer memory is addressed via this index
   // modulo the number of elements.
   std::atomic<long long> mWriteIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   virtual void reset();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ring buffer writer class.

class RingBufferWriter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // The ring buffer.
   BaseRingBuffer* mRB;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RingBufferWriter();
   void initialize(BaseRingBuffer* aRingBuffer);

   // Return a pointer to an element, based on an index modulo
   // the number of elements.
   void* elementAt(long long aIndex);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   
   // Write an element to the array, updating the write index state variable.
   void doWriteElement(void* aElement);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ring buffer reader class.

class RingBufferReader
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // The ring buffer.
   BaseRingBuffer* mRB;

   // The index of the last element that was read.
   long long mReadIndex;

   // Temporary element used during read.
   void* mTempElement;

   // The number of elements that were dropped.
   int mDropCount;

   // The number of reads that had nothing available to read.
   int mNotReadyCount;

   // The number of reads that were retried.
   int mRetryCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RingBufferReader();
   ~RingBufferReader();
   void initialize(BaseRingBuffer* aRingBuffer);

   // Return a pointer to an element, based on an index modulo
   // the number of elements.
   void* elementAt(long long aIndex);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Read an element from the array, updating state variables. Return
   // true if successful. 
   bool doReadElement(void* aElement);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


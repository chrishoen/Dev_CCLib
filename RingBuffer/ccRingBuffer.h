#pragma once

/*==============================================================================

Ring buffer of fixed size opaque objects.

It is single writer multiple reader thread safe.
It is non blocking
It is shared memory safe.

This implements a ring buffer of fixed size objects.


The ring buffer is based on the idea of an infinite memory of contiguous
fixed size elements that is written to sequentially by a single writer.
Writes are indexed by according to a long long WriteIndex, which is
effectively infinite.

The actual memory is finite, the size of which is specified by NumElements
and ElementSize. Writes into the memory are performed using modulo
arithmetic.

Writes are executed as
   ElementArray[++WriteIndex % NumElements] = NewElement

where WriteIndex is the index of the last array element that was written to.

Readers can read from the memory as long as the reads are within the bounds
of a Head and Tail, where

   TailIndex = HeadIndex - (NumElements - 1)
   HeadIndex = WriteIndex, the index of the last element written to.
so
   HeadIndex - TailIndex = NumElements - 1

Here's an example of a buffer with NumElements = 4 that is past the
initialization stage. It is full. The write index is in the first column
and the modulo of it is in the second column.

122 2
123 3  xxxx  Tail
124 0  xxxx
125 1  xxxx
126 2  xxxx  Head  so Head - Tail = 3 = NumElements - 1
127 3

A reader can read any one element of 123,124,125,126.
During a read of 123, an asynchrounous write could occur and the
read would be overwritten. In this case the read would be retried.
Reads are also accomplished with modulo arithmetic.

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
   void* mElementArray;

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
// Ring buffer writer class. There should only be one instance of this class
// for the single writer.

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
// Ring buffer reader class. There can be multiple instance of this class
// for multiple readers.

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


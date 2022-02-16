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

Here's an example of a buffer with NumElements = 8 that is past the
initialization stage. It is full. The write index is in the first column
and the modulo of it is in the second column.

122 2
123 3  xxxx  Tail
124 4  xxxx
125 5  xxxx
126 6  xxxx
127 7  xxxx
128 0  xxxx
129 1  xxxx
130 2  xxxx  Head  so Head - Tail = 7 = NumElements - 1
131 3

A reader can read any one element of 123 .. 130.
During a read of 123, an asynchrounous write could occur and the
read would be overwritten. In this case the read would be retried.
Reads are also accomplished with modulo arithmetic.

As a complication, consider a buffer where the writer writes an
element to the array that only contains partial data. After writing
a few more elements, the writer wants to go back and update a previous
element. A ready read guard is provided for this case.

Here's an example of a buffer with NumElements = 8 and ReadyGuard = 3
A reader can read any one element of 123 .. 127. The writer can go
back and modify any one element of 128 .. 130.

122 2
123 3  xxxx  Tail
124 4  xxxx
125 5  xxxx
126 6  xxxx
127 7  xxxx  Ready = Head - ReadyGuard = 130 - 3
128 0  yyyy
129 1  yyyy
130 2  yyyy  Head  so Head - Tail = 7 = NumElements - 1
131 3

ReadyGuard = 0 means no read ready guard. Then the reader can read
any element of 123 .. 130 and the writer cannot modify any elements
once they have been written.

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

   // Read ready guard.
   long long mReadyGuard;

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
   
   // Write an element to the array at the next element to write to, copying
   // it from the function argument. Update the write index state variable
   // so that it contains the index of the last element written to.
   void doWrite(void* aElement);

   // Return a pointer to the next element to write to. Do not update the
   // write index state variable.
   void* startWrite();

   // Update the write index state variable after a started write is finished
   // so that it contains the index of the last element written to.
   void finishWrite();
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

   // If true then this is the first read.
   bool mFirstFlag;

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
   // Members. State variables.

   // Here's an example of a buffer with NumElements = 8 and ReadyGuard = 3.
   // All elements have been written to. The buffer is full.
   // 
   // The buffer contains written elements on the closed interval [123 .. 130].
   // Elements can be read on [123 .. 127]
   // 122 2
   // 123 3  xxxx  Tail = WriteIndex - (NumElements - 1)
   // 124 4  xxxx
   // 125 5  xxxx
   // 126 6  xxxx
   // 127 7  xxxx  Ready = WriteIndex - ReadyGuard
   // 128 0  yyyy
   // 129 1  yyyy
   // 130 2  yyyy  Head  = WriteIndex
   // 131 3

   // Depending on the context, the last element that was read from or
   // the next element to read from. Successfully or not.
   long long mReadIndex;

   // The previous read index for the last successful read.
   long long mLastReadIndex;

   // The oldest element that was written to.
   long long mTail;

   // The youngest element that can be read from.
   long long mReady;

   // The youngest element that was written to.
   long long mHead;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RingBufferReader();
   ~RingBufferReader();
   void resetVars();
   void initialize(BaseRingBuffer* aRingBuffer);

   // Return a pointer to an element, based on an index modulo
   // the number of elements.
   void* elementAt(long long aIndex);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Read an element from the array, copying it to the function argument.
   // Return true if successful.
   bool doRead(void* aElement);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Helpers.

   // Internal test function that can be used by inheritors to perform
   // ring buffer performance tests.
   virtual void doTest(long long aReadIndex, void* aElement) {}
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


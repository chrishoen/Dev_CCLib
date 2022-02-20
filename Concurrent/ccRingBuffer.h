#pragma once

/*==============================================================================

Ring buffer of fixed size opaque objects.

It is single writer multiple reader thread safe.
It is non blocking
It is not shared memory safe.

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

   TailIndex = HeadIndex - (NumElements - 2)
   HeadIndex = WriteIndex, the index of the last element written to.
so
   HeadIndex - TailIndex = NumElements - 2

Here's an example of a buffer with NumElements = 8 that is past the
initialization stage. It is full. The write index is in the first column
and the modulo of it is in the second column.

122 2
123 3  zzzz
124 4  xxxx  Tail = WriteIndex - (NumElements - 2)
125 5  xxxx
126 6  xxxx
127 7  xxxx
128 0  xxxx
129 1  xxxx
130 2  xxxx  Head  = WriteIndex
131 3  zzzz 

Only elements marked with xxxx can be safely read, on the closed interval
[Tail .. Head]

A reader can read always safely read any one element of 124 .. 130.
During a read of 123, an asynchrounous write to 131 could occur and
the read would be overwritten.

As a complication, consider a buffer where the writer writes an
element to the array that only contains partial data. After writing
a few more elements, the writer wants to go back and update a previous
element. A ready read guard is provided for this case.

Here's an example of a buffer with NumElements = 8 and ReadGap = 3
A reader can read any one element of 124 .. 127. The writer can go
back and modify any one element of 128 .. 130.

122 2
123 3  zzzz
124 4  xxxx  Tail  = WriteIndex - (NumElements - 2)
125 5  xxxx
126 6  xxxx
127 7  xxxx  Ready = WriteIndex - ReadGap = 130 - 3
128 0  yyyy
129 1  yyyy
130 2  yyyy  Head  = WriteIndex
131 3  zzzz

A reader can read always safely read any one element of 124 .. 127.

Only elements marked with xxxx can be safely read, on the closed interval
[Tail .. Ready] = [WriteIndex - (NumElements - 2) .. WriteIndex - ReadGap]

After writing to the Head, the writer can go back and modify elements
marked with yyyy on the closed interval
[Ready + 1 .. Head] = [WriteIndex - (ReadGap - 1) .. WriteIndex]

ReadGap = 0 means no read ready gap. Then the reader can read
any element of 124 .. 130 and the writer cannot modify any elements
once they have been written.

=============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <atomic>
#include <functional>

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ring buffer. This contains variables that describe a ring buffer
// and its state.

class RingBuffer
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Number of elements in the ring buffer.
   long long mNumElements;

   // Size of each element in the ring buffer.
   size_t mElementSize;

   // Read gap.
   long long mReadGap;

   // Memory for the ring buffer element array. This is created on the heap at 
   // initialization.
   void* mElementArrayMemory;

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

   // Constructor.
   RingBuffer();
   ~RingBuffer();

   void initialize(int aNumElements, size_t aElementSize, int aReadGap);

   // Return a pointer to an element, based on an index modulo
   // the number of elements.
   void* elementAt(long long aIndex);

   void show();
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
   RingBuffer* mRB;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RingBufferWriter();
   virtual ~RingBufferWriter() {};
   void resetVars();
   virtual void resetTest() {}
   void initialize(RingBuffer* aRingBuffer);

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   
   // Internal test function that can be override inheritors to perform
   // ring buffer performance tests.
   virtual void doWriteTest(long long aIndex, void* aElement) {}
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
   RingBuffer* mRB;

   // If true then this is the first read.
   bool mFirstFlag;

   // The number of reads that had nothing available to read.
   int mNotReadyCount1;
   int mNotReadyCount2;
   int mNotReadyCount3;

   // The number of elements that were dropped.
   int mDropCount1;
   int mDropCount2;

   // The number of reads that were retried.
   int mRetryCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. State variables.

   // Here's an example of a buffer with NumElements = 8 and ReadGap = 3.
   // 
   // The buffer contains written elements on the closed interval [123 .. 130].
   // Elements can be read on [124 .. 127]. While the reader is reading, the
   // writer could possible write to 131 == 123.
   // 
   // 122 2
   // 123 3  zzzz
   // 124 4  xxxx  Tail  = WriteIndex - (NumElements - 2)
   // 125 5  xxxx
   // 126 6  xxxx
   // 127 7  xxxx  Ready = WriteIndex - ReadGap
   // 128 0  yyyy
   // 129 1  yyyy
   // 130 2  yyyy  Head  = WriteIndex
   // 131 3  zzzz

   // Depending on the context, the last element that was read from or
   // the next element to read from. Successfully or not.
   long long mReadIndex;

   // The previous read index for the last successful read.
   long long mLastReadIndex;

   // The oldest element that can be read from.
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
   virtual ~RingBufferReader() {};
   void resetVars();
   virtual void resetTest() {}
   void initialize(RingBuffer* aRingBuffer);

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
   // Methods.

   // Internal test function that can be override inheritors to perform
   // ring buffer performance tests.
   virtual void doReadTest(long long aIndex, void* aElement) {}
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


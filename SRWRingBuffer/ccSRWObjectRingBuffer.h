#pragma once

/*==============================================================================

Ring buffer of fixed size opaque objects.

It is single reader single writer for a single thread.
It is lock free and non blocking

This accomodates a single writer and multiple indepenent readers. The writer 
writes to the buffer with no knowledge of the readers and the readers can read
from the buffer independantly from each other. There is no locking of the
buffer. Each reader maintains its own state and manages its own logic for
keeping track of buffer indices and dropping of elements and testing for
overwrites.

The ring buffer is based on the idea of an infinite memory of contiguous
fixed size elements that is written to sequentially by a single writer. Writes
are indexed by according to a long long WriteIndex, which is effectively
infinite.

The actual memory is finite, the size of which is specified by NumElements
and ElementSize. Writes into the memory are performed using modulo arithmetic
with NumElements.

Writes are concepually executed as
   ElementArray[NextWriteIndex % NumElements] = NewElement
   ++NextWriteIndex %= NumElements

where NextWriteIndex is the index of the next array element to write to.

Readers can read from the memory as long as the reads are within the bounds
of the indices of a min and max available, where

   MinReadIndex = NextWriteIndex - NumElements
   MaxReadIndex = NextWriteIndex - 1
where
   MaxReadIndex - MinReadIndex = NumElements - 1

Here's an example of a buffer with NumElements = 8 that is past the
initialization stage. It is full. The write index is in the first column
and the modulo of it is in the second column.

122 2  yyyy
123 3  xxxx  NextWriteIndex - NumElements = MinReadIndex
124 4  xxxx
125 5  xxxx
126 6  xxxx
127 7  xxxx
128 0  xxxx
129 1  xxxx
130 2  xxxx  NextWriteIndex - 1 = MaxReadIndex
131 3  zzzz  NextWriteIndex is the next element to write to

Only elements marked with xxxx can be safely read. They are on the closed
interval
[MinReadIndex .. MaxReadIndex] = 
[NextWriteIndex - NumElements .. NextWriteIndex - 1]

A reader can read always safely read any one element of 124 .. 130.
During a read of 123, an asynchrounous write to 131 could occur and
the read would be overwritten. So, any read from less than 124 is
not allowed.

=============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stddef.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This template implements an N element memory structure of type T that
// provides a fixed delay. It can be used for digital filters.

template <class T, int N>
class SRWObjectRingBuffer
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Array of elements. This is allocated on the heap in the
   // initialize function.
   T* mElements;

   // The index of the next element to write to. If this is equal to
   // zero then no writes have occured and the ring buffer is empty.
   long long mNextWriteIndex;

   // The index of the next element to read from.
   long long mNextReadIndex;

   // Min and max possible read indices. These provided a lower and
   // upper bound on possible reads. These are updated by the write
   // operation.
   long long mMinReadIndex;
   long long mMaxReadIndex;

   // If true then the at least N writes have been executed.
   bool mFullFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SRWObjectRingBuffer();
   ~SRWObjectRingBuffer();
   void initialize();
   void finalize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Helpers.

   // Return a reference to an array element at an index modulo the
   // number of elements.
   T& elementAt(long long aIndex);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Write.

   // Write an element to the array at the write index. Increment the
   // write index state variable so that it contains the index of the
   // next element to write to.
   void doWrite(T* aElement);

   // Return a pointer to an element at an offset relative to the 
   // next write index - 1. An offset of zero corresponds to the
   // last element that was written and so, corresponds to the
   // max read index. This can be used for implementing digital
   // filters where, after a write, offset = 0..N-1 corresponds
   // to K, K-1, .. K-(N-1).
   T* atOffset(int aOffset);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Read.

   // Return the number of elements that are available to be read.
   int available();

   // Restart read operations. This sets the first flag true so that
   // the next read will start at the last element that was written,
   // which is the max available.
   void doStartReadAtMax();

   // Restart read operations. This sets the first flag true so that
   // the next read will start at the minimum available.
   void doStartReadAtMin();

   // Read an element from the array, copying it to the function argument.
   // Return true if successful.
   bool tryRead(T* aElement);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

template <class T, int N>
SRWObjectRingBuffer<T, N>::SRWObjectRingBuffer()
{
   mElements = 0;
   initialize();
}

template <class T, int N>
SRWObjectRingBuffer<T, N>::~SRWObjectRingBuffer()
{
   if (mElements)
   {
      delete[] mElements;
      mElements = 0;
   }
}

template <class T, int N>
void SRWObjectRingBuffer<T, N>::initialize()
{
   finalize();
   mElements = new T[N];
   mNextWriteIndex = 0;
   mNextReadIndex = 0;
   mMinReadIndex = 0;
   mMaxReadIndex = 0;
   mFullFlag = false;
}

template <class T, int N>
void SRWObjectRingBuffer<T, N>::finalize()
{
   if (mElements)
   {
      delete[] mElements;
      mElements = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a reference to an array element at an index modulo the
// number of elements.

template <class T, int N>
inline T& SRWObjectRingBuffer<T, N>::elementAt(long long aIndex)
{
   aIndex %= N;
   return mElements[aIndex];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an element to the array at the write index. Increment the
// write index state variable so that it contains the index of the
// next element to write to.

template <class T, int N>
void SRWObjectRingBuffer<T, N>::doWrite(T* aElement)
{
   // Copy the input element to the array.
   elementAt(mNextWriteIndex) = *aElement;

   // Update the state variables.
   mNextWriteIndex++;
   mFullFlag = mNextWriteIndex >= N;
   mMaxReadIndex = mNextWriteIndex - 1;
   mMinReadIndex = mNextWriteIndex - N;
   if(mMinReadIndex < 0) mMinReadIndex = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a pointer to an element at an offset relative to the 
// next write index - 1. An offset of zero corresponds to the
// last element that was written and so, corresponds to the
// max read index. This can be used for implementing digital
// filters where, after a write, offset = 0..N-1 corresponds
// to K, K-1, .. K-(N-1).

template <class T, int N>
T* SRWObjectRingBuffer<T, N>::atOffset(int aOffset)
{
   int tIndex = (int)(mMaxReadIndex - aOffset);
   if (tIndex < 0) tIndex = 0;
   return &mElements[tIndex % N];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return the number of elements that are available to be read.

template <class T, int N>
int SRWObjectRingBuffer<T, N>::available()
{
   long long tDiff = mMaxReadIndex - mNextReadIndex + 1;
   if (tDiff > N) tDiff = N;
   return (int)tDiff;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Restart read operations. This sets the first flag true so that
// the next read will start at the last element that was written,
// which is the max available.

template <class T, int N>
void SRWObjectRingBuffer<T, N>::doStartReadAtMax()
{
   mNextReadIndex = mMaxReadIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Restart read operations. This sets the first flag true so that
// the next read will start at the minimum available.

template <class T, int N>
void SRWObjectRingBuffer<T, N>::doStartReadAtMin()
{
   mNextReadIndex = mMinReadIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read an element from the array, copying it to the function argument.
// Return true if successful.

template <class T, int N>
bool SRWObjectRingBuffer<T, N>::tryRead(T* aElement)
{
   // Test for no written data yet.
   if (mNextWriteIndex == 0)
   {
      return false;
   }

   // Test for no new data available.
   if (mNextReadIndex > mMaxReadIndex)
   {
      return false;
   }

   // Test for dropped data.
   if (mNextReadIndex < mMinReadIndex)
   {
      mNextReadIndex = mMinReadIndex;
   }

   // Copy the array element to the output. Update the state.
   *aElement = elementAt(mNextReadIndex++);

   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


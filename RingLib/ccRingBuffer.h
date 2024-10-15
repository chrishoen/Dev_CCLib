#pragma once

/*==============================================================================

Ring buffer of fixed size opaque objects.

It is single writer multiple reader thread safe.
It is lock free and non blocking
There are two versions, one for heap and one for shared memory.

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
   NextWriteIndex++

where NextWriteIndex is the index of the next array element to write to.

Readers can read from the memory as long as the reads are within the bounds
of the indices of a min and max available, where

   MinReadIndex = NextWriteIndex - (NumElements - 1)
   MaxReadIndex = NextWriteIndex - 1
where
   MaxReadIndex - MinReadIndex = NumElements - 1

Here's an example of a buffer with NumElements = 8 that is past the
initialization stage. It is full. The write index is in the first column
and the modulo of it is in the second column.

122 2
123 3  zzzz
124 4  xxxx  NextWriteIndex - (NumElements - 1) = MinReadIndex
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
[NextWriteIndex - (NumElements - 1) .. NextWriteIndex - 1]

A reader can read always safely read any one element of 124 .. 130.
During a read of 123, an asynchrounous write to 131 could occur and
the read would be overwritten. So, any read from less than 124 is
not allowed.

As a complication, consider a buffer where the writer writes an
element to the array that only contains partial data. After writing
a few more elements, the writer wants to go back and update a previous
element. A read gap is provided for this case.

Here's an example of a buffer with NumElements = 8 and ReadGap = 3
A reader can read any one element of 124 .. 127. The writer can go
back and modify any one element of 128 .. 130.

122 2
123 3  zzzz
124 4  xxxx  NextWriteIndex - (NumElements - 1) = MinReadIndex
125 5  xxxx
126 6  xxxx
127 7  xxxx  NextWriteIndex - ReadGap - 1  = MaxReadIndex
128 0  yyyy  NextWriteIndex - ReadGap
129 1  yyyy
130 2  yyyy  NextWriteIndex - 1
131 3  zzzz  NextWriteIndex is the next element to write to

A reader can read always safely read any one element of 124 .. 127.

Only elements marked with xxxx can be safely read on the closed interval
[WriteIndex - (NumElements - 1) .. WriteIndex - ReadGap - 1]

While writing an element marked zzzz, the writer can go back and modify
elements marked with yyyy on the closed interval
[WriteIndex - ReadGap .. WriteIndex]

ReadGap = 0 means no read gap. Then the reader can read any element of
124 .. 130 and the writer cannot modify any elements once they have been
written.

ALSO, DON'T FORGET:
The following rules are for shared memory, regions that are shared between
different processes (who therefore have different address spaces):

1) No constructors.
2) No pointers.
3) No dynamic memory, this means no std::vector, ...
4) No vtables, this means no virtual functions.
5) Be careful with your loads and stores.

=============================================================================*/

#include "ccIntrinsics.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ring buffer. This contains variables that describe a ring buffer
// and its state. This class is shared memory safe.

class alignas(16) RingBufferState
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // The index of the next element to write to. If this is equal to
   // zero then no writes have occured and the ring buffer is empty.
   // This single variable encapsulates the state of the ring buffer. It
   // can only be written to by a single writer thread and it can be read
   // by multiple reader threads. Buffer memory is addressed via this index
   // modulo the number of elements. This variable is surrounded by padding
   // so that it is on a separate cache line.

   alignas(16) long long mPadding1[8];
   alignas(16) volatile long long mNextWriteIndex;
   alignas(16) long long mPadding2[8];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   virtual ~RingBufferState() {}

   void initialize()
   {
      store_barrier();
      mNextWriteIndex = 0;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ring buffer writer class. There should only be one instance of this
// class for the single writer. This attaches to a ring buffer and is 
// used to write to it. It is not shared memory safe.

template <class Element, int NumElements>
class RingBufferWriter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // The ring buffer.
   RingBufferState* mRB;

   // The ring buffer element array memory.
   Element* mElementArrayMemory;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true then call an inheritor supplied test function after a
   // write operation.
   bool mTestFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor.

   // Constructor.
   RingBufferWriter()
   {
      mRB = 0;
      mElementArrayMemory = 0;
      mTestFlag = false;
      resetVars();
   }
   virtual ~RingBufferWriter() {};

   // Reset variables.
   void resetVars()
   {
      resetTest();
   }
   virtual void resetTest() {}

   // Initialize.
   void initialize(RingBufferState* aRingBufferState, Element* aElementArrayMemory)
   {
      resetVars();
      mRB = aRingBufferState;
      mElementArrayMemory = aElementArrayMemory;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Helpers.

   // Return a pointer to an element, based on an index modulo the number
   // of elements.
   Element* elementAt(long long aIndex)
   {
      aIndex %= NumElements;
      return &mElementArrayMemory[aIndex];
   }

   // Return the index of the next element to write to.
   long long getNextWriteIndex()
   {
      // Return the index of the next element to write to.
      return mRB->mNextWriteIndex;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   
   // Write an element to the array at the write index, copying it from
   // the function argument. Increment the write index state variable so 
   // that it contains the index of the next element to write to.
   void doWrite(Element* aElement)
   {
      // Get the index of the next element to write to.
      long long tWriteIndex = mRB->mNextWriteIndex;

      // Get the address of the next element to write to.
      Element* tPtr = elementAt(tWriteIndex);

      // Copy the element into the array.
      *tPtr = *aElement;

      // Internal test function that can be used by inheritors to perform
      // ring buffer performance tests.
      if (mTestFlag)
      {
         doTest(tWriteIndex, tPtr);
      }

      // Increment the write index to the next element to write to.
      store_barrier();
      mRB->mNextWriteIndex++;
      store_barrier();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   
   // Return a pointer to the next element to write to, which is the element
   // at the write index. Do not increment the  write index state. The caller
   // can then execute its own write operation.
   Element* startWrite()
   {
      // Get the index of the next element to write to.
      long long tWriteIndex = mRB->mNextWriteIndex;

      // Get the address of the next element to write to.
      Element* tPtr = elementAt(tWriteIndex);

      // Return the address of the next element to write to.
      return tPtr;
   }

   // Increment the write index state variable after a started write is
   // finished so that it contains the index of the last element written to.
   void finishWrite()
   {
      if (mTestFlag)
      {
         // Get the index of the next element to write to.
         long long tWriteIndex = mRB->mNextWriteIndex;

         // Get the address of the next element to write to.
         Element* tPtr = elementAt(tWriteIndex);

         // Internal test function that can be used by inheritors to perform
         // ring buffer consistency tests. This is called with the index of
         // the write and the element that was written.
         doTest(tWriteIndex, tPtr);
      }

      // Increment the write index to the next element to write to.
      store_barrier();
      mRB->mNextWriteIndex++;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   
   // Internal test function that can be used by inheritors to perform
   // ring buffer consistency tests. This is called after the write, but
   // before incrementing the write index. It is passed the the write
   // index and the element that was written.
   virtual void doTest(long long aIndex, Element* aElement) {}
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ring buffer reader class. There can be multiple instances of this
// class for multiple readers. This attaches to a ring buffer and is 
// used to read from it. It is not shared memory safe.

template <class Element, int NumElements, int ReadGap>
class RingBufferReader
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // The ring buffer.
   RingBufferState* mRB;

   // The ring buffer element array memory.
   Element* mElementArrayMemory;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // The index of the last successful read.
   long long mLastReadIndex;

   // Saved index of the last successful read. This is used to 
   // undo a read.
   long long mSaveLastReadIndex;

   // If true then this is the first read.
   bool mFirstFlag;

   // If true then restart reads at the max available,
   // else restart reads at the min available.
   bool mRestartAtMax;

   // If true then call an inheritor supplied test function after a
   // read operation.
   bool mTestFlag;

   // The number of reads that had no elements available to read.
   int mNotReadyCount1;
   int mNotReadyCount2;
   int mNotReadyCount3;

   // The number of elements that were dropped.
   int mDropCount;

   // The number of overwrites that occurred.
   int mOverwriteCount;

   // The max number of difference between two consecutive read operations.
   int mMaxDeltaRead;

   // Internal debug error count;
   int mErrorCount;

   // If true then the last read operation resulted in not ready condition.
   bool mNotReadyFlag;

   // If true then the last read operation resulted in an overwrite condition.
   bool mOverwriteFlag;

   // The number of successful reads.
   int mReadCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor.

   RingBufferReader()
   {
      mRB = 0;
      mElementArrayMemory = 0;
      mTestFlag = false;
      resetVars();
   }
   virtual ~RingBufferReader() {};

   void resetVars()
   {
      mFirstFlag = true;
      mRestartAtMax = true;
      mLastReadIndex = 0;
      mNotReadyCount1 = 0;
      mNotReadyCount2 = 0;
      mNotReadyCount3 = 0;
      mErrorCount = 0;
      mDropCount = 0;
      mMaxDeltaRead = 0;
      mOverwriteCount = 0;
      mNotReadyFlag = false;
      mOverwriteFlag = false;
      mReadCount = 0;
      resetTest();
   }
   virtual void resetTest() {}

   void initialize(RingBufferState* aRingBufferState, Element* aElementArrayMemory)
   {
      resetVars();
      mRB = aRingBufferState;
      mElementArrayMemory = aElementArrayMemory;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Helpers.

   // Return a pointer to an element, based on an index modulo the number
   // of elements.
   Element* elementAt(long long aIndex)
   {
      aIndex %= NumElements;
      return &mElementArrayMemory[aIndex];
   }

   // Return the number of elements that are available to be read.
   int available()
   {
      long long tMaxReadIndex = saferead_i64(&mRB->mNextWriteIndex) - 1 - ReadGap;
      long long tDiff = tMaxReadIndex - mLastReadIndex;
      if (tDiff > NumElements - 1) tDiff = NumElements - 1;
      return (int)tDiff;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Restart read operations. This sets the first flag true so that
   // the next read will start at the last element that was written,
   // which is the max available.
   void doRestartAtMax()
   {
      mFirstFlag = true;
      mRestartAtMax = true;
   }

   // Restart read operations. This sets the first flag true so that
   // the next read will start at the minimum available.
   void doRestartAtMin()
   {
      mFirstFlag = true;
      mRestartAtMax = false;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Read an element from the array, copying it to the function argument.
   // Return true if successful.
   // 
   // Here's an example of a buffer with NumElements = 8 and ReadGap = 3
   // A reader can read any one element of 124 .. 127. The writer can go
   // back and modify any one element of 128 .. 130.
   //
   // 122 2
   // 123 3  zzzz
   // 124 4  xxxx  NextWriteIndex - (NumElements - 1) = MinReadIndex
   // 125 5  xxxx
   // 126 6  xxxx
   // 127 7  xxxx  NextWriteIndex - ReadGap - 1 = MaxReadIndex
   // 128 0  yyyy  NextWriteIndex - ReadGap
   // 129 1  yyyy
   // 130 2  yyyy  NextWriteIndex - 1
   // 131 3  zzzz  NextWriteIndex is the next element to write to

   bool doRead(Element* aElement)
   {
      // Do this first.
      mNotReadyFlag = false;
      mOverwriteFlag = false;

      // Local variables.
      long long tMinReadIndex = 0;
      long long tMaxReadIndex = 0;
      long long tNextReadIndex = 0;

      // Get the initial write index. This might change asynchronously during
      // the read. The write index is the index of the next element that the 
      // writer will write to.
      long long tNextWriteIndex = saferead_i64(&mRB->mNextWriteIndex);
      load_barrier();

      // Test for invalid data. This means that the writer has not yet
      // written any elements or is resetting the buffer.
      if (tNextWriteIndex == 0)
      {
         // The writer is not ready.
         mFirstFlag = true;
         mNotReadyCount1++;
         mNotReadyFlag = true;
         return false;
      }

      // Calculate the indices of the limits of available elements.
      tMinReadIndex = tNextWriteIndex - (NumElements - 1);
      tMaxReadIndex = tNextWriteIndex - 1 - ReadGap;

      // If the max available element is negative then no elements are
      // available yet, so exit. This can happen with a nonzero read gap.
      if (tMaxReadIndex < 0)
      {
         // Set the read for the behind the maximum available element.
         mLastReadIndex = tMaxReadIndex - 1;
         mNotReadyCount2++;
         mNotReadyFlag = true;
         return false;
      }

      // Test for the first read.
      if (mFirstFlag)
      {
         mFirstFlag = false;
         mReadCount = 0;
         // Set the read for the maximum available element.
         if (mRestartAtMax)
         {
            mLastReadIndex = tMaxReadIndex - 1;
            tNextReadIndex = tMaxReadIndex;
         }
         // Set the read for the minimum available element.
         else
         {
            mLastReadIndex = tMinReadIndex - 1;
            tNextReadIndex = tMinReadIndex;
         }
      }
      else
      {
         // If the maximum available element has already been read then
         // no elements are available, so exit.
         if (mLastReadIndex == tMaxReadIndex)
         {
            // There's nothing to read.
            mNotReadyCount3++;
            mNotReadyFlag = true;
            return false;
         }

         // If the last element read is behind the minimum available element, 
         // then read from the minimum available element.
         if (mLastReadIndex < tMinReadIndex)
         {
            tNextReadIndex = tMinReadIndex;
         }
         // Else read from the next one.
         else
         {
            tNextReadIndex = mLastReadIndex + 1;
         }
      }

      // This should never happen.
      if (tNextReadIndex < 0)
      {
         mErrorCount++;
         mNotReadyFlag = true;
         return false;
      }

      // Get the address of the next element to read.
      Element* tPtr = elementAt(tNextReadIndex);

      // Copy that element into the argument element.
      *aElement = *tPtr;

      // If, during the read, the ring buffer was written to asynchronously
      // by the writer, then test if the read was possibly or actually
      // overwritten. If it was then drop the read.

      // Get the final write index. If a write occurred during the read then
      // this will be different than the write index at the beginning of the
      // read. If the read element was less than the final min available
      // element then the read was or could have been overwritten, so drop it.
      load_barrier();
      tNextWriteIndex = saferead_i64(&mRB->mNextWriteIndex);
      load_barrier();
      tMinReadIndex = tNextWriteIndex - (NumElements - 1);
      if (tNextReadIndex < tMinReadIndex)
      {
         mOverwriteCount++;
         mOverwriteFlag = true;
         return false;
      }

      // Internal test function that can be used by inheritors to perform
      // ring buffer consistency tests. This is called with the index of
      // the read and the element that was read.
      if (mTestFlag)
      {
         doTest(tNextReadIndex, aElement);
      }

      // Increment the drop count. If none were dropped then the read index
      // should be the index of the last succesful read plus one.
      if (mLastReadIndex > 0)
      {
         int tDeltaRead = (int)(tNextReadIndex - mLastReadIndex);
         if (tDeltaRead > mMaxDeltaRead) mMaxDeltaRead = tDeltaRead;
         mDropCount += tDeltaRead - 1;
      }

      // Save the index for the last successful read. This is used to 
      // undo this read operation.
      mSaveLastReadIndex = mLastReadIndex;

      // Store the new index for the last successful read.
      mLastReadIndex = tNextReadIndex;

      // Success. 
      mReadCount++;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Undo the last read operation. This sets the last read index to 
   // the saved last read index.

   void doUndoLastRead()
   {
      mLastReadIndex = mSaveLastReadIndex;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Internal test function that can be used by inheritors to perform
   // ring buffer consistency tests. This is called after the read, but
   // before incrementing the read index. It is passed the the read
   // index and the element that was read.
   virtual void doTest(long long aIndex, Element* aElement) {}
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


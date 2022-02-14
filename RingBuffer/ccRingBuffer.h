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

//******************************************************************************
//******************************************************************************
//******************************************************************************

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
   // Members. All if these must be set by an inheriting class.

   // Major and minor moduli. The major modulus must be a multiple of
   // the minor modulus. 
   int mMajorMod;
   int mMinorMod;

   // Size of each element in the ring buffer.
   int mElementSize;

   // The address of the first element in the buffer. The ring buffer memory
   // must contain contiguous storage for MinorMod elements.
   void* mElements;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. State variables.

   // The major index of the next element to be written to. 
   int mMajorIndex;

   // If true then at no writes have occured since initialization.
   bool mEmpty;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // No constructor.
   virtual void reset();

   // Return a pointer to an element, based on an index modulo the minor
   // modulus.
   void* elementAt(int aIndex);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Lock free object queue class.

class RingBufferWriter
{
public:

   // Allocate memory for the queue and free list arrays and initialize the
   // queue variables. 
   void initialize(int aNumElements,int aElementSize);
   void initialize(int aNumElements,int aElementSize,bool aConstructorFlag, void* aMemory);

   // Deallocate memory.
   void finalize();

   // Queue size
   int size();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue and Free List Methods. These write or read objects from the queue
   // and pop or push node indices from the free list.

   // These are used to enqueue an object. StartWrite pops an object from the 
   // free list and returns a pointer to it. If the queue is full then it 
   // returns null. After writing to the object, FinishWrite is called to 
   // enqueue it at the queue tail. The node index is passed between the two
   // methods.

   void* startWrite  (int* aNodeIndex);
   void  finishWrite (int  aNodeIndex);

   // These are used to dequeue an object. StartRead dequeues an object from the 
   // queue head and returns a pointer to it. After reading from the object,
   // FinishRead is called to push it onto the free list. The node index is 
   // passed between the two methods.

   void* startRead   (int* aNodeIndex);
   void  finishRead  (int  aNodeIndex);

   // These are called by the above write and read methods. 
   bool  listPop     (int* aNode);
   bool  listPush    (int  aNode);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helper methods.
private:
   // Return a pointer to an object, based on its object index.
   void* elementAt(int aIndex);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Example

#if 0
   //---------------------------------------------------------------------------
   // Management

   // includes
   #include <new>
   #include "ccRingBuffer.h"

   // Declare object queue
   CC::RingBuffer mObjectQueue;
   // Initialize object queue
   mObjectQueue.initialize(100,sizeof(Class1A));

   //---------------------------------------------------------------------------
   // Enqueue an object

   // Example counter
   int tWriteCount;
   // This is passed between StartWrite and FinishWrite
   int tWriteIndex;

   // Try to start a write to allocate an object
   void* tElement = mObjectQueue.startWrite(&tWriteIndex);
   // If the queue is not full
   if (tElement)
   {
      // Create a new object with placement new on the allocated object.
      // Placement new must be used with any classes that use vtables.
      Class1A* tObject = new(tElement) Class1A;
      // Access the new object
      tObject->mCode1 = tWriteCount;
      // Finish the write
      mObjectQueue.finishWrite(tWriteIndex);
   }

   //---------------------------------------------------------------------------
   // Dequeue an object 

   // Example counter
   int tReadCount;
   // This is passed between StartRead and FinishRead
   int tReadIndex;

   // Try to start an object read, returns a pointer to an object
   Class1A* tObject = (Class1A*)mObjectQueue.startRead(&tReadIndex);
   // If the queue is not empty
   if (tObject)
   {
      // Access the object
      tReadCount = tObject->mCode1;
      // Finish the read
      mObjectQueue.finishRead(tReadIndex);
   }
#endif


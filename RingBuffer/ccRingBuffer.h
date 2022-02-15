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

   // The address of the first element in the buffer element array. The ring 
   // buffer memory must contain contiguous storage for MinorMod elements.
   void* mElements;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. State variables.

   // The major index of the next element to be written to. 
   int mMajorIndex;

   // If true then writes have occured since initialization.
   bool mEmpty;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   virtual void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helper methods.

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. These are copied from a ring buffer instance at initialization.

   // The ring buffer.
   BaseRingBuffer* mRB;

   // Major and minor moduli. The major modulus must be a multiple of
   // the minor modulus. 
   int mMajorMod;
   int mMinorMod;

   // Size of each element in the ring buffer.
   int mElementSize;

   // The address of the first element in the ring buffer element array.
   void* mElements;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RingBufferWriter();
   void initialize(BaseRingBuffer* aRingBuffer);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   
   // Copy an element to the element array at the current major index modulo
   // the minor modulus. Increment the major index modulo the major modulus.
   // Set the empty flag false.
   void doWriteElement(void* aElement);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helper methods.

   // Return a pointer to an element, based on an index modulo the minor
   // modulus.
   void* elementAt(int aIndex);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


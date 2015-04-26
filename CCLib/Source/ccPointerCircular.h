#ifndef _POINTERCIRCULAR_H_
#define _POINTERCIRCULAR_H_
/*==============================================================================

This defines a circular array of pointers. It is used by short term memory 
block pools to establish circular buffers. It is thread safe, it uses critical
sections to lock access to array indices.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a circular array of pointers. It maintains an array
// of pointers that are dynamically allocated at initialization. Access to the
// array is done is a circular manner. It is used to implement circular
// buffers. This is used by the short term memory pool classes to maintain 
// pointers into arrays of allocated memory blocks.

class PointerCircular
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   PointerCircular();
  ~PointerCircular();

   // Allocate memory for the pointer array and initialize the indices. 
   // aAllocate is the number of pointers to allocate, the size of the array.
   void initialize(int aAllocate);

   // Put a pointer into the circular array. This is used during initialization
   // of short term memory pools by filling up the pointer array with allocated
   // block addresses. It cycles through the array via the PutIndex.
   bool  put(void* aPointer);

   // Get a pointer from the circular array. This is used to allocate a block
   // from a short term memory pool. It returns the address of an allocated
   // block. It does so in a circular manner by indexing through the pointer
   // array, via the GetIndex.
   void* get();

   // This is called by an owner to indicate that it is done with its current
   // element. It decrements the usage counter. It is used to track usage of
   // the circular buffer.
   void done();

   //---------------------------------------------------------------------------
   // Members

   // Array of pointers, it is dynamically allocated by initialize.
   void** mArray;

   // Index into the array. Put operations cycle through the array via this
   // index.
   int mPutIndex;

   // Index into the array. Get operations cycle through the array via this
   // index.
   int mGetIndex;

   // Size of the array, number of pointers allocated.
   int mAllocate;

   // Count of allocated elements. This is incremented by get operations and
   // decremented by done operations. This is a usage counter that is used
   // to track usage of the circular buffer.
   int mCount;
};

//******************************************************************************

}//namespace
#endif


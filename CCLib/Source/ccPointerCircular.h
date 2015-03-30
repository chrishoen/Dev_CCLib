#ifndef _POINTERCIRCULAR_H_
#define _POINTERCIRCULAR_H_
/*==============================================================================

This defines a circular array of pointers. It is used by heaps and
and pools as an allocator. It is not thread safe.

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
// buffers.

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

   // Put a pointer into the circular array.
   bool  put(void* aPointer);

   // Get a pointer from the circular array.
   void* get();

   //---------------------------------------------------------------------------
   // Members

   // Array of pointers, Dynamically allocated by initialize.
   void** mArray;

   // Index into the array, to put to.
   int mPutIndex;

   // Index into the array, to get from.
   int mGetIndex;

   // Size of the array, number of pointers allocated.
   int mAllocate;
};

//******************************************************************************

}//namespace
#endif

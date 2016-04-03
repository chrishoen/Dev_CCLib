#ifndef _CCLFFREELISTSTACK_H_
#define _CCLFFREELISTSTACK_H_
/*==============================================================================

Lock Free Free List Stack of Indices. 

This implements a fixed size free list stack of indices. The free list is 
thread safe. It uses atomic compare and exchanges to guard against concurrency 
contentions. It implements the Trieber algorithm with no backoff.

This is used by containers that use a free list.

==============================================================================*/
#include <atomic>
#include "ccLFIndex.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class LFFreeListIndexStack
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Constructor
   LFFreeListIndexStack();
  ~LFFreeListIndexStack();

   // Initialize the stack for a fixed size. Initialize member variables and
   // allocate system memory for the treiber linked list node array.
   // Initialize the stack to full. Push the indices of the blocks for which 
   // this will be used onto the stack.
   // For aAllocate==10 this will push 0,1,2,3,4,5,6,7,8,9
   void initialize(int aNumElements);

   // Deallocate memory.
   void finalize();

   // Pop a value off of the stack. Return false if the stack is empty.
   bool pop(int* aValue);

   // Push a value onto the stack. Return false if the stack is full.
   bool push(int aValue);

   // Return size, the number of elements that have been pushed onto the stack.
   int size();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // Number of values allocated
   int mNumElements;

   // Number of free list nodes allocated
   int mListAllocate;

   // Free List array and variables
   AtomicLFIndex*    mListNext;
   AtomicLFIndex     mListHead;
   std::atomic<int>  mListSize;
   
   std::atomic<int>* mListHeadIndexPtr = (std::atomic<int>*)&mListHead;

   static const int  cInvalid = 0x80000000;
};

//******************************************************************************

}//namespace
#endif


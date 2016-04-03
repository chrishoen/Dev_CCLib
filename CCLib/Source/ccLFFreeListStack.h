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

class LFFreeListStack
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Constructor
   LFFreeListStack();
  ~LFFreeListStack();

   // This initializes the stack to a fixed size. It initializes member
   // variables and allocates system memory for the treiber stack linked 
   // list. The stack is initialized to full.
   void initialize(int aNumElements);

   // Deallocate memory.
   void finalize();

   // Pop a value off of the stack. Return false if the stack is empty.
   bool pop(int* aValue);

   // Push a value onto the stack. Return false if the stack is full.
   bool push(int aValue);

   // Return size.
   int size();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // Number of values allocated
   int mNumElements;

   // Number of free list nodes allocated
   int mListAllocate;

   // Pointer to allocated memory, array of values
   void* mMemory;

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


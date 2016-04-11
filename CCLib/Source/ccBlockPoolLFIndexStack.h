#ifndef _CCBLOCKPOOLLFINDEXSTACK_H_
#define _CCBLOCKPOOLLFINDEXSTACK_H_
/*==============================================================================

Lock Free Free List Stack of Indices. 

This implements a fixed size free list stack of indices. The free list is 
thread safe. It uses atomic compare and exchanges to guard against concurrency 
contentions. It implements the Trieber algorithm with no backoff.

This is used by containers that use a free list.

==============================================================================*/
#include <atomic>
#include "ccLFIndex.h"
#include "ccBlockPoolBaseIndexStack.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// State variables for the stack. These are located in a separate class
// so that they can be located in external memory.

class BlockPoolLFIndexStackState
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Number of values allocated
   int mNumElements;

   // Number of free list nodes allocated
   int mListNumElements;

   // Free List array and variables
   AtomicLFIndex     mListHead;
   std::atomic<int>  mListSize;
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   BlockPoolLFIndexStackState();

   // Initialize.
   void initialize(BlockPoolParms* aParms);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class BlockPoolLFIndexStack : public BlockPoolBaseIndexStack
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize(BlockPoolParms* aParms);

   class MemorySize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Constructor
   BlockPoolLFIndexStack();
  ~BlockPoolLFIndexStack();

   // Initialize the stack to either allocate memory from the system heap or
   // to use external memory that has already been allocated for it.
   // If aMemory is null then it mallocs from the system heap. If not, then
   // it uses the memory pointed to by aMemory.
   // If external memory is used, it must be of a size obtained by a call to
   // getMemorySize.
   //
   // Initialize the stack to full. Push the indices of the blocks for which 
   // this will be used onto the stack.
   // For aAllocate==10 this will push 9,8,7,6,5,4,3,2,1,0 so that element
   // zero will be the first one poped.
   void initialize(BlockPoolParms* aParms,void* aMemory = 0);

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

   // If this flag is false then the memory for this object was created
   // externally. If it is true then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mFreeMemoryFlag;

   // Pointer to memory for which the stack resides. This is either created
   // externally and passed as an initialization parameter or it is created
   // on the system heap at initialization.
   void* mMemory;

   // Free List array for treiber stack.
   AtomicLFIndex*    mListNext;
   
   // State variables for the stack. These are located in a separate class
   // so that they can be located in externale memory.
   BlockPoolLFIndexStackState* mX;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // More

   static const int  cInvalid = 0x80000000;

};

//******************************************************************************

}//namespace
#endif


#ifndef _CCBLOCKPOOLINDEXSTACK_H_
#define _CCBLOCKPOOLINDEXSTACK_H_
/*==============================================================================

Free List Stack of Indices. 

This implements a free list stack of indices. It is not thread safe.

==============================================================================*/
#include "ccBlockPoolBaseIndexStack.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This encapsulates a stack of indices to be used with containers that 
// implement free lists of blocks.

namespace CC
{

   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// State variables for the stack. These are located in a separate class
// so that they can be located in external memory.

class BlockPoolIndexStackState
{
public:

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   // Index into the array.
   int mIndex;

   // Size of the array, number of elements allocated.
   int mNumElements;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods.

   // Constructor.
   BlockPoolIndexStackState();

   // Initialize.
   void initialize(int aNumElements);

   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.
   static int getMemorySize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class BlockPoolIndexStack : public BlockPoolBaseIndexStack
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Constructor
   BlockPoolIndexStack();
  ~BlockPoolIndexStack();

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
   void initialize(int aNumElements,void* aMemory = 0);

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

   // If this flag is true then the memory for this object was created
   // externally. If it is false then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mExternalMemoryFlag;

   // Pointer to memory for which the stack resides. This is either created
   // externally and passed as an initialization parameter or it is created
   // on the system heap at initialization.
   void* mMemory;

   // Array of indices for the stack.
   int* mElement;
   
   // State variables for the stack. These are located in a separate class
   // so that they can be located in externale memory.
   BlockPoolIndexStackState* mX;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize(int aNumElements);
};

//******************************************************************************

}//namespace
#endif

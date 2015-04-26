#ifndef _CCBLOCKPOOL_H_
#define _CCBLOCKPOOL_H_
/*==============================================================================

This defines a memory pool of a fixed number of blocks that are of a fixed
size.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockArray.h"
#include "ccPointerStack.h"
#include "ccPointerCircular.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a pool of memory blocks. At initialization, a fixed
// number of blocks of fixed size are allocated on the system heap. Methods
// are provided to allocate and deallocate blocks from the pool. These methods
// are thread safe because they use critical sections.
//
// This is used in programs that will have a bounded number of specific
// objects allocated at any given time. The memory for the objects is allocated
// at program initialization and allocation/deallocation of the objects
// throughout the programs lifetime is much faster than system heap
// malloc/free operations (new/delete). To use this, the maximum number of 
// blocks that can be allocated at any given time must be known apriori.
// 
// There are two types of memory block pool: short term and long term. Short
// term blocks are non persistent and have short term lifetimes. Long term
// blocks are persistent and have long lifetimes. The type of the block pool
// is set at initialization and there can only be one type for a specific
// instance.
//
// Blocks that are allocated from long term pools must be deallocated once
// their lifetimes have expired. Blocks that are allocated from short term 
// pools are not deallocated, they are simply reused. 

class BlockPool
{
public:
   //---------------------------------------------------------------------------
   // Methods

   //---------------------------------------------------------------------------
   // Constructor
   BlockPool();
  ~BlockPool();

   //---------------------------------------------------------------------------
   // This initializes the block pool for short term blocks. It allocates memory
   // for the block array and initializes the circular pointer array. It is
   // passed the number of blocks to allocate and the size of the blocks.
   void initializeShortTerm(int aAllocate,int aBlockSize);

   // This initializes the block pool for long term blocks. It allocates memory
   // for the block array and initializes the pointer stack. It is passed the
   // number of blocks to allocate and the size of the blocks.
   void initializeLongTerm(int aAllocate,int aBlockSize);

   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block. If the block pool is 
   // short term, it gets a pointer from the circular array of pointers and 
   // advances the index into the array. If the block pool is long term, it 
   // pops a pointer from the pointer stack.
   void* get();

   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block. If the block pool
   // is short term, it does nothing. If the block pool is long term, it pushes
   // the pointer back onto the pointer stack.
   void put(void* aBlockPointer);

   //---------------------------------------------------------------------------
   // Members

   // This allocates storage for the blocks on the system heap and provides
   // pointer access to the allocated blocks.
   BlockArray mBlocks;

   // The two types of block pool, short term and long term lifetimes. Short
   // term blocks are non persistent and long term blocks are persistent.
   enum
   {
      BlockPoolType_ShortTerm = 1,
      BlockPoolType_LongTerm  = 2,
   };

   // This variable determines which of the two following pointer arrays are
   // used, short term or long term.
   int mBlockPoolType;

   bool isShortTerm(){ return mBlockPoolType == BlockPoolType_ShortTerm; }
   bool isLongTerm() { return mBlockPoolType == BlockPoolType_LongTerm; }

   // This is a circular buffer of pointers. This is used if the block pool
   // has short term blocks. It is an array of pointers into the above
   // allocated memory block array. To allocate a block, a pointer is gotten
   // from the array and its index is incremented. Allocations are locked with
   // critical sections, making them thread safe.
   PointerCircular mShortTermPointerCircular;

   // This is a stack of pointers. This is used if the block pool has long
   // term blocks. It is a stack of pointers into the above allocated memory
   // block array. To allocate a block, a pointer is popped off of the stack.
   // To free a block, a pointer is pushed back onto the stack. To deallocate
   // a block, a pointer is pushed back onto the stack. Pushes and Pops are
   // locked with critical sections, making tehm thread safe.
   PointerStack mLongTermPointerStack;

   //---------------------------------------------------------------------------
   // Helpers
   void show();

};

//******************************************************************************

}//namespace
#endif


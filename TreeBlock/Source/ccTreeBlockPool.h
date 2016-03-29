#ifndef _CCTREEBLOCKPOOL_H_
#define _CCTREEBLOCKPOOL_H_
/*==============================================================================

This defines a memory pool of a fixed number of blocks that are of a fixed
size.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include "ccBlockArray.h"
#include "ccValueStack.h"

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

template <class TreeBlockClass>
class TreeBlockPool
{
public:

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constructor

   TreeBlockPool()
   {
   }

  ~TreeBlockPool()
   {
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This initializes the block pool for short term blocks. It allocates memory
   // for the block array and initializes the circular pointer array. It is
   // passed the number of blocks to allocate and the size of the blocks.

   void initializeShortTerm(int aAllocate,int aBlockSize)
   {
      // Set the block pool type
      mBlockPoolType = BlockPoolType_ShortTerm;

      // Set the number of blocks to allocate.
      mAllocate = aAllocate;

      // Allocate memory for the block array.
      // For aAllocate==10 blocks  will range 0,1,2,3,4,5,6,7,8,9.
      // An index of zero is reserved for null index, so block 0 is unused.
      mBlocks.initialize(aAllocate,aBlockSize);

      // Initialize the block circular index
      // An index of zero is reserved for null index.
      // For aAllocate==10 the indices will range 1,2,3,4,5,6,7,8,9.
      mShortTermIndex = 1;

      // Counter
      mShortTermCount = 0;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This initializes the block pool for long term blocks. It allocates memory
   // for the block array and initializes the index stack. It is passed the
   // number of blocks to allocate and the size of the blocks. Memory for one
   // dummy block is allocated because index zero is reserved to indicate a
   // null block.
   //
   // For aAllocate==10 blocks will range 0,1,2,3,4,5,6,7,8,9,10
   // An index of zero is reserved for null index, so block 0 is unused.
   // So usable blocks will range 1,2,3,4,5,6,7,8,9,10
   //
   // An index stack is used to manage free list access to the blocks
   // The stack is initialized for a free list by pushing indices onto it.
   // For aAllocate==10 this will push 10,9,8,7,6,5,4,3,2,1

   void initializeLongTerm(int aAllocate,int aBlockSize)
   {
      // Set the block pool type
      mBlockPoolType = BlockPoolType_LongTerm;

      // Set the number of blocks to allocate.
      mAllocate = aAllocate;

      // Allocate memory for the block array.
      // For aAllocate==10 blocks will range 0,1,2,3,4,5,6,7,8,9,10
      // An index of zero is reserved for null index, so block 0 is unused.
      // So usable blocks will range 1,2,3,4,5,6,7,8,9,10
      mBlocks.initialize(mAllocate + 1,aBlockSize);

      // Initialize the pointer stack
      mLongTermIndexStack.initialize(mAllocate);

      // Push the indices of the blocks in the array onto the index stack.
      // For aAllocate==10 this will push 10,9,8,7,6,5,4,3,2,1
      for (int i = mAllocate; i >= 1; i--)
      {
         mLongTermIndexStack.push(i);
      }
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Get a block from the pool, this allocates a block. If the block pool is 
   // short term, it gets a pointer from the circular array of pointers and 
   // advances the index into the array. If the block pool is long term, it 
   // pops a pointer from the pointer stack.

   TreeBlockClass* get()
   {
      // If this pool is short term
      if (mBlockPoolType == BlockPoolType_ShortTerm)
      {
         // Update counter.
         mShortTermCount++;

         // Advance the block index, circularly.
         // An index of zero is reserved for null index.
         // For aAllocate==10 the indices will range 1,2,3,4,5,6,7,8,9.
         if (++mShortTermIndex==mAllocate) mShortTermIndex = 1;

         // Return a pointer to a block, circularly.
         return (TreeBlockClass*)mBlocks.e(mShortTermIndex);
      }
      // Else if this pool is long term
      else if (mBlockPoolType == BlockPoolType_LongTerm)
      {
         // Pop a block index from the index stack
         int tBlockIndex = mLongTermIndexStack.pop();
         // Guard for stack empty
         if (tBlockIndex == 0)
         {
            printf("TreeBlockPool STACK EMPTY\n");
            return 0;
         }
         // Get a pointer to the block at that index
         TreeBlockClass* tBlockPointer = (TreeBlockClass*)mBlocks.e(tBlockIndex);
         // Set block variables
         tBlockPointer->mBlockIndex = tBlockIndex;
         // Return the pointer to the block
         return tBlockPointer;
      }
      // Else error
      else
      {
         return 0;
      }
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Put a block back to the pool, this deallocates a block. If the block pool
   // is short term, it does nothing. If the block pool is long term, it pushes
   // the pointer back onto the pointer stack.

   void put(TreeBlockClass* aBlockPointer)
   {
      // If this pool is short term
      if (mBlockPoolType == BlockPoolType_ShortTerm)
      {
         // Update counter.
         mShortTermCount--;
      }
      // Else if this pool is long term
      else if (mBlockPoolType == BlockPoolType_LongTerm)
      {
         // Push the block index back onto the stack
         mLongTermIndexStack.push(aBlockPointer->mBlockIndex);
      }
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members

   // This allocates storage for the blocks on the system heap and provides
   // pointer access to the allocated blocks.
   BlockArray mBlocks;

   // This is the number of blocks allocated.
   int mAllocate;

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

   int mShortTermIndex;
   int mShortTermCount;

   // This is a stack of pointers. This is used if the block pool has long
   // term blocks. It is a stack of pointers into the above allocated memory
   // block array. To allocate a block, a pointer is popped off of the stack.
   // To free a block, a pointer is pushed back onto the stack. To deallocate
   // a block, a pointer is pushed back onto the stack. Pushes and Pops are
   // locked with critical sections, making tehm thread safe.

   ValueStack<int> mLongTermIndexStack;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Helpers

   void show()
   {
      int tCount = 0;

      if (mBlockPoolType == BlockPoolType_ShortTerm)
      {
         tCount = mShortTermCount;
      }
      else if (mBlockPoolType == BlockPoolType_LongTerm)
      {
         tCount = mLongTermIndexStack.mCount;
      }

      printf("BlockPool Count %d\n", tCount);
   }

};

//******************************************************************************

}//namespace
#endif


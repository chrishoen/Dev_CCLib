#ifndef _CCLFBLOCKFREELIST_H_
#define _CCLFBLOCKFREELIST_H_
/*==============================================================================

Lock Free Block Free List. 

This implements a fixed size free list. The free list is thread safe. It uses
atomic compare and exchanges to guard against concurrency contentions.
It implements the Trieber algorithm with no backoff.

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

class LFBlockFreeList
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   LFBlockFreeList();
  ~LFBlockFreeList();

   // Allocate memory for the free list arrays and initialize the free list
   // member variables. aAllocate is the number of blocks to allocate
   // memory for. aBlockSize is the size of a block.

   void initialize(int aAllocate,int aBlockSize);

   // Deallocate memory.
   void finalize();

   // Free list size
   int  size();

   // Return a pointer to a block, based on its block index.
  
   void* element(int aIndex);


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue and Free List Members

   // Number of values allocated
   int mBlockSize;
   int mListAllocate;

   // Pointer to allocated block memory
   void* mMemory;

   // Free List array and variables
   AtomicLFIndex*    mListNext;
   AtomicLFIndex     mListHead;
   std::atomic<int>  mListSize;
   
   std::atomic<int>* mListHeadIndexPtr = (std::atomic<int>*)&mListHead;

   static const int  cInvalid = 0x80000000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   BaseLFBlock* listPop  ();
   bool         listPush (BaseLFBlock* aBlock);
};

//******************************************************************************

}//namespace
#endif


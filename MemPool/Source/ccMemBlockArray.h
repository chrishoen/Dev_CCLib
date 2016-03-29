#ifndef _CCMEMBLOCKARRAY_H_
#define _CCMEMBLOCKARRAY_H_
/*==============================================================================

This defines an array of memory blocks that are dynamically allocated. It 
provides an initialization method that allocates the blocks and it provides
an indexing method that is used to access the blocks.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an array of memory blocks that are dynamically
// allocated at initialization.

class MemBlockArray
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   MemBlockArray();
  ~MemBlockArray();

   // Allocate memory for the block array. It is passed the number of blocks to 
   // allocate and the size of the blocks.
   void initialize(int aAllocate,int aBlockSize);

   // Return a pointer to a block, based on its block index.
   char* e(int aIndex);


   //---------------------------------------------------------------------------
   // Members

   // Pointer to allocated memory
   char* mMemory;

   // Number of blocks allocated
   int mAllocate;

   // Size of each block allocated
   int mBlockSize;
};

//******************************************************************************

}//namespace
#endif


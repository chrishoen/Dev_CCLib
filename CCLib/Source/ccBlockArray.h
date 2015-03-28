#ifndef _BLOCKARRAY_H_
#define _BLOCKARRAY_H_
/*==============================================================================

This defines an array of memory blocks that are dynamically allocated.

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

class BlockArray
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   BlockArray();
  ~BlockArray();

   // Allocate memory for the block array.
   void initialize(int aAllocate,int aBlockSize);

   // Return a pointer to a block, based on block index
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


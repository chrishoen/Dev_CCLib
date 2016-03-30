#ifndef _CCBLOCBOXKARRAY_H_
#define _CCBLOCBOXKARRAY_H_
/*==============================================================================

This defines an array of memory blocks that are dynamically allocated. It 
provides an initialization method that allocates the blocks and it provides
an indexing method that is used to access the blocks.

A block box contains a block header and a block.

==============================================================================*/

#include "ccBlockHandle.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a header that is placed at the start of every block that is 
// allocated from the block array.

typedef struct BlockHeader
{
   // Unique memory handle for a block.
   BlockHandle mBlockHandle;
} BlockHeader;

// This structure must not take up more than sixteen bytes.
static const int cHeaderSize = 16;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an array of memory blocks that are dynamically
// allocated at initialization.

class BlockBoxArray
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   BlockBoxArray();
  ~BlockBoxArray();

   // Allocate memory for the block box array. It is passed the number of blocks
   // to allocate, the size of the block body, and the memory pool index for the
   // block box array.
   void initialize(int aNumBlocks,int aBlockSize,int aPoolIndex);

   // Deallocate memory for the block array.
   void finalize();

   // Return a pointer to a block box, based on its block index.
   char* blockBox(int aIndex);

   // Return a pointer to a block header, based on its block index.
   BlockHeader* header(int aIndex);

   // Return a pointer to a block body, based on its block index.
   char* block(int aIndex);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members

   // Number of blocks allocated.
   int mNumBlocks;

   // Size of each block allocated.
   int mBlockSize;

   // Size of each block body.
   int mHeaderSize;

   // Size of each block box allocated.
   int mBlockBoxSize;

   // Memory pool index for the block box array.
   int mPoolIndex;

   // Pointer to allocated memory for the block box.
   char* mMemory;
};

//******************************************************************************

}//namespace
#endif


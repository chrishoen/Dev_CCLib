#ifndef _CCBLOCKPOOLPARMS_H_
#define _CCBLOCKPOOLPARMS_H_

/*==============================================================================
Block pool parameter class
==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Block pool constants.

   // Block pool types.
   static const int cBlockPoolType_FreeList   = 1;
   static const int cBlockPoolType_LFFreeList = 2;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Block pool parameters. These are passed to the create block pool call.

class BlockPoolParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters that are passed to the create block pool call.

   // Unique index for the block pool.
   int   mPoolIndex;

   // Type of block pool.
   int   mBlockPoolType;

   // Number of blocks to allocate.
   int   mNumBlocks;

   // Block size in bytes.
   int   mBlockSize;

   // Pointer to external memory allocated for the entire block pool.
   // If this is null then system heap memory is allocated for the entire
   // block pool.
   void* mMemory;

   // If true then constructors are called for all internal objects created
   // for the block pool. If false then the constructors are not called.
   // This is false if the block pool resides in shared memory and has
   // already been created. This is true otherwise.
   bool mConstructorFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters that are used internally to the block pool.

   // True if block pool has been created.
   bool  mValidFlag;

   // True if these are the original parameters that were passed in at block
   // pool creation. False if this is a copy of the original parameters. If
   // this is false and these parameters reside in shared memory then none of
   // the pointer parameters are valid.
   bool  mOriginalFlag;

   // Block box size in bytes.
   int   mBlockBoxSize;

   // Block header size in bytes.
   int   mBlockHeaderSize;

   // This contains the address of the first block box in the block box array.
   // It can be used to obtain the address of a block header or a block body.
   void* mBlockArrayPtr;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   BlockPoolParms();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize();
};

}//namespace
#endif


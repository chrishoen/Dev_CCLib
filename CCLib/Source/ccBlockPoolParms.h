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
// Block pool parameters. These are passed to the create block pool call.

class BlockPoolParms
{
public:

   //--------------------------------------------------------------------------
   // Parameters
   
   bool  mValidFlag;        // True if block pool has been created.
   int   mPoolIndex;        // Unique index for the block pool.
   int   mBlockPoolType;    // Type of block pool.
   int   mNumBlocks;        // Number of blocks to allocate.
   int   mBlockSize;        // Block size in bytes.

   //--------------------------------------------------------------------------
   // Constructors

   BlockPoolParms();
   void reset();
};

}//namespace
#endif


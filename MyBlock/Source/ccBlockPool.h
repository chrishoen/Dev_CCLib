#ifndef _CCBLOCKPOOL_H_
#define _CCBLOCKPOOL_H_

/*==============================================================================
==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccBlockHandle.h"

namespace CC
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   void resetBlockPool       ();

   void addBlockPool(int aNumBlocks,int aBlockSize,int aPoolIndex);

   void initializeBlockPool  ();
   void finalizeBlockPool    ();

   
   void allocateBlockPoolBlock(int aPoolIndex,void** aBlockPointer,BlockHandle* aBlockHandle);
   void deallocateBlockPoolBlock(BlockHandle aBlockHandle);

   void showBlockPool(int aPoolIndex);

   void* getBlockPoolBlockPtr(BlockHandle aBlockHandle);

}//namespace
#endif


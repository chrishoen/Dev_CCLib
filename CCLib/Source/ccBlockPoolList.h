#ifndef _CCBLOCKPOOLLIST_H_
#define _CCBLOCKPOOLLIST_H_

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

   void resetBlockPoolList();

   void addToBlockPoolList(int aNumBlocks,int aBlockSize,int aPoolIndex);

   void initializeBlockPoolList();
   void finalizeBlockPoollist();

   
   void allocateBlockPoolBlock(int aPoolIndex,void** aBlockPointer,BlockHandle* aBlockHandle);
   void deallocateBlockPoolBlock(BlockHandle aBlockHandle);

   void showBlockPool(int aPoolIndex);

   void* getBlockPoolBlockPtr(BlockHandle aBlockHandle);

}//namespace
#endif


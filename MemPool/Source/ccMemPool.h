#ifndef _CCMEMPOOL_H_
#define _CCMEMPOOL_H_

/*==============================================================================
==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccMemHandle.h"

namespace CC
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   void resetMemPool       ();

   void addBlockPool(int aNumBlocks,int aBlockSize,int aMemPoolIndex);

   void initializeMemPool  ();
   void finalizeMemPool    ();

   
   void getMemPoolBlock(int aMemPoolIndex,void** aBlockPointer,MemHandle* aMemHandle);
   void putMemPoolBlock(MemHandle aMemHandle);

   void showMemPool(int aMemPoolIndex);

}//namespace
#endif


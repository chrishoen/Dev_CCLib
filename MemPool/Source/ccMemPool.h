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

   HasMemHandle* getMemPoolBlock(int aMemPoolIndex);
   void putMemPoolBlock(HasMemHandle* aBlockPointer);

   void showMemPool(int aMemPoolIndex);

}//namespace
#endif


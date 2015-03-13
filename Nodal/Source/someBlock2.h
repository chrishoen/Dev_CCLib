#ifndef _SOMEBLOCK2_H_
#define _SOMEBLOCK2_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccDefs.h"
#include "ccBlockUniverse.h"

namespace Some
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class  Block2A
{
public:

   Block2A();
  ~Block2A();

   static  Block2A*  create(int aMemoryType=0);
   virtual void      destroy();

   static CC::BlockUniverse mBlockUniverse;

   static void initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks);

   int mMemoryType;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class  Block2B : public Block2A
{
public:

   Block2B();
  ~Block2B();

   static  Block2B*  create(int aMemoryType=0);
   virtual void      destroy();

   static CC::BlockUniverse mBlockUniverse;

   static void initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks);
};

//******************************************************************************
}//namespace

#endif


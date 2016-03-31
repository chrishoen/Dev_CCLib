#ifndef _SOMEMYBLOCKB_H_
#define _SOMEMYBLOCKB_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "ccBlockHandle.h"
#include "ccBlockPoolBlock.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockA.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

//class MyBlockB : public CC::HasBlockHandle, public CC::BlockPoolBlock<Some::MyBlockB,Some::cBlockPoolIndex_MyBlockB>
class MyBlockB : public Some::MyBlockA, public CC::BlockPoolBlock<Some::MyBlockB,Some::cBlockPoolIndex_MyBlockB>
{
public:

   MyBlockB();
  ~MyBlockB();

   void method1B();

   int mCode1B;
};

//******************************************************************************
}//namespace

#endif


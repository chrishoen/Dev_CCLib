/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <new>
#include "prnPrint.h"

#include "ccBlockPoolCentral.h"
#include "someBlockPoolIndex.h"
#include "someMyTreeBlock.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Default Constructor.

MyTreeBlock::MyTreeBlock()
{
   mIdentifier = 0;
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

MyTreeBlock::MyTreeBlock(int aIdentifier)
{
   mIdentifier = aIdentifier;
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void MyTreeBlock::method1A()
{
   Prn::print(0, "MyTreeBlock::method1A %d",mCode1);
}

}//namespace
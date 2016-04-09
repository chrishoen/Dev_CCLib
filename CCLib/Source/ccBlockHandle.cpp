/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "ccBlockPoolCentral.h"
#include "ccBlockHandle.h"

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Static variable instance

CC::BlockHandle CC::BlockHandle::nullH;

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructors.

BlockHandle::BlockHandle()
{
   mPoolIndex  = cInvalid;
   mBlockIndex = cInvalid;
}

BlockHandle::BlockHandle(unsigned short aPoolIndex, unsigned short aBlockIndex)
{
   mPoolIndex  = aPoolIndex;
   mBlockIndex = aBlockIndex;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Set null.

void BlockHandle::setNull()
{
   mPoolIndex  = cInvalid;
   mBlockIndex = cInvalid;
}

void BlockHandle::set(unsigned short aPoolIndex, unsigned short aBlockIndex)
{
   mPoolIndex  = aPoolIndex;
   mBlockIndex = aBlockIndex;
}

bool BlockHandle::isNull()
{
   return mPoolIndex==cInvalid || mBlockIndex==cInvalid;
}

BlockHandle  BlockHandle::null()
{
   BlockHandle tTemp;
   tTemp.setNull();
   return tTemp;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set a block handle from the given address of the block. This obtains the 
// block handle by looking it up in the global block pool facility.

void BlockHandle::set(void* aBlockPointer)
{
   *this = getBlockPoolBlockHandle(aBlockPointer);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Get the address of the block specified by the block handle. This obtains 
// the handle by looking it up in the global block pool facility.

void* BlockHandle::ptr(BlockHandle aBlockHandle)
{
   return getBlockPoolBlockPtr(aBlockHandle);
}

} //namespace


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
// Get a pointer from a block handle.

void* BlockHandle::ptr(BlockHandle aBlockHandle)
{
   return getBlockPoolBlockPtr(aBlockHandle);
}

} //namespace


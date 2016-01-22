/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "LFIntQueue.h"

#define  _SOMESHARE_CPP_
#include "someShare.h"
namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Share::Share()
{
   initialize();
}

void Share::initialize()
{
   LFIntQueue::initialize(10000);
   mWriter.initialize(0);
   mReader.initialize();
}

}//namespace

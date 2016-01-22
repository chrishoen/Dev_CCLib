/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"

#include "LFIntQueue.h"
#include "GSettings.h"

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
   LFIntQueue::initialize(gGSettings.mAllocate);
   mWriter.initialize(0);
   mReader.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Share::update()
{
   mWriterPassCount = mWriter.mPassCount;
   mWriterFailCount = mWriter.mFailCount;
   mWriterCodeSum   = mWriter.mCodeSum;

   mReaderPassCount = mReader.mPassCount;
   mReaderFailCount = mReader.mFailCount;
   mReaderCodeSum   = mReader.mCodeSum;
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Share::show()
{
   Prn::print(0,"TOTAL");
   Prn::print(0,"");
   Prn::print(0,"Writer.mPassCount %llu",mWriterPassCount);
   Prn::print(0,"Writer.mFailCount %llu",mWriterFailCount);
   Prn::print(0,"Writer.mCodeSum   %llu",mWriterCodeSum);
   Prn::print(0,"");
   Prn::print(0,"Reader.mPassCount %llu",mReaderPassCount);
   Prn::print(0,"Reader.mFailCount %llu",mReaderFailCount);
   Prn::print(0,"Reader.mCodeSum   %llu",mReaderCodeSum);
   Prn::print(0,"");
}
  
}//namespace

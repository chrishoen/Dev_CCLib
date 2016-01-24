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

   mNumWriters = gGSettings.mNumWriters;
   if (mNumWriters > cMaxNumWriters) mNumWriters = cMaxNumWriters;

   for (int i = 0; i < mNumWriters; i++)
   {
      mWriter[i].initialize(i);
   }

   mReader.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Share::update()
{
   mWriterPassCount = 0;
   mWriterFailCount = 0;
   mWriterCodeSum   = 0;

   for (int i = 0; i < mNumWriters; i++)
   {
      mWriterPassCount += mWriter[i].mPassCount;
      mWriterFailCount += mWriter[i].mFailCount;
      mWriterCodeSum   += mWriter[i].mCodeSum;
   }

   mReaderPassCount = mReader.mPassCount;
   mReaderFailCount = mReader.mFailCount;
   mReaderCodeSum   = mReader.mCodeSum;
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Share::show()
{
   Prn::print(0,"");
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
   LFIntQueue::show();
}
  
}//namespace

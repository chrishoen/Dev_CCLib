/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"

#include "LFIntQueue.h"
#include "LFFreeList.h"
#include "RisIntQueue.h"
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
   mMode = gGSettings.mMode;

   switch (mMode)
   {
   case 1:
      LFIntQueue::initialize(gGSettings.mAllocate);
      break;
   case 2:
      RisIntQueue::initialize(gGSettings.mAllocate);
      break;
   case 8:
      LFFreeList::initialize(gGSettings.mAllocate);
      LFFreeList::initializeTest(gGSettings.mTest);
      break;
   case 9:
      LFIntQueue::initialize(gGSettings.mAllocate);
      LFIntQueue::initializeTest(gGSettings.mTest);
      break;
   }

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
   mWriterCount     = 0;
   mWriterPassCount = 0;
   mWriterFailCount = 0;
   mWriterCodeSum   = 0;
   mWriterMeanTime  = 0.0;

   for (int i = 0; i < mNumWriters; i++)
   {
      mWriterCount     += mWriter[i].mCount;
      mWriterPassCount += mWriter[i].mPassCount;
      mWriterFailCount += mWriter[i].mFailCount;
      mWriterCodeSum   += mWriter[i].mCodeSum;
      mWriterMeanTime  += mWriter[i].mMeanTime/mNumWriters;
   }

   mReaderCount     = mReader.mCount;
   mReaderPassCount = mReader.mPassCount;
   mReaderFailCount = mReader.mFailCount;
   mReaderCodeSum   = mReader.mCodeSum;
   mReaderMeanTime  = mReader.mMeanTime;
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Share::show()
{
   Prn::print(0,"");
   Prn::print(0,"TOTAL");
   Prn::print(0,"");
   Prn::print(0,"Writer.mCount     %llu",  mWriterCount);
   Prn::print(0,"Writer.mPassCount %llu",  mWriterPassCount);
   Prn::print(0,"Writer.mFailCount %llu",  mWriterFailCount);
   Prn::print(0,"Writer.mCodeSum   %llu",  mWriterCodeSum);
   Prn::print(0,"Writer.mMeanTime  %4.3f", mWriterMeanTime);
   Prn::print(0,"");
   Prn::print(0,"Reader.mCount     %llu",  mReaderCount);
   Prn::print(0,"Reader.mPassCount %llu",  mReaderPassCount);
   Prn::print(0,"Reader.mFailCount %llu",  mReaderFailCount);
   Prn::print(0,"Reader.mCodeSum   %llu",  mReaderCodeSum);
   Prn::print(0,"Reader.mMeanTime  %4.3f", mReaderMeanTime);
   Prn::print(0,"");

   switch (mMode)
   {
   case 1: LFIntQueue::show(); return;
   case 2: return;
   case 8: LFFreeList::show(); return;
   case 9: LFIntQueue::show(); return;
   }
}
  
}//namespace

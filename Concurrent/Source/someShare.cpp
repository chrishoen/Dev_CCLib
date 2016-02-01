/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "my_functions.h"
#include "prnPrint.h"

#include "LFIntQueue.h"
#include "LFFreeList.h"
#include "LFBackoff.h"
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
   mTerminateFlag = false;


   switch (mMode)
   {
   case 1:
      LFIntQueue::initialize(gGSettings.mAllocate);
      LFBackoff::initialize(gGSettings.mBackoff1,gGSettings.mBackoff2);
      break;
   case 2:
      RisIntQueue::initialize(gGSettings.mAllocate);
      break;
   case 8:
      LFFreeList::initialize(gGSettings.mAllocate);
      LFFreeList::initializeTest(gGSettings.mTest);
      LFBackoff::initialize(gGSettings.mBackoff1,gGSettings.mBackoff2);
      break;
   case 9:
      LFIntQueue::initialize(gGSettings.mAllocate);
      LFIntQueue::initializeTest(gGSettings.mTest);
      LFBackoff::initialize(gGSettings.mBackoff1,gGSettings.mBackoff2);
      break;
   }

   mNumWriters = gGSettings.mNumWriters;
   if (mNumWriters > cMaxNumWriters) mNumWriters = cMaxNumWriters;

   for (int i = 0; i < mNumWriters; i++)
   {
      mWriter[i].initialize(i);
      mWriterProc[i]=0;
   }

   mReader.initialize();
   mReaderProc=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Share::update()
{
   mWriterCount     = 0;
   mWriterPassCount = 0;
   mWriterFailCount = 0;
   mWriterCheckSum  = 0;
   mWriterMeanTime  = 0.0;
   mWriterXMeanTime = 0.0;

   for (int i = 0; i < mNumWriters; i++)
   {
      mWriterCount     += mWriter[i].mCount;
      mWriterPassCount += mWriter[i].mPassCount;
      mWriterFailCount += mWriter[i].mFailCount;
      mWriterCheckSum  += mWriter[i].mCheckSum;
      mWriterMeanTime  += mWriter[i].mMeanTime/mNumWriters;
   }

   mReaderCount     = mReader.mCount;
   mReaderPassCount = mReader.mPassCount;
   mReaderFailCount = mReader.mFailCount;
   mReaderCheckSum  = mReader.mCheckSum;
   mReaderMeanTime  = mReader.mMeanTime;
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************
void Share::show()
{
   char tString[40];


   if (mMode < 8)
   {
      Prn::print(0, "");
      Prn::print(0, "");
      Prn::print(0, "");
      Prn::print(0, "TOTAL");
      Prn::print(0, "");
      Prn::print(0, "Writer.mCheckSum   %16llu", mWriterCheckSum);
      Prn::print(0, "Reader.mCheckSum   %16llu", mReaderCheckSum);
      Prn::print(0, "");
      Prn::print(0, "Writer.mCount      %16s", my_stringLLU(tString, mWriterCount));
      Prn::print(0, "Writer.mPassCount  %16s", my_stringLLU(tString, mWriterPassCount));
      Prn::print(0, "Writer.mFailCount  %16s", my_stringLLU(tString, mWriterFailCount));
      Prn::print(0, "");
      Prn::print(0, "Reader.mCount      %16s", my_stringLLU(tString, mReaderCount));
      Prn::print(0, "Reader.mPassCount  %16s", my_stringLLU(tString, mReaderPassCount));
      Prn::print(0, "Reader.mFailCount  %16s", my_stringLLU(tString, mReaderFailCount));
      Prn::print(0, "");
   }
   else
   {
      Prn::print(0, "");
      Prn::print(0, "");
      Prn::print(0, "");
      Prn::print(0, "TOTAL");
      Prn::print(0, "");
      Prn::print(0, "Writer.mCount      %16s", my_stringLLU(tString, mWriterCount));
      Prn::print(0, "Writer.mPassCount  %16s", my_stringLLU(tString, mWriterPassCount));
      Prn::print(0, "Writer.mFailCount  %16s", my_stringLLU(tString, mWriterFailCount));
      Prn::print(0, "");
   }


   switch (mMode)
   {
   case 1: LFIntQueue::show(); break;
   case 2: break;
   case 8: LFFreeList::show(); break;
   case 9: LFIntQueue::show(); break;
   }

   if (mMode < 8)
   {
      Prn::print(0, "");
      Prn::print(0, "Writer.mMeanTime   %16.5f", mWriterMeanTime);
      Prn::print(0, "Reader.mMeanTime   %16.5f", mReaderMeanTime);
      Prn::print(0, "mMeanTime          %16.5f", mReaderMeanTime + mWriterMeanTime);
   }
   else
   {
      Prn::print(0, "");
      Prn::print(0, "Writer.mMeanTime   %16.5f", mWriterMeanTime);
   }


   if (mMode < 8)
   {
      double tWriterPass = (double)mWriterPassCount / (double)mWriterCount;
      double tReaderPass = (double)mReaderPassCount / (double)mReaderCount;
      double tWriteRetry = (double)LFIntQueue::writeRetry() / (double)mWriterCount;
      double tReadRetry = (double)LFIntQueue::readRetry() / (double)mReaderCount;
      double tPopRetry = (double)LFIntQueue::popRetry() / (double)mWriterPassCount;
      double tPushRetry = (double)LFIntQueue::pushRetry() / (double)mReaderPassCount;

      Prn::print(0, "");
      Prn::print(0, "WriterPass         %16.5f", tWriterPass);
      Prn::print(0, "ReaderPass         %16.5f", tReaderPass);
      Prn::print(0, "writeRetry         %16.5f", tWriteRetry);
      Prn::print(0, "readRetry          %16.5f", tReadRetry);
      Prn::print(0, "popRetry           %16.5f", tPopRetry);
      Prn::print(0, "pushRetry          %16.5f", tPushRetry);
   }
   else if (mMode == 8)
   {
      double tPopRetry = (double)LFFreeList::popRetry() / (double)mWriterCount;
      double tPushRetry = (double)LFFreeList::pushRetry() / (double)mWriterPassCount;

      Prn::print(0, "");
      Prn::print(0, "popRetry           %16.5f", tPopRetry);
      Prn::print(0, "pushRetry          %16.5f", tPushRetry);
   }
   else if (mMode == 9)
   {
      double tPopRetry = (double)LFIntQueue::popRetry() / (double)mWriterCount;
      double tPushRetry = (double)LFIntQueue::pushRetry() / (double)mWriterPassCount;

      Prn::print(0, "");
      Prn::print(0, "popRetry           %16.5f", tPopRetry);
      Prn::print(0, "pushRetry          %16.5f", tPushRetry);
   }

}
  
}//namespace

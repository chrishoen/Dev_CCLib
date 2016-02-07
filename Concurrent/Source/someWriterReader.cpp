/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"
#include "my_functions.h"

#include "GSettings.h"
#include "LFBackoff.h"
#include "LFFreeList.h"
#include "LFIntQueue.h"
#include "someShare.h"
#include "someWriterReader.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

WriterReader::WriterReader()
{
   initialize();
}

void WriterReader::initialize(unsigned aIdent)
{
   mIdent = aIdent;
   mMsg.mCode  = 0;
   mMsg.mIdent = aIdent;

   mWriteCount     = 0;
   mWritePassCount = 0;
   mWriteFailCount = 0;
   mWriteCheckSum   = 0;
   mReadCount     = 0;
   mReadPassCount = 0;
   mReadFailCount = 0;
   mReadCheckSum   = 0;

   mMeanTimeWrite  = 0.0;
   mMeanTimeRead  = 0.0;
}

void WriterReader::finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::show()
{
   Prn::print(0,"WriterReader.mIdent      %d",  mIdent);
   Prn::print(0,"WriterReader.mWriteCount %llu",mWriteCount);
   Prn::print(0,"WriterReader.mReadCount  %llu",mReadCount);
   Prn::print(0,"");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::startTrial()
{
   if (mIdent == 0)
   {
      int tListSize = gGSettings.mAllocate;
      for (int i = 0; i < tListSize / 2; i++)
      {
         mMsg.mCode++;
         LFIntQueue::tryWrite(mMsg.mInt);

         mWriteCount++;
         mWritePassCount++;
         mWriteCheckSum += mMsg.mCode;
      }
   }

   mMarkerWrite.startTrial(gGSettings.mXLimit);
   mMarkerRead.startTrial(gGSettings.mXLimit);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::finishTrial()
{
   mMarkerWrite.finishTrial();
   mMarkerRead.finishTrial();

   mMeanTimeWrite = mMarkerWrite.mStatistics.mMean;
   mMeanTimeRead = mMarkerRead.mStatistics.mMean;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::writeread(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      // Write
      if (my_randflag(0.5))
      {
         bool tPass;
         mMsg.mCode++;

         mMarkerWrite.doStart();
         tPass = LFIntQueue::tryWrite(mMsg.mInt);
         mMarkerWrite.doStop();
         tDelayA.delay();

         if (tPass)
         {
            mWriteCount++;
            mWritePassCount++;
            mWriteCheckSum += mMsg.mCode;
         }
         else
         {
            mWriteCount++;
            mWriteFailCount++;
         }
      }
      // Read
      else
      {
         bool tPass;
         IntMessage tMsg;

         mMarkerRead.doStart();
         tPass = LFIntQueue::tryRead(&tMsg.mInt);
         mMarkerRead.doStop();
         tDelayA.delay();

         if (tPass)
         {
            mReadCount++;
            mReadPassCount++;
            mReadCheckSum += tMsg.mCode;
         }
         else
         {
            mReadCount++;
            mReadFailCount++;
         }
         mMarkerRead.doStop();
      }
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::flush()
{
   while(true)
   {
      IntMessage tMsg;
      if (!LFIntQueue::tryRead(&tMsg.mInt)) break;
      mReadCount++;
      mReadPassCount++;
      mReadCheckSum += tMsg.mCode;
   }
}
   


   
}//namespace
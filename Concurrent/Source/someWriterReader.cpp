/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"
#include "my_functions.h"

#include "GSettings.h"
#include "LFDelay.h"
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
   mCode = 0;

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
      int tListSize = LFIntQueue::listSize();
      for (int i = 0; i < tListSize / 2; i++)
      {
         mCode++;
         IntMessage tMsg(mIdent, mCode);
         LFIntQueue::tryWrite(tMsg.aint());

         mWriteCount++;
         mWritePassCount++;
         mWriteCheckSum += mCode;
      }
   }

   mMarkerWrite.startTrial(gGSettings.mXLimit);
   mMarkerRead.startTrial(gGSettings.mXLimit);
}

void WriterReader::finishTrial()
{
   mMarkerWrite.finishTrial();
   mMarkerRead.finishTrial();

   mMeanTimeWrite = mMarkerWrite.mStatistics.mMean;
   mMeanTimeRead = mMarkerRead.mStatistics.mMean;
}

void WriterReader::writeread(int aNumWrites)
{
   for (int i = 0; i < aNumWrites; i++)
   {
      // Write
      if (my_randflag(0.5))
      {
         bool tPass;
         mCode++;
         IntMessage tMsg(mIdent, mCode);

         mMarkerWrite.doStart();
         tPass = LFIntQueue::tryWrite(tMsg.aint());
         mMarkerWrite.doStop();
         LFDelay::delay(gGSettings.mDelayWrite);

         if (tPass)
         {
            mWriteCount++;
            mWritePassCount++;
            mWriteCheckSum += mCode;
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
         tPass = LFIntQueue::tryRead(&tMsg.aint());
         mMarkerRead.doStop();
         LFDelay::delay(gGSettings.mDelayRead);

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
   


   
}//namespace
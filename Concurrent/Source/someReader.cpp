/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <prnPrint.h>

#include "GSettings.h"
#include "someShare.h"
#include "LFBackoff.h"
#include "LFIntQueue.h"
#include "RisIntQueue.h"
#include "someReader.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Reader::Reader()
{
   initialize();
}

void Reader::initialize()
{
   mCount     = 0;
   mPassCount = 0;
   mFailCount = 0;
   mCheckSum   = 0;
   mMeanTimeRead  = 0.0;
}

void Reader::finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::show()
{
   Prn::print(0,"Reader.mCount     %llu",mCount);
   return;
   Prn::print(0,"Reader.mPassCount %llu",mPassCount);
   Prn::print(0,"Reader.mFailCount %llu",mFailCount);
   Prn::print(0,"Reader.mCheckSum   %llu",mCheckSum);
   Prn::print(0,"");
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::read1(int aNumReads)
{
   for (int i = 0; i < aNumReads; i++)
   {
      bool tPass;
      IntMessage tMsg;

      mMarkerRead.doStart();
      tPass = LFIntQueue::tryRead(&tMsg.aint());
      mMarkerRead.doStop();
      LFBackoff::delay(gGSettings.mDelayRead);

      if (tPass)
      {
         mPassCount++;
         mCheckSum += tMsg.mCode;
      }
      else
      {
         mFailCount++;
      }
      mMarkerRead.doStop();
   }
}
   
void Reader::flush1()
{
   while(true)
   {
      IntMessage tMsg;
      if (!LFIntQueue::tryRead(&tMsg.aint())) break;
      mPassCount++;
      mCheckSum += tMsg.mCode;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::read2(int aNumReads)
{
   for (int i = 0; i < aNumReads; i++)
   {
      bool tPass;
      IntMessage tMsg;

      mMarkerRead.doStart();
      tPass = RisIntQueue::tryRead(&tMsg.aint());
      LFBackoff::delay(gGSettings.mDelayRead);

      if (tPass)
      {
         mPassCount++;
         mCheckSum += tMsg.mCode;
      }
      else
      {
         mFailCount++;
      }
      mMarkerRead.doStop();
   }
}
   
void Reader::flush2()
{
   while(true)
   {
      IntMessage tMsg;
      if (!RisIntQueue::tryRead(&tMsg.aint())) break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::startTrial()
{
   mMarkerRead.startTrial(gGSettings.mXLimit);

}
void Reader::finishTrial()
{
   mMarkerRead.finishTrial();

   mMeanTimeRead = mMarkerRead.mStatistics.mMean;

   mCount = mPassCount + mFailCount;
}

void Reader::read(int aNumReads)
{
   mMarkerRead.startTrial(gGSettings.mXLimit);

   switch (gShare.mMode)
   {
   case 1: read1(aNumReads); break;
   case 2: read2(aNumReads); break;
   }

   mCount = mPassCount + mFailCount;
   mMarkerRead.finishTrial();
   mMeanTimeRead = mMarkerRead.mStatistics.mMean;
}
   
void Reader::flush()
{
   switch (gShare.mMode)
   {
   case 1: flush1(); break;
   case 2: flush2(); break;
   }
}
   
}//namespace
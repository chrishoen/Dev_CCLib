/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <prnPrint.h>

#include "GSettings.h"
#include "LFBackoff.h"
#include "LFFreeList.h"
#include "LFIntQueue.h"
#include "RisIntQueue.h"
#include "someShare.h"
#include "someWriter.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Writer::Writer()
{
   initialize();
}

void Writer::initialize(unsigned aIdent)
{
   mIdent = aIdent;
   mCode = 0;

   mCount     = 0;
   mPassCount = 0;
   mFailCount = 0;
   mCheckSum   = 0;
   mMeanTimeWrite  = 0.0;
   mMeanTimePop  = 0.0;
   mMeanTimePush  = 0.0;
}

void Writer::finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::show()
{
   Prn::print(0,"Writer.mIdent     %d",  mIdent);
   Prn::print(0,"Writer.mCount     %llu",mCount);
   return;
   Prn::print(0,"Writer.mPassCount %llu",mPassCount);
   Prn::print(0,"Writer.mFailCount %llu",mFailCount);
   Prn::print(0,"Writer.mCheckSum   %llu",mCheckSum);
   Prn::print(0,"");
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::write1(int aNumWrites)
{
   for (int i = 0; i < aNumWrites; i++)
   {
      bool tPass;
      mCode++;
      IntMessage tMsg(mIdent,mCode);

      mMarkerWrite.doStart();
      tPass = LFIntQueue::tryWrite(tMsg.aint());
      mMarkerWrite.doStop();
      LFBackoff::delay(gGSettings.mDelayWrite);

      if (tPass)
      {
         mCount++;
         mPassCount++;
         mCheckSum += mCode;
      }
      else
      {
         mCount++;
         mFailCount++;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::write2(int aNumWrites)
{
   for (int i = 0; i < aNumWrites; i++)
   {
      bool tPass;
      mCode++;
      IntMessage tMsg(mIdent,mCode);

      mMarkerWrite.doStart();
      tPass = RisIntQueue::tryWrite(tMsg.aint());
      mMarkerWrite.doStop();
      LFBackoff::delay(gGSettings.mDelayWrite);

      if (tPass)
      {
         mPassCount++;
         mCheckSum += mCode;
      }
      else
      {
         mFailCount++;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::write8(int aNumWrites)
{
   for (int i = 0; i < aNumWrites; i++)
   {
      int tNode;
      bool tPass;

      mMarkerPop.doStart();
      tPass = LFFreeList::listPop(&tNode);
      mMarkerPop.doStop();
      LFBackoff::delay(gGSettings.mDelay1);

      if (tPass)
      {
         mMarkerPush.doStart();
         LFFreeList::listPush(tNode);
         mMarkerPush.doStop();
         LFBackoff::delay(gGSettings.mDelay1);
         mPassCount++;
      }
      else
      {
         mFailCount++;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::startTrial()
{
   mMarkerWrite.startTrial(gGSettings.mXLimit);
   mMarkerPop.startTrial(gGSettings.mXLimit);
   mMarkerPush.startTrial(gGSettings.mXLimit);

}
void Writer::finishTrial()
{
   mMarkerWrite.finishTrial();
   mMarkerPop.finishTrial();
   mMarkerPush.finishTrial();

   mMeanTimeWrite = mMarkerWrite.mStatistics.mMean;
   mMeanTimePop = mMarkerPop.mStatistics.mMean;
   mMeanTimePush = mMarkerPush.mStatistics.mMean;
}

void Writer::write(int aNumWrites)
{
   switch (gShare.mMode)
   {
   case 1: write1 (aNumWrites); break;
   case 2: write2 (aNumWrites); break;
   case 8: write8 (aNumWrites); break;
   }
}
   


   
}//namespace
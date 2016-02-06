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
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      bool tPass;
      mCode++;
      IntMessage tMsg(mIdent,mCode);

      mMarkerWrite.doStart();
      tPass = LFIntQueue::tryWrite(tMsg.aint());
      mMarkerWrite.doStop();
      tDelayA.delay();

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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::write8(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);
   LFBackoff tDelayB(gGSettings.mDelayB1,gGSettings.mDelayB2);

   // Free List pop,push
   if (gShare.mTest == 1)
   {
      for (int i = 0; i < aNumWrites; i++)
      {
         int tNode;
         bool tPass;

         mMarkerPop.doStart();
         tPass = LFFreeList::listPop(&tNode);
         mMarkerPop.doStop();
         tDelayA.delay();

         if (tPass)
         {
            mMarkerPush.doStart();
            LFFreeList::listPush(tNode);
            mMarkerPush.doStop();
            tDelayB.delay();

            mCount++;
            mPassCount++;
         }
         else
         {
            mCount++;
            mFailCount++;
         }
      }
   }
   // Free List stub
   else if (gShare.mTest == 2)
   {
      // Free List pop,push
      for (int i = 0; i < aNumWrites; i++)
      {
         mMarkerPop.doStart();
         LFFreeList::listStub();
         mMarkerPop.doStop();
         tDelayA.delay();

         mCount++;
         mPassCount++;
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
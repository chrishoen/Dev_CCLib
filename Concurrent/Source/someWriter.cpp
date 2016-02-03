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
   mMeanTime  = 0.0;
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
      mCode++;
      IntMessage tMsg(mIdent,mCode);

      mMarker.doStart();
      if (LFIntQueue::tryWrite(tMsg.aint()))
      {
         mPassCount++;
         mCheckSum += mCode;
      }
      else
      {
         mFailCount++;
      }
      mMarker.doStop();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::write2(int aNumWrites)
{
   for (int i = 0; i < aNumWrites; i++)
   {
      mCode++;
      IntMessage tMsg(mIdent,mCode);

      mMarker.doStart();
      if (RisIntQueue::tryWrite(tMsg.aint()))
      {
         mPassCount++;
         mCheckSum += mCode;
      }
      else
      {
         mFailCount++;
      }
      mMarker.doStop();
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
      LFBackoff::delay();

      if (tPass)
      {
         mMarkerPush.doStart();
         LFFreeList::listPush(tNode);
         mMarkerPush.doStop();
         LFBackoff::delay();
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

void Writer::write9(int aNumWrites)
{
   for (int i = 0; i < aNumWrites; i++)
   {
      mMarker.doStart();
      if (LFIntQueue::test())
      {
         mPassCount++;
      }
      else
      {
         mFailCount++;
      }
      mMarker.doStop();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::startTrial()
{
   mMarker.startTrial(gGSettings.mXLimit);
   mMarkerPop.startTrial(gGSettings.mXLimit);
   mMarkerPush.startTrial(gGSettings.mXLimit);

}
void Writer::finishTrial()
{
   mMarker.finishTrial();
   mMarkerPop.finishTrial();
   mMarkerPush.finishTrial();

   mMeanTime = mMarker.mStatistics.mMean;
   mMeanTimePop = mMarkerPop.mStatistics.mMean;
   mMeanTimePush = mMarkerPush.mStatistics.mMean;

   mCount = mPassCount + mFailCount;
}

void Writer::write(int aNumWrites)
{
   switch (gShare.mMode)
   {
   case 1: write1 (aNumWrites); break;
   case 2: write2 (aNumWrites); break;
   case 8: write8 (aNumWrites); break;
   case 9: write9 (aNumWrites); break;
   }

   mCount = mPassCount + mFailCount;
}
   


   
}//namespace
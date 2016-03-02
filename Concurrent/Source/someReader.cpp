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

void Reader::readType1(int aNumReads)
{
   LFBackoff tDelayB(gGSettings.mDelayB1,gGSettings.mDelayB2);

   for (int i = 0; i < aNumReads; i++)
   {
      bool tPass;
      int tCount;

      mMarkerRead.doStart();
      tPass = LFIntQueue::tryRead(&tCount);
      mMarkerRead.doStop();

      tDelayB.delay();

      if (tPass)
      {
         mCount++;
         mPassCount++;
         mCheckSum += tCount;
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

void Reader::readType2(int aNumReads)
{
   LFBackoff tDelayB(gGSettings.mDelayB1,gGSettings.mDelayB2);

   for (int i = 0; i < aNumReads; i++)
   {
      bool tPass;
      int tCount;

      mMarkerRead.doStart();
      Class1A* tObject = (Class1A*)gShare.mPointerQueue.readPtr();
      mMarkerRead.doStop();
      tDelayB.delay();

      tPass = tObject!=0;
      if (tObject)
      {
         tCount = tObject->mCode1;
         delete tObject;
      }

      if (tPass)
      {
         mCount++;
         mPassCount++;
         mCheckSum += tCount;
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

void Reader::readType3(int aNumReads)
{
   LFBackoff tDelayB(gGSettings.mDelayB1,gGSettings.mDelayB2);

   for (int i = 0; i < aNumReads; i++)
   {
      bool tPass;
      int tCount;
      int tIndex;

      mMarkerRead.doStart();

      Class1A* tObject = (Class1A*)gShare.mBlockQueue.startRead(&tIndex);
      if (tObject)
      {
         tCount = tObject->mCode1;
         gShare.mBlockQueue.finishRead(tIndex);
      }

      mMarkerRead.doStop();
      tPass = tObject!=0;

      tDelayB.delay();

      if (tPass)
      {
         mCount++;
         mPassCount++;
         mCheckSum += tCount;
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

void Reader::flushType1()
{
   while(true)
   {
      int tCount;
      if (!LFIntQueue::tryRead(&tCount)) break;
      mCount++;
      mPassCount++;
      mCheckSum += tCount;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::flushType2()
{
   while(true)
   {
      Class1A* tObject = (Class1A*)gShare.mPointerQueue.readPtr();
      if (!tObject) break;

      int tCount = tObject->mCode1;
      delete tObject;

      mCount++;
      mPassCount++;
      mCheckSum += tCount;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::flushType3()
{
   int tCount;
   int tIndex;

   while(true)
   {

      Class1A* tObject = (Class1A*)gShare.mBlockQueue.startRead(&tIndex);
      if (!tObject) break;

      tCount = tObject->mCode1;
      gShare.mBlockQueue.finishRead(tIndex);

      mCount++;
      mPassCount++;
      mCheckSum += tCount;
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
}

void Reader::read(int aNumReads)
{
   switch (gShare.mType)
   {
   case 1: readType1(aNumReads); break;
   case 2: readType2(aNumReads); break;
   case 3: readType3(aNumReads); break;
   }
}
   
void Reader::flush()
{
   switch (gShare.mType)
   {
   case 1: flushType1(); break;
   case 2: flushType2(); break;
   case 3: flushType3(); break;
   }
}
   
}//namespace
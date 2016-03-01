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

void Reader::read1(int aNumReads)
{
   LFBackoff tDelayB(gGSettings.mDelayB1,gGSettings.mDelayB2);

   for (int i = 0; i < aNumReads; i++)
   {
      bool tPass;
      int tCount;
      int tIndex;

      if (gShare.mTest == 1)
      {
         mMarkerRead.doStart();
         tPass = LFIntQueue::tryRead(&tCount);
         mMarkerRead.doStop();
      }

      if (gShare.mTest == 2)
      {
         mMarkerRead.doStart();

         Class1A* tObject = (Class1A*)gShare.mBlockQueue.startRead(&tIndex);
         if (tObject)
         {
            tCount = tObject->mCode1;
            gShare.mBlockQueue.finishRead(tIndex);
         }

         mMarkerRead.doStop();
         tPass = tObject!=0;
      }

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
      mMarkerRead.doStop();
   }
}
   
void Reader::flush1()
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

void Reader::read2(int aNumReads)
{
}
   
void Reader::flush2()
{
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
   switch (gShare.mMode)
   {
   case 1: read1(aNumReads); break;
   case 2: read2(aNumReads); break;
   }
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
/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <prnPrint.h>

#include "GSettings.h"
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
      mMarker.doStart();
      if (LFFreeList::test())
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

void Writer::write(int aNumWrites)
{
   mMarker.startTrial(gGSettings.mXLimit);

   switch (gShare.mMode)
   {
   case 1: write1 (aNumWrites); break;
   case 2: write2 (aNumWrites); break;
   case 8: write8 (aNumWrites); break;
   case 9: write9 (aNumWrites); break;
   }

   mCount = mPassCount + mFailCount;
   mMarker.finishTrial();
   mMeanTime = mMarker.mStatistics.mMean;
}
   


   
}//namespace
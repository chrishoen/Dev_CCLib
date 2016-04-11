/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <new>
#include "prnPrint.h"

#include "GSettings.h"
#include "LFBackoff.h"
#include "LFFreeList.h"
#include "LFIntQueue.h"
#include "someMyBlockA.h"
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
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::writeType1(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      bool tPass;
      int tCount = mCount & 0xFFFF;

      mMarkerWrite.doStart();
      tPass = LFIntQueue::tryWrite(tCount);
      mMarkerWrite.doStop();
      tDelayA.delay();

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

void Writer::writeType2(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      bool tPass;
      int tCount = mCount & 0xFFFF;

      Class1A* tObject = new Class1A;
      tObject->mCode1 = tCount;

      mMarkerWrite.doStart();
      tPass = gShare.mPointerQueue.writePtr(tObject);
      mMarkerWrite.doStop();
      tDelayA.delay();

      if (tPass)
      {
         mCount++;
         mPassCount++;
         mCheckSum += tCount;
      }
      else
      {
         delete tObject;
         mCount++;
         mFailCount++;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::writeType3(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      bool tPass = false;
      int tCount = mCount & 0xFFFF;

      mMarkerWrite.doStart();

      int tIndex;
      void* tPacket = gShare.mPacketQueue.startWrite(&tIndex);
      if (tPacket)
      {
         Class1A* tObject = new(tPacket) Class1A;
         tObject->mCode1 = tCount;
         tDelayA.delay();
         gShare.mPacketQueue.finishWrite(tIndex);
         tPass=true;
      }

      mMarkerWrite.doStop();
      tDelayA.delay();

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

void Writer::writeType4(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      MyBlockA* tObject = 0;
      bool tPass = false;
      int tCount = mCount & 0xFFFF;

      mMarkerWrite.doStart();
      tObject = new MyBlockA();
      mMarkerWrite.doStop();

      if (tObject)
      {
         tObject->mCode1 = tCount;
         tPass = gShare.mValueQueue.tryWrite(tObject);
      }
      else
      {
         tPass=false;
      }

      tDelayA.delay();

      if (tPass)
      {
         mCount++;
         mPassCount++;
         mCheckSum += tCount;
      }
      else
      {
         if (tObject)
         {
            delete tObject;
         }
         mCount++;
         mFailCount++;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Writer::writeType5(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      bool tPass = false;
      ++mCount &= 0xFFFF;

      mMarkerWrite.doStart();
      tPass = gShare.mIntQueue.tryWrite(mCount);
      mMarkerWrite.doStop();

      tDelayA.delay();

      if (tPass)
      {
         mPassCount++;
         mCheckSum += mCount;
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
   switch (gShare.mType)
   {
   case 1: writeType1 (aNumWrites); break;
   case 2: writeType2 (aNumWrites); break;
   case 3: writeType3 (aNumWrites); break;
   case 4: writeType4 (aNumWrites); break;
   case 5: writeType5 (aNumWrites); break;
   }
}
   


   
}//namespace
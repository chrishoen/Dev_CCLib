/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <new>
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
   mCount = 0;

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

void WriterReader::startTrialType1()
{
   if (mIdent == 0)
   {
      int tListSize = gGSettings.mAllocate;
      for (int i = 0; i < tListSize / 2; i++)
      {
         ++mCount &= 0xFFFF;
         LFIntQueue::tryWrite(mCount);

         mWriteCount++;
         mWritePassCount++;
         mWriteCheckSum += mCount;
      }
   }

   mMarkerWrite.startTrial(gGSettings.mXLimit);
   mMarkerRead.startTrial(gGSettings.mXLimit);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::startTrialType2()
{
   if (mIdent == 0)
   {
      int tListSize = gGSettings.mAllocate;
      for (int i = 0; i < tListSize / 2; i++)
      {
         ++mCount &= 0xFFFF;

         Class1A* tObject = new Class1A;
         tObject->mCode1 = mCount;
         gShare.mPointerQueue.writePtr(tObject);

         mWriteCount++;
         mWritePassCount++;
         mWriteCheckSum += mCount;
      }
   }

   mMarkerWrite.startTrial(gGSettings.mXLimit);
   mMarkerRead.startTrial(gGSettings.mXLimit);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::startTrialType3()
{
   if (mIdent == 0)
   {
      int tListSize = gGSettings.mAllocate;
      for (int i = 0; i < tListSize / 2; i++)
      {
         ++mCount &= 0xFFFF;

         int tIndex;
         void* tBlock = gShare.mBlockQueue.startWrite(&tIndex);
         if (tBlock)
         {
            Class1A* tObject = new(tBlock) Class1A;
            tObject->mCode1 = mCount;
            gShare.mBlockQueue.finishWrite(tIndex);
         }

         mWriteCount++;
         mWritePassCount++;
         mWriteCheckSum += mCount;
      }
   }

   mMarkerWrite.startTrial(gGSettings.mXLimit);
   mMarkerRead.startTrial(gGSettings.mXLimit);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::startTrialType4()
{
   if (mIdent == 0)
   {
      int tListSize = gGSettings.mAllocate;
      for (int i = 0; i < tListSize / 2; i++)
      {
         ++mCount &= 0xFFFF;

         Class1A* tObject = new Class1A;
         tObject->mCode1 = mCount;
         gShare.mPointerQueue.writePtr(tObject);

         mWriteCount++;
         mWritePassCount++;
         mWriteCheckSum += mCount;
      }
   }

   mMarkerWrite.startTrial(gGSettings.mXLimit);
   mMarkerRead.startTrial(gGSettings.mXLimit);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::startTrial()
{
   switch (gShare.mType)
   {
   case 1: startTrialType1 (); break;
   case 2: startTrialType2 (); break;
   case 3: startTrialType3 (); break;
   case 4: startTrialType4 (); break;
   }
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

void WriterReader::writereadType1(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      // Write
      if (my_randflag(0.5))
      {
         ++mCount &= 0xFFFF;
         bool tPass;

         mMarkerWrite.doStart();
         tPass = LFIntQueue::tryWrite(mCount);
         mMarkerWrite.doStop();
         tDelayA.delay();

         if (tPass)
         {
            mWriteCount++;
            mWritePassCount++;
            mWriteCheckSum += mCount;
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
         int tCount;
         mMarkerRead.doStart();
         tPass = LFIntQueue::tryRead(&tCount);
         mMarkerRead.doStop();
         tDelayA.delay();

         if (tPass)
         {
            mReadCount++;
            mReadPassCount++;
            mReadCheckSum += tCount;
         }
         else
         {
            mReadCount++;
            mReadFailCount++;
         }
      }
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::writereadType2(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      // Write
      if (my_randflag(0.5))
      {
         ++mCount &= 0xFFFF;

         Class1A* tObject = new Class1A;
         tObject->mCode1 = mCount;

         mMarkerWrite.doStart();
         bool tPass = gShare.mPointerQueue.writePtr(tObject);
         mMarkerWrite.doStop();
         tDelayA.delay();

         if (tPass)
         {
            mWriteCount++;
            mWritePassCount++;
            mWriteCheckSum += mCount;
         }
         else
         {
            delete tObject;
            mWriteCount++;
            mWriteFailCount++;
         }
      }
      // Read
      else
      {
         bool tPass;
         int tCount;

         mMarkerRead.doStart();
         Class1A* tObject = (Class1A*)gShare.mPointerQueue.readPtr();
         mMarkerRead.doStop();
         tDelayA.delay();

         tPass = tObject!=0;
         if (tObject)
         {
            tCount = tObject->mCode1;
            delete tObject;
         }

         if (tPass)
         {
            mReadCount++;
            mReadPassCount++;
            mReadCheckSum += tCount;
         }
         else
         {
            mReadCount++;
            mReadFailCount++;
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::writereadType3(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      // Write
      if (my_randflag(0.5))
      {
         ++mCount &= 0xFFFF;

         mMarkerWrite.doStart();

         int tIndex;
         void* tBlock = gShare.mBlockQueue.startWrite(&tIndex);
         if (tBlock)
         {
            Class1A* tObject = new(tBlock) Class1A;
            tObject->mCode1 = mCount;
            gShare.mBlockQueue.finishWrite(tIndex);
         }

         mMarkerWrite.doStop();
         tDelayA.delay();

         if (tBlock)
         {
            mWriteCount++;
            mWritePassCount++;
            mWriteCheckSum += mCount;
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
         bool tPass = false;
         int tIndex;
         int tCount;

         mMarkerRead.doStart();
         Class1A* tObject = (Class1A*)gShare.mBlockQueue.startRead(&tIndex);
         if (tObject)
         {
            tCount = tObject->mCode1;
            gShare.mBlockQueue.finishRead(tIndex);
            tPass = true;
         }
         mMarkerRead.doStop();
         tDelayA.delay();

         if (tPass)
         {
            mReadCount++;
            mReadPassCount++;
            mReadCheckSum += tCount;
         }
         else
         {
            mReadCount++;
            mReadFailCount++;
         }
      }
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::writereadType4(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      // Write
      if (my_randflag(0.5))
      {
         ++mCount &= 0xFFFF;

         Class1A* tObject = new Class1A;
         tObject->mCode1 = mCount;

         mMarkerWrite.doStart();
         bool tPass = gShare.mPointerQueue.writePtr(tObject);
         mMarkerWrite.doStop();
         tDelayA.delay();

         if (tPass)
         {
            mWriteCount++;
            mWritePassCount++;
            mWriteCheckSum += mCount;
         }
         else
         {
            delete tObject;
            mWriteCount++;
            mWriteFailCount++;
         }
      }
      // Read
      else
      {
         bool tPass;
         int tCount;

         mMarkerRead.doStart();
         Class1A* tObject = (Class1A*)gShare.mPointerQueue.readPtr();
         mMarkerRead.doStop();
         tDelayA.delay();

         tPass = tObject!=0;
         if (tObject)
         {
            tCount = tObject->mCode1;
            delete tObject;
         }

         if (tPass)
         {
            mReadCount++;
            mReadPassCount++;
            mReadCheckSum += tCount;
         }
         else
         {
            mReadCount++;
            mReadFailCount++;
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::writeread(int aNumWrites)
{
   switch (gShare.mType)
   {
   case 1: writereadType1 (aNumWrites); break;
   case 2: writereadType2 (aNumWrites); break;
   case 3: writereadType3 (aNumWrites); break;
   case 4: writereadType4 (aNumWrites); break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::flushType1()
{
   while(true)
   {
      int tCount;
      if (!LFIntQueue::tryRead(&tCount)) break;
      mReadCount++;
      mReadPassCount++;
      mReadCheckSum += tCount;
   }
}
   

//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::flushType2()
{
   while(true)
   {
      int tCount;
      Class1A* tObject = (Class1A*)gShare.mPointerQueue.readPtr();
      if (tObject==0) break;
      tCount = tObject->mCode1;
      delete tObject;
      mReadCount++;
      mReadPassCount++;
      mReadCheckSum += tCount;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::flushType3()
{
   int tCount;
   int tIndex;

   while(true)
   {

      Class1A* tObject = (Class1A*)gShare.mBlockQueue.startRead(&tIndex);
      if (!tObject) break;

      tCount = tObject->mCode1;
      gShare.mBlockQueue.finishRead(tIndex);

      mReadCount++;
      mReadPassCount++;
      mReadCheckSum += tCount;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::flushType4()
{
   while(true)
   {
      int tCount;
      Class1A* tObject = (Class1A*)gShare.mPointerQueue.readPtr();
      if (tObject==0) break;
      tCount = tObject->mCode1;
      delete tObject;
      mReadCount++;
      mReadPassCount++;
      mReadCheckSum += tCount;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void WriterReader::flush()
{
   switch (gShare.mType)
   {
   case 1: flushType1 (); break;
   case 2: flushType2 (); break;
   case 3: flushType3 (); break;
   case 4: flushType4 (); break;
   }
}
   


   
}//namespace
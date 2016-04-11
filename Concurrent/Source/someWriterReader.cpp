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
#include "someMyBlockA.h"
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
      int tListSize = gGSettings.mNumElements;
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
      int tListSize = gGSettings.mNumElements;
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
      int tListSize = gGSettings.mNumElements;
      for (int i = 0; i < tListSize / 2; i++)
      {
         ++mCount &= 0xFFFF;

         int tIndex;
         void* tPacket = gShare.mPacketQueue.startWrite(&tIndex);
         if (tPacket)
         {
            Class1A* tObject = new(tPacket) Class1A;
            tObject->mCode1 = mCount;
            gShare.mPacketQueue.finishWrite(tIndex);
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
      int tListSize = gGSettings.mNumElements;
      for (int i = 0; i < tListSize / 2; i++)
      {
         ++mCount &= 0xFFFF;

         MyBlockA* tObject = new MyBlockA();
         tObject->mCode1 = mCount;
         gShare.mValueQueue.tryWrite(tObject);

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

void WriterReader::startTrialType5()
{
   if (mIdent == 0)
   {
      int tListSize = gGSettings.mNumElements;
      for (int i = 0; i < tListSize / 2; i++)
      {
         ++mCount &= 0xFFFF;

         gShare.mIntQueue.tryWrite(mCount);

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
   case 5: startTrialType5 (); break;
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
         void* tPacket = gShare.mPacketQueue.startWrite(&tIndex);
         if (tPacket)
         {
            Class1A* tObject = new(tPacket) Class1A;
            tObject->mCode1 = mCount;
            gShare.mPacketQueue.finishWrite(tIndex);
         }

         mMarkerWrite.doStop();
         tDelayA.delay();

         if (tPacket)
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
         Class1A* tObject = (Class1A*)gShare.mPacketQueue.startRead(&tIndex);
         if (tObject)
         {
            tCount = tObject->mCode1;
            gShare.mPacketQueue.finishRead(tIndex);
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

         MyBlockA* tObject = 0;
         bool tPass = false;

         mMarkerWrite.doStart();
         tObject = new MyBlockA();
         mMarkerWrite.doStop();

         if (tObject)
         {
            tObject->mCode1 = mCount;
            tPass = gShare.mValueQueue.tryWrite(tObject);

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
         tDelayA.delay();
      }
      // Read
      else
      {
         bool tPass;
         int tCount;

         MyBlockA* tObject = 0;
         tPass = gShare.mValueQueue.tryRead((void**)&tObject);
         tDelayA.delay();

         if (tPass)
         {
            tCount = tObject->mCode1;
            mMarkerRead.doStart();
            delete tObject;
            mMarkerRead.doStop();
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

void WriterReader::writereadType5(int aNumWrites)
{
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);

   for (int i = 0; i < aNumWrites; i++)
   {
      // Write
      if (my_randflag(0.5))
      {
         ++mCount &= 0xFFFF;

         bool tPass = false;

         mMarkerWrite.doStart();
         tPass = gShare.mIntQueue.tryWrite(mCount);
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
         tPass = gShare.mIntQueue.tryRead(&tCount);
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

void WriterReader::writeread(int aNumWrites)
{
   switch (gShare.mType)
   {
   case 1: writereadType1 (aNumWrites); break;
   case 2: writereadType2 (aNumWrites); break;
   case 3: writereadType3 (aNumWrites); break;
   case 4: writereadType4 (aNumWrites); break;
   case 5: writereadType5 (aNumWrites); break;
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

      Class1A* tObject = (Class1A*)gShare.mPacketQueue.startRead(&tIndex);
      if (!tObject) break;

      tCount = tObject->mCode1;
      gShare.mPacketQueue.finishRead(tIndex);

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
      bool tPass;
      MyBlockA* tObject = 0;
      tPass = gShare.mValueQueue.tryRead((void**)&tObject);
      if (!tPass) break;
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

void WriterReader::flushType5()
{
   while(true)
   {
      int tCount;
      bool tPass;
      tPass = gShare.mIntQueue.tryRead(&tCount);
      if (!tPass) break;
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
   case 5: flushType5 (); break;
   }
}
   


   
}//namespace
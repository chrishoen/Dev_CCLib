#pragma once

/*==============================================================================
Test ring buffer.
=============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risSleep.h"
#include "ccRingBuffer.h"
#include "someRingParms.h"
#include "someTestRecord.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test ring buffer.

class TestRingBuffer : public CC::HeapRingBuffer
{
private:
   typedef CC::HeapRingBuffer BaseClass;
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   void initialize()
   {
      BaseClass::initialize(100, sizeof(TestRecord), 20);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test ring buffer writer.

class TestRingWriter : public CC::RingBufferWriter
{
private:
   typedef CC::RingBufferWriter BaseClass;
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Test variables.
   bool mFirstWriteFlag;
   long long mFirstWriteIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   TestRingWriter()
   {
      mFirstWriteFlag = true;
      mFirstWriteIndex = 0;
   }

   void resetTest() override
   {
      BaseClass::mTestFlag = true;
      mFirstWriteFlag = true;
      mFirstWriteIndex = 0;
   }

   void doTest(long long aWriteIndex, void* aElement) override
   {
      if (mFirstWriteFlag)
      {
         mFirstWriteFlag = false;
         mFirstWriteIndex = aWriteIndex;
      }
      TestRecord* tRecord = (TestRecord*)aElement;
      tRecord->doSet1(aWriteIndex);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test ring buffer writer.

class TestRingReader : public CC::RingBufferReader
{
private:
   typedef CC::RingBufferReader BaseClass;
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Test variables.
   bool mFirstReadFlag;
   long long mFirstReadIndex;
   int mTestPassCount;
   int mTestFailCount;
   long long mTestFailReadIndex;
   long long mTestFailCode0;
   long long mTestFailCode6;
   // Test variables.
   int mSleepAfterNotReadyUs;
   int mSleepAfterOverwriteUs;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   TestRingReader()
   {
      mFirstReadFlag = true;
      mFirstReadIndex = 0;
      mTestPassCount = 0;
      mTestFailCount = 0;
      mTestFailReadIndex = 0;
      mTestFailCode0 = 0;
      mTestFailCode6 = 0;
      mSleepAfterNotReadyUs = gRingParms.mSleepAfterNotReadyUs;
      mSleepAfterOverwriteUs = gRingParms.mSleepAfterOverwriteUs;
   }

   void resetTest() override
   {
      BaseClass::mTestFlag = true;
      mFirstReadFlag = true;
      mFirstReadIndex = 0;
      mTestPassCount = 0;
      mTestFailCount = 0;
      mTestFailReadIndex = 0;
      mTestFailCode0 = 0;
      mTestFailCode6 = 0;
   }

   void doTest(long long aReadIndex, void* aElement) override
   {
      if (mFirstReadFlag)
      {
         mFirstReadFlag = false;
         mFirstReadIndex = aReadIndex;
      }

      TestRecord* tRecord = (TestRecord*)aElement;

      if (tRecord->doTest1(aReadIndex))
      {
         mTestPassCount++;
      }
      else
      {
         mTestFailCount++;
         mTestFailReadIndex = aReadIndex;
         mTestFailCode0 = tRecord->mCode[0];
         mTestFailCode6 = tRecord->mCode[6];
      }
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


#pragma once

/*==============================================================================
Test ring buffer.
=============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccRingBuffer.h"
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
public:

   typedef CC::HeapRingBuffer BaseClass;

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
public:
   typedef CC::RingBufferWriter BaseClass;

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
public:
   typedef CC::RingBufferReader BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Test variables.
   bool mFirstReadFlag;
   long long mFirstReadIndex;
   int mTestPassCount;
   int mTestFailCount;

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
   }

   void resetTest() override
   {
      BaseClass::mTestFlag = true;
      mFirstReadFlag = true;
      mFirstReadIndex = 0;
      mTestPassCount = 0;
      mTestFailCount = 0;
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
      }
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


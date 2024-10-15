#pragma once

/*==============================================================================
Test ring buffer.
=============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccRingBufferEx.h"
#include "someTestRecord.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

   const int cTestRing_NumElements = 100;
   const int cTestRing_ReadGap = 20;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test ring buffer.

class alignas(16) TestRing : public CC::MemoryRingBuffer<TestRecord, cTestRing_NumElements>
{
public:
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test ring buffer writer.

class TestRingWriter : public CC::RingBufferWriter<TestRecord, cTestRing_NumElements>
{
private:
   typedef CC::RingBufferWriter<TestRecord, cTestRing_NumElements> BaseClass;
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Test variables.
   bool mFirstWriteFlag;
   long long mFirstWriteIndex;
   int mWriteTestMode;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   TestRingWriter();

   // Test methods.
   void resetTest() override;
   void doTest(long long aWriteIndex, TestRecord* aElement) override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test ring buffer writer.

class TestRingReader : public CC::RingBufferReader<TestRecord, cTestRing_NumElements, cTestRing_ReadGap>
{
private:
   typedef CC::RingBufferReader<TestRecord, cTestRing_NumElements, cTestRing_ReadGap> BaseClass;
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
   long long mTestFailCode[7];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   TestRingReader();

   // Test methods.
   void resetTest() override;
   void doTest(long long aReadIndex, TestRecord* aElement) override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


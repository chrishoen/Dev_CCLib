/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "someTestRingBuffer.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

TestRingWriter::TestRingWriter()
{
   mFirstWriteFlag = true;
   mFirstWriteIndex = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Tests.

void TestRingWriter::resetTest()
{
   BaseClass::mTestFlag = true;
   mFirstWriteFlag = true;
   mFirstWriteIndex = 0;
}

void TestRingWriter::doTest(long long aWriteIndex, void* aElement)
{
   if (mFirstWriteFlag)
   {
      mFirstWriteFlag = false;
      mFirstWriteIndex = aWriteIndex;
   }
   TestRecord* tRecord = (TestRecord*)aElement;
   tRecord->doSet(aWriteIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

TestRingReader::TestRingReader()
{
   mFirstReadFlag = true;
   mFirstReadIndex = 0;
   mTestPassCount = 0;
   mTestFailCount = 0;
   mTestFailReadIndex = 0;
   for (int i = 0; i < 7; i++)mTestFailCode[i] = 0;
   mSleepAfterNotReadyUs = gRingParms.mSleepAfterNotReadyUs;
   mSleepAfterOverwriteUs = gRingParms.mSleepAfterOverwriteUs;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Tests.

void TestRingReader::resetTest()
{
   BaseClass::mTestFlag = true;
   mFirstReadFlag = true;
   mFirstReadIndex = 0;
   mTestPassCount = 0;
   mTestFailCount = 0;
   mTestFailReadIndex = 0;
   for (int i = 0; i < 7; i++)mTestFailCode[i] = 0;
}

void TestRingReader::doTest(long long aReadIndex, void* aElement)
{
   if (mFirstReadFlag)
   {
      mFirstReadFlag = false;
      mFirstReadIndex = aReadIndex;
   }

   TestRecord* tRecord = (TestRecord*)aElement;

   if (tRecord->doTest(aReadIndex))
   {
      mTestPassCount++;
   }
   else
   {
      mTestFailCount++;
      mTestFailReadIndex = aReadIndex;
      for (int i = 0; i < 7; i++)
      {
         mTestFailCode[i] = tRecord->mCode[i];
      }
   }

   tRecord->doSet(101);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
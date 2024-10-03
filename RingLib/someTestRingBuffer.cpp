/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "someRingParms.h"
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
   // Store the first write index.
   if (mFirstWriteFlag)
   {
      mFirstWriteFlag = false;
      mFirstWriteIndex = aWriteIndex;
   }

   // For test3, do not set the record values. It will be set
   // explicitly by the thread.
   if (gRingParms.mWriteTestMode == 3) return;

   // Set the record value.
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
   // Store the first read index.
   if (mFirstReadFlag)
   {
      mFirstReadFlag = false;
      mFirstReadIndex = aReadIndex;
   }

   // Test the record against the read index.
   TestRecord* tRecord = (TestRecord*)aElement;
   if (tRecord->doTest(aReadIndex))
   {
      mTestPassCount++;
   }
   else
   {
      mTestFailCount++;
      // Store the code that the failure occured at.
      mTestFailReadIndex = aReadIndex;
      for (int i = 0; i < 7; i++)
      {
         mTestFailCode[i] = tRecord->mCode[i];
      }
   }

   // Set a dummy value to see if we read the same record more than once.
   tRecord->doSet(101);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
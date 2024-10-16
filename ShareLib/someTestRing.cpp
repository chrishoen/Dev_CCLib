/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "someTestRing.h"

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
   BaseClass::mTestFlag = cTestRing_TestFlag;
   mFirstWriteFlag = true;
   mFirstWriteIndex = 0;
   mWriteTestMode = 0;
}

void TestRingWriter::doTest(long long aWriteIndex, TestRecord* aElement)
{
   // Store the first write index.
   if (mFirstWriteFlag)
   {
      mFirstWriteFlag = false;
      mFirstWriteIndex = aWriteIndex;
   }

   // For test3, do not set the record values. It will be set
   // explicitly by the thread.
   if (mWriteTestMode == 3) return;

   // Set the record value.
   aElement->doSet(aWriteIndex);
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
   for (int i = 0; i < 7; i++) mTestFailCode[i] = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Tests.

void TestRingReader::resetTest()
{
   BaseClass::mTestFlag = cTestRing_TestFlag;
   mFirstReadFlag = true;
   mFirstReadIndex = 0;
   mTestPassCount = 0;
   mTestFailCount = 0;
   mTestFailReadIndex = 0;
   for (int i = 0; i < 7; i++) mTestFailCode[i] = 0;
}

void TestRingReader::doTest(long long aReadIndex, TestRecord* aElement)
{
   // Store the first read index.
   if (mFirstReadFlag)
   {
      mFirstReadFlag = false;
      mFirstReadIndex = aReadIndex;
   }

   // Test the record against the read index.
   if (aElement->doTest(aReadIndex))
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
         mTestFailCode[i] = aElement->mCode[i];
      }
   }

   // Set a dummy value to see if we read the same record more than once.
   aElement->doSet(101);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
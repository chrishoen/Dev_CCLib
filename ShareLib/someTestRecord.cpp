/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "someTestRecord.h"

// Global instance of the block pool

namespace Some
{
// Constructors.
TestRecord::TestRecord()
{
   for (int i = 0; i < cNumCodes; i++) mCode[i] = 11;
}

// Set.
void TestRecord::doSet1(long long aCode)
{
   for (int i = 0; i < cNumCodes; i++) mCode[i] = aCode;
}

// Test.
bool TestRecord::doTest1(long long aCode)
{
   bool tPass = true;
   for (int i = 0; i < cNumCodes; i++) if (mCode[i] != aCode) tPass = false;
   return tPass;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

   
}//namespace
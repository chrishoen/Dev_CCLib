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
   mCode1 = 0;
   for (int i = 0; i < cNumCodes; i++) mCode[i] = 0;
}

// Set.
void TestRecord::doSet1(long long aCode)
{
   mCode1 = 101;
   for (int i = 0; i < cNumCodes; i++) mCode[i] = aCode;
}

// Test.
bool TestRecord::doTest1(long long aCode)
{
   if (mCode1 != 101) return false;
   for (int i = 0; i < cNumCodes; i++) if (mCode[i] != aCode) return false;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

   
}//namespace
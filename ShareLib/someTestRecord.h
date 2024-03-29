#pragma once

/*==============================================================================
==============================================================================*/

#include <stdio.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************


namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class TestRecord
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cNumCodes = 7;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   long long mCode[cNumCodes];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Set.
   void doSet(long long aCode);

   // Test.
   bool doTest(long long aCode);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



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

class alignas(16) TestRecord
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

   // Record data variables.
   alignas(16) volatile long long mCode[cNumCodes];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   void reset();

   // Set.
   void doSet(long long aCode);

   // Test.
   bool doTest(long long aCode);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



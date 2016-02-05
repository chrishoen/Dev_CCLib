/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <prnPrint.h>

#include "GSettings.h"
#include "LFBackoff.h"
#include "LFFreeList.h"
#include "LFIntQueue.h"
#include "someShare.h"
#include "someTester.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Tester::Tester()
{
   initialize();
}

void Tester::initialize(unsigned aIdent)
{
   mCount     = 0;
   mMeanTimeTest  = 0.0;
}

void Tester::finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Tester::show()
{
   Prn::print(0,"Tester.mCount     %llu",mCount);
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Tester::test1(int aNumIter)
{
   for (int i = 0; i < aNumIter; i++)
   {
      mMarkerTest.doStart();
      LFBackoff::delay(gGSettings.mDelay1);
      mMarkerTest.doStop();
      LFBackoff::delay(gGSettings.mDelay2);

      mCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Tester::test2(int aNumIter)
{
   for (int i = 0; i < aNumIter; i++)
   {
      mMarkerTest.doStart();
      LFBackoff::delay2(gGSettings.mBackoff11,gGSettings.mBackoff12);
      mMarkerTest.doStop();
      LFBackoff::delay(gGSettings.mDelay2);

      mCount++;
   }
}




//******************************************************************************
//******************************************************************************
//******************************************************************************

void Tester::startTrial()
{
   mMarkerTest.startTrial(gGSettings.mXLimit);
}
void Tester::finishTrial()
{
   mMarkerTest.finishTrial();
   mMeanTimeTest = mMarkerTest.mStatistics.mMean;
}

void Tester::test(int aNumWrites)
{
   switch (gShare.mTest)
   {
   case 1: test1 (aNumWrites); break;
   case 2: test2 (aNumWrites); break;
   }
}
   


   
}//namespace
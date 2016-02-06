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
   LFBackoff tBackoffA(gGSettings.mDelayA1,gGSettings.mDelayA2);
   LFBackoff tBackoffB(gGSettings.mDelayB1,gGSettings.mDelayB2);

   for (int i = 0; i < aNumIter; i++)
   {
      mMarkerTest.doStart();
      tBackoffA.delay();
      mMarkerTest.doStop();
      tBackoffB.delay();

      mCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Tester::test2(int aNumIter)
{
   LFBackoff tBackoffA(gGSettings.mDelayA1,gGSettings.mDelayA2);
   LFBackoff tDelayB  (gGSettings.mDelayB1,gGSettings.mDelayB2);

   for (int i = 0; i < aNumIter; i++)
   {
      tBackoffA.reset();
      mMarkerTest.doStart();
      tBackoffA.expBackoff();
      mMarkerTest.doStop();
      tDelayB.delay();

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
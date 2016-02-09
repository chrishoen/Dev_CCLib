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
   mMeanTimeTest1  = 0.0;
   mMeanTimeTest2  = 0.0;
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
   LFBackoff tDelayA(gGSettings.mDelayA1,gGSettings.mDelayA2);
   LFBackoff tDelayB(gGSettings.mDelayB1,gGSettings.mDelayB2);
// tDelayA.setDelay(100,100);

   for (int i = 0; i < aNumIter; i++)
   {
      mMarkerTest1.doStart();
      tDelayA.delay();
      mMarkerTest1.doStop();
      tDelayB.delay();

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

      mMarkerTest1.doStart();
      tBackoffA.expBackoff();
      mMarkerTest1.doStop();

      mMarkerTest2.doStart();
      tBackoffA.expBackoff();
      mMarkerTest2.doStop();

      tDelayB.delay();

      mCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Tester::test3(int aNumIter)
{
}




//******************************************************************************
//******************************************************************************
//******************************************************************************

void Tester::startTrial()
{
   mMarkerTest1.startTrial(gGSettings.mXLimit);
   mMarkerTest2.startTrial(gGSettings.mXLimit);
}
void Tester::finishTrial()
{
   mMarkerTest1.finishTrial();
   mMarkerTest2.finishTrial();
   mMeanTimeTest1 = mMarkerTest1.mStatistics.mMean;
   mMeanTimeTest2 = mMarkerTest2.mStatistics.mMean;
}

void Tester::test(int aNumWrites)
{
   switch (gShare.mTest)
   {
      case 1: test1 (aNumWrites); break;
      case 2: test2 (aNumWrites); break;
      case 3: test3 (aNumWrites); break;
   }
}
   


   
}//namespace
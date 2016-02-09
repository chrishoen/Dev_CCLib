#ifndef _SOMETESTER_H_
#define _SOMETESTER_H_

/*==============================================================================
==============================================================================*/

#include <stdio.h>
#include <atomic>
#include "someMessage.h"
#include "someClass1.h"
#include "risTimeMarker.h"
#include "LFBackoff.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************


namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class Tester
{
public:

   //---------------------------------------------------------------------------
   // Methods

   Tester();

   void initialize(unsigned aIdent=0);
   void finalize();
   void show();

   void startTrial();
   void finishTrial();

   void test1 (int aNumIter);
   void test2 (int aNumIter);
   void test3 (int aNumIter);
   void test4 (int aNumIter);
   void test  (int aNumIter);

   //---------------------------------------------------------------------------
   // Members

   unsigned long long mCount;

   Ris::TrialTimeMarker mMarkerTest1;
   Ris::TrialTimeMarker mMarkerTest2;
   double               mMeanTimeTest1;
   double               mMeanTimeTest2;

   Some::Class1A*       mClass1A;
};

//******************************************************************************
}//namespace

#endif


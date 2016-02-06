#ifndef _SOMETESTER_H_
#define _SOMETESTER_H_

/*==============================================================================
==============================================================================*/

#include <stdio.h>
#include <atomic>
#include "someMessage.h"
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
   void test  (int aNumIter);

   //---------------------------------------------------------------------------
   // Members

   unsigned long long mCount;

   Ris::TrialTimeMarker mMarkerTest;
   double               mMeanTimeTest;

   std::atomic<int> mAX;
   int              mNC;
   int              mNE;
};

//******************************************************************************
}//namespace

#endif


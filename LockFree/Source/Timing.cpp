#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>

#include "prnPrint.h"
#include "risTimeMarker.h"
#include "LFIntQueue.h"
#include "Timing.h"

using namespace std;

namespace Timing
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Regionals

   Ris::TrialTimeMarker mMarker;
   int mWriteCount=0;
   int mReadCount=0;

   atomic<int> mAX=0;
   int mNC=0;
   int mNE=0;

   void test1();
   void test2();
   void test3();
   void test4();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Run1

   void run1(int aTest)
   {
      int tIterations = 1000000;

      mWriteCount=0;
      mReadCount=0;
      mAX=0;

      mMarker.startTrial();

      for (int i = 0; i < tIterations; i++)
      {
         mMarker.doStart();
         switch (aTest)
         {
         case 1:  test1(); break;
         case 2:  test2(); break;
         case 3:  test3(); break;
         case 4:  test4(); break;
         }
         mMarker.doStop();
      }

      mMarker.finishTrial();

      Prn::print(0, "TEST %5d $$ %10.3f  %10.3f  %10.3f  %10.3f",
         mMarker.mStatistics.mPutCount,
         mMarker.mStatistics.mMean,
         mMarker.mStatistics.mStdDev,
         mMarker.mStatistics.mMinX,
         mMarker.mStatistics.mMaxX);

      Prn::print(0, "Done");
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Test

   void test1()
   {
      mWriteCount++;
   }

   void test2()
   {
      mAX++;
   }

   void test3()
   {
      LFIntQueue::tryWrite(++mWriteCount);
      LFIntQueue::tryRead(&mReadCount);
   }

   void test4()
   {
      mAX = 100;
      mNC = 100;
      mNE = 200;

      mAX.compare_exchange_weak(mNC,mNE);
   }


}
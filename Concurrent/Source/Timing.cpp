#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>

#include "prnPrint.h"
#include "my_functions.h"
#include "risTimeMarker.h"
#include "LFIntQueue.h"
#include "LFBackoff.h"
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

   void test11();
   void test12();
   void test13();
   void test14();
   void test15();

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
         case 1:  test11(); break;
         case 2:  test12(); break;
         case 3:  test13(); break;
         case 4:  test14(); break;
         case 5:  test15(); break;
         }
         mMarker.doStop();
      }

      mMarker.finishTrial();

      Prn::print(0, "TEST1 %5d $$ %10.3f  %10.3f  %10.3f  %10.3f",
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
   // Run2

   void run2(int aTest)
   {
      LFIntQueue::initializeTest(aTest);

      int tIterations = 1000000;

      mMarker.startTrial();

      for (int i = 0; i < tIterations; i++)
      {
         mMarker.doStart();
         LFIntQueue::test();
         mMarker.doStop();
      }

      mMarker.finishTrial();

      Prn::print(0, "TEST2 %5d $$ %10.3f  %10.3f  %10.3f  %10.3f",
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

   void test11()
   {
      mWriteCount++;
   }

   void test12()
   {
      mAX++;
   }

   void test13()
   {
      mAX.fetch_add(1,memory_order_relaxed);
      return;
      mAX = 100;
      mNC = 100;
      mNE = 200;

      mAX.compare_exchange_weak(mNC,mNE);
   }

   void test14()
   {
      LFIntQueue::tryWrite(++mWriteCount);
      LFIntQueue::tryRead(&mReadCount);
   }

   void test15()
   {
   }
}
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

   Ris::TimeMarker mMarker;
   int mWriteCount=0;
   int mReadCount=0;
   atomic<int> mAX=0;

   void test1();
   void test2();
   void test3();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Run1

   void run1()
   {
      int tIterations = 1000000;
      mMarker.initialize(tIterations);

      mWriteCount=0;
      mReadCount=0;
      mAX=0;

      for (int i = 0; i < tIterations; i++)
      {
         mMarker.doStart();
         test1();
         mMarker.doStop();

         if (mMarker.mStatistics.mEndOfPeriod)
         {
            Prn::print(0, "TEST %5d $$ %10.3f  %10.3f  %10.3f  %10.3f",
               mMarker.mStatistics.mSize,
               mMarker.mStatistics.mMean,
               mMarker.mStatistics.mStdDev,
               mMarker.mStatistics.mMinX,
               mMarker.mStatistics.mMaxX);
            mMarker.mStatistics.mEndOfPeriod = false;
         }
      }

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


}
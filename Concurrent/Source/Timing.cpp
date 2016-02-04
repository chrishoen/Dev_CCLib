#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>

#include "prnPrint.h"
#include "my_functions.h"
#include "risTimeMarker.h"
#include "GSettings.h"
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
   Ris::TrialTimeMarker mMarkerWrite;
   Ris::TrialTimeMarker mMarkerRead;
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
   void test16();

   void test21();
   void test22();

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

      mMarker.startTrial(gGSettings.mXLimit);

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
         case 6:  test16(); break;
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
      int tIterations = 1000000;

      mWriteCount=0;
      mReadCount=0;
      mAX=0;

      mMarkerWrite.startTrial(gGSettings.mXLimit);
      mMarkerRead.startTrial(gGSettings.mXLimit);

      for (int i = 0; i < tIterations; i++)
      {
         switch (aTest)
         {
         case 1:  test21(); break;
         case 2:  test22(); break;
         }
      }

      mMarkerWrite.finishTrial();
      mMarkerRead.finishTrial();

      Prn::print(0, "WRITE2 %5d $$ %10.3f  %10.3f  %10.3f  %10.3f",
         mMarkerWrite.mStatistics.mPutCount,
         mMarkerWrite.mStatistics.mMean,
         mMarkerWrite.mStatistics.mStdDev,
         mMarkerWrite.mStatistics.mMinX,
         mMarkerWrite.mStatistics.mMaxX);

      Prn::print(0, "READ2  %5d $$ %10.3f  %10.3f  %10.3f  %10.3f",
         mMarkerRead.mStatistics.mPutCount,
         mMarkerRead.mStatistics.mMean,
         mMarkerRead.mStatistics.mStdDev,
         mMarkerRead.mStatistics.mMinX,
         mMarkerRead.mStatistics.mMaxX);

      Prn::print(0, "Done");
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Test

   void test11()
   {
      LFBackoff::delay(gGSettings.mDelay1);
   }

   void test12()
   {
      LFBackoff::delay(gGSettings.mBackoff1);
   }

   void test13()
   {
      mWriteCount++;
   }

   void test14()
   {
      mAX++;

      mAX = 100;
      mNC = 200;
      mNE = 200;

      mAX.compare_exchange_weak(mNC,mNE);
   }

   void test15()
   {
      LFIntQueue::tryWrite(++mWriteCount);
      LFIntQueue::tryRead(&mReadCount);
   }

   void test16()
   {
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Test

   void test21()
   {
      mMarkerWrite.doStart();
      LFIntQueue::tryWrite(++mWriteCount);
      mMarkerWrite.doStop();

      mMarkerRead.doStart();
      LFIntQueue::tryRead(&mReadCount);
      mMarkerRead.doStop();
   }

   void test22()
   {
      mMarkerWrite.doStart();
      LFIntQueue::tryWrite(++mWriteCount);
      mMarkerWrite.doStop();
      LFBackoff::delay(gGSettings.mDelayWrite);

      mMarkerRead.doStart();
      LFIntQueue::tryRead(&mReadCount);
      mMarkerRead.doStop();
      LFBackoff::delay(gGSettings.mDelayRead);
   }

}
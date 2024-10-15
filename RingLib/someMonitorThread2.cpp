/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <time.h>

#include "risProgramTime.h"
#include "risThreadsPriorities.h"

#include "smShare.h"

#include "someRingParms.h"
#include "someRingReaderThread2.h"

#define  _SOMEMONITORTHREAD2_CPP_
#include "someMonitorThread2.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MonitorThread2::MonitorThread2()
{
   // Set base class variables.
   BaseClass::setThreadName("Monitor");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mMonitor);
   BaseClass::mTimerPeriod = gRingParms.mMonitorThreadPeriod;

   // Set member variables.
   mShowCode = 0;

   // Bind member variables.
   mMon_NextWriteIndex.bind((long long*)&SM::gShare->mTestRing.mNextWriteIndex);
   mMon_LastReadIndex.bind((long long*)&gRingReaderThread2->mRingReader.mLastReadIndex);
}

// Update status variables.
void MonitorThread2::update()
{
   mMon_NextWriteIndex.update();
   mMon_LastReadIndex.update();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void MonitorThread2::executeOnTimer(int aTimeCount)
{
   if (gRingReaderThread2->mStopFlag) return;

   update();

   TestRingReader* tReader = &gRingReaderThread2->mRingReader;

   if (mShowCode == 1)
   {
      Prn::print(Prn::Show1, "NextWriteIndex           %-10lld  %lld",
         mMon_NextWriteIndex.mValue, mMon_NextWriteIndex.mDelta);
      Prn::print(Prn::Show1, "LastReadIndex            %-10lld  %lld",
         mMon_LastReadIndex.mValue, mMon_LastReadIndex.mDelta);

      Prn::print(Prn::Show1, "ReadCount                %-10d", tReader->mReadCount);
      Prn::print(Prn::Show1, "available                %-10d", tReader->available());
      Prn::print(Prn::Show1, "NotReadyCount1           %-10d", tReader->mNotReadyCount1);
      Prn::print(Prn::Show1, "NotReadyCount2           %-10d", tReader->mNotReadyCount2);
      Prn::print(Prn::Show1, "NotReadyCount3           %-10d", tReader->mNotReadyCount3);
      Prn::print(Prn::Show1, "MissCount                %-10d", tReader->mMissCount);
      Prn::print(Prn::Show1, "OverwriteCount           %-10d", tReader->mOverwriteCount);
      Prn::print(Prn::Show1, "MaxDeltaRead             %-10d", tReader->mMaxDeltaRead);
      Prn::print(Prn::Show1, "TestPassCount            %-10d", tReader->mTestPassCount);
      Prn::print(Prn::Show1, "TestFailCount            %-10d", tReader->mTestFailCount);
      Prn::print(Prn::Show1, "");
   }

   if (mShowCode == 2)
   {
      Prn::print(Prn::Show1, "%1d$   %3lld %3lld  %3d NRDY %d %d %d DROP %d %d OVER %d TEST %d %d",
         gRingReaderThread2->mThreadCurrentProcessor,
         SM::gShare->mTestRing.mNextWriteIndex,
         gRingReaderThread2->mRingReader.mLastReadIndex,
         gRingReaderThread2->mRingReader.available(),
         gRingReaderThread2->mRingReader.mNotReadyCount1,
         gRingReaderThread2->mRingReader.mNotReadyCount2,
         gRingReaderThread2->mRingReader.mNotReadyCount3,
         gRingReaderThread2->mRingReader.mMissCount,
         gRingReaderThread2->mRingReader.mMaxDeltaRead,
         gRingReaderThread2->mRingReader.mOverwriteCount,
         gRingReaderThread2->mRingReader.mTestPassCount,
         gRingReaderThread2->mRingReader.mTestFailCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
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
#include "someRingReaderThread.h"

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
   BaseClass::mTimerPeriod = 1000;

   // Set member variables.
   mShowCode = 0;

   // Bind member variables.
   mMon_UpNextWriteIndex.bind((long long*)&SM::gShare->mUpRing.mNextWriteIndex);
   mMon_UpLastReadIndex.bind((long long*)&SM::gShare->mSX.mRpuRingLastReadIndex);
   mMon_DownNextWriteIndex.bind((long long*)&SM::gShare->mDownRing.mNextWriteIndex);
   mMon_DownLastReadIndex.bind((long long*)&gRingReaderThread->mRingReader.mLastReadIndex);
   mMon_UpTestPassCount.bind((int*)&SM::gShare->mSX.mRpuRingTestPassCount);
}

// Update status variables.
void MonitorThread2::update()
{
   mMon_UpNextWriteIndex.update();
   mMon_UpLastReadIndex.update();
   mMon_DownNextWriteIndex.update();
   mMon_DownLastReadIndex.update();
   mMon_UpTestPassCount.update();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void MonitorThread2::executeOnTimer(int aTimeCount)
{
   update();

   TestRingReader* tReader = &gRingReaderThread->mRingReader;

   if (mShowCode == 1)
   {
      Prn::print(Prn::Show1, "Cpu Up   NextWriteIndex       %-10lld  %lld",
         mMon_UpNextWriteIndex.mValue, mMon_UpNextWriteIndex.mDelta);
      Prn::print(Prn::Show1, "Rpu Up   LastReadIndex        %-10lld  %lld",
         mMon_UpLastReadIndex.mValue, mMon_UpLastReadIndex.mDelta);
      Prn::print(Prn::Show1, "Rpu Down NextWriteIndex       %-10lld  %lld",
         mMon_DownNextWriteIndex.mValue, mMon_DownNextWriteIndex.mDelta);
      Prn::print(Prn::Show1, "Cpu Down LastReadIndex        %-10lld  %lld",
         mMon_DownLastReadIndex.mValue, mMon_DownLastReadIndex.mDelta);

      Prn::print(Prn::Show1, "Cpu Down ReadCount            %-10d", tReader->mReadCount);
      Prn::print(Prn::Show1, "Cpu Down available            %-10d", tReader->available());
      Prn::print(Prn::Show1, "Cpu Down NotReadyCount1       %-10d", tReader->mNotReadyCount1);
      Prn::print(Prn::Show1, "Cpu Down NotReadyCount2       %-10d", tReader->mNotReadyCount2);
      Prn::print(Prn::Show1, "Cpu Down NotReadyCount3       %-10d", tReader->mNotReadyCount3);
      Prn::print(Prn::Show1, "Cpu Down MissCount            %-10d", tReader->mMissCount);
      Prn::print(Prn::Show1, "Cpu Down OverwriteCount       %-10d", tReader->mOverwriteCount);
      Prn::print(Prn::Show1, "Cpu Down MaxDeltaRead         %-10d", tReader->mMaxDeltaRead);
      Prn::print(Prn::Show1, "Cpu Down TestPassCount        %-10d", tReader->mTestPassCount);
      Prn::print(Prn::Show1, "Cpu Down TestFailCount        %-10d", tReader->mTestFailCount);
      Prn::print(Prn::Show1, "");
   }

   if (mShowCode == 2)
   {
      Prn::print(Prn::Show1, "Cpu Down $   %3lld %3lld  %3d NRDY %d %d %d MISS %d OVER %d MAX %d TEST %d %d",
         SM::gShare->mTestRing.mNextWriteIndex,
         gRingReaderThread->mRingReader.mLastReadIndex,
         gRingReaderThread->mRingReader.available(),
         gRingReaderThread->mRingReader.mNotReadyCount1,
         gRingReaderThread->mRingReader.mNotReadyCount2,
         gRingReaderThread->mRingReader.mNotReadyCount3,
         gRingReaderThread->mRingReader.mMissCount,
         gRingReaderThread->mRingReader.mOverwriteCount,
         gRingReaderThread->mRingReader.mMaxDeltaRead,
         gRingReaderThread->mRingReader.mTestPassCount,
         gRingReaderThread->mRingReader.mTestFailCount);
   }

   if (gRingParms.mScope == 2 && mShowCode == 3)
   {
      Prn::print(Prn::Show1, "Cpu Up   NextWriteIndex       %-10lld  %lld",
         mMon_UpNextWriteIndex.mValue, mMon_UpNextWriteIndex.mDelta);
      Prn::print(Prn::Show1, "Rpu Up   LastReadIndex        %-10lld  %lld",
         mMon_UpLastReadIndex.mValue, mMon_UpLastReadIndex.mDelta);
      Prn::print(Prn::Show1, "Rpu Down NextWriteIndex       %-10lld  %lld",
         mMon_DownNextWriteIndex.mValue, mMon_DownNextWriteIndex.mDelta);
      Prn::print(Prn::Show1, "Cpu Down LastReadIndex        %-10lld  %lld",
         mMon_DownLastReadIndex.mValue, mMon_DownLastReadIndex.mDelta);

      Prn::print(Prn::Show1, "Rpu Up ReadCount              %-10d", SM::gShare->mSX.mRpuRingReadCount);
      Prn::print(Prn::Show1, "Rpu Up Available              %-10d", SM::gShare->mSX.mRpuRingAvailable);
      Prn::print(Prn::Show1, "Rpu Up NotReadyCount1         %-10d", SM::gShare->mSX.mRpuRingNotReadyCount1);
      Prn::print(Prn::Show1, "Rpu Up NotReadyCount2         %-10d", SM::gShare->mSX.mRpuRingNotReadyCount2);
      Prn::print(Prn::Show1, "Rpu Up NotReadyCount3         %-10d", SM::gShare->mSX.mRpuRingNotReadyCount3);
      Prn::print(Prn::Show1, "Rpu Up MissCount              %-10d", SM::gShare->mSX.mRpuRingMissCount);
      Prn::print(Prn::Show1, "Rpu Up OverwriteCount         %-10d", SM::gShare->mSX.mRpuRingOverwriteCount);
      Prn::print(Prn::Show1, "Rpu Up MaxDeltaRead           %-10d", SM::gShare->mSX.mRpuRingMaxDeltaRead);
      Prn::print(Prn::Show1, "Rpu Up TestPassCount          %-10d  %d",
         mMon_UpTestPassCount.mValue, mMon_UpTestPassCount.mDelta);
      Prn::print(Prn::Show1, "Rpu Up TestFailCount          %-10d", SM::gShare->mSX.mRpuRingTestFailCount);
      Prn::print(Prn::Show1, "");
   }

   if (gRingParms.mScope == 2 && mShowCode == 4)
   {
      Prn::print(Prn::Show1, "Rpu Up $   %3lld %3lld  %3d NRDY %d %d %d MISS %d OVER MAX %d TEST %d %d",
         SM::gShare->mTestRing.mNextWriteIndex,
         gRingReaderThread->mRingReader.mLastReadIndex,
         SM::gShare->mSX.mRpuRingAvailable,
         SM::gShare->mSX.mRpuRingNotReadyCount1,
         SM::gShare->mSX.mRpuRingNotReadyCount2,
         SM::gShare->mSX.mRpuRingNotReadyCount3,
         SM::gShare->mSX.mRpuRingMissCount,
         SM::gShare->mSX.mRpuRingOverwriteCount,
         SM::gShare->mSX.mRpuRingMaxDeltaRead,
         SM::gShare->mSX.mRpuRingTestPassCount,
         SM::gShare->mSX.mRpuRingTestFailCount);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
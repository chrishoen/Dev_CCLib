/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <time.h>

#include "risProgramTime.h"
#include "cmnPriorities.h"

#include "smShare.h"

#include "someRingParms.h"
#include "someRingReaderThread.h"

#define  _SOMEMONITORTHREAD1_CPP_
#include "someMonitorThread1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MonitorThread1::MonitorThread1()
{
   // Set base class variables.
   BaseClass::setThreadName("Monitor");
   BaseClass::setThreadPriority(Cmn::gPriorities.mMonitor);
   BaseClass::mTimerPeriod = 1000;

   // Set member variables.
   mShowCode = 0;

   // Bind member variables.
   mMon_NextWriteIndex.bind((long long*)&SM::gShare->mTestRing.mNextWriteIndex);
   mMon_LastReadIndex.bind((long long*)&gRingReaderThread->mRingReader.mLastReadIndex);
}

// Update status variables.
void MonitorThread1::update()
{
   mMon_NextWriteIndex.update();
   mMon_LastReadIndex.update();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void MonitorThread1::executeOnTimer(int aTimeCount)
{
   update();

   TestRingReader* tReader = &gRingReaderThread->mRingReader;

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
      Prn::print(Prn::Show1, "OverwriteCount           %-10d", tReader->mOverwriteCount);
      Prn::print(Prn::Show1, "MaxDeltaRead             %-10d", tReader->mMaxDeltaRead);
      Prn::print(Prn::Show1, "TestPassCount            %-10d", tReader->mTestPassCount);
      Prn::print(Prn::Show1, "TestFailCount            %-10d", tReader->mTestFailCount);
      Prn::print(Prn::Show1, "");
   }

   if (mShowCode == 2)
   {
      Prn::print(Prn::Show1, "%1d$   %3lld %3lld  %3d NRDY %d %d %d DROP %d OVER %d MAX %d TEST %d %d",
         gRingReaderThread->mThreadCurrentProcessor,
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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
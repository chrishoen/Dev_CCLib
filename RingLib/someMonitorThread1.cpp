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
#include "someRingReaderThread1.h"

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
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mMonitor);
   BaseClass::mTimerPeriod = gRingParms.mMonitorThreadPeriod;

   // Set member variables.
   mShowCode = 0;

   // Bind member variables.
   mMon_NextWriteIndex.bind(&SM::gShare->mTestRing.mNextWriteIndex);
   mMon_LastReadIndex.bind(&gRingReaderThread1->mRingReader.mLastReadIndex);
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

   TestRingReader* tReader = &gRingReaderThread1->mRingReader;

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
      Prn::print(Prn::Show1, "DropCount                %-10d", tReader->mDropCount);
      Prn::print(Prn::Show1, "MaxDeltaRead             %-10d", tReader->mMaxDeltaRead);
      Prn::print(Prn::Show1, "OverwriteCount           %-10d", tReader->mOverwriteCount);
      Prn::print(Prn::Show1, "TestPassCount            %-10d", tReader->mTestPassCount);
      Prn::print(Prn::Show1, "TestFailCount            %-10d", tReader->mTestFailCount);
      Prn::print(Prn::Show1, "");
   }

   if (mShowCode == 2)
   {
      Prn::print(Prn::Show1, "%1d$   %3lld %3lld  %3d NRDY %d %d %d DROP %d %d OVER %d TEST %d %d",
         gRingReaderThread1->mThreadCurrentProcessor,
         SM::gShare->mTestRing.mNextWriteIndex,
         gRingReaderThread1->mRingReader.mLastReadIndex,
         gRingReaderThread1->mRingReader.available(),
         gRingReaderThread1->mRingReader.mNotReadyCount1,
         gRingReaderThread1->mRingReader.mNotReadyCount2,
         gRingReaderThread1->mRingReader.mNotReadyCount3,
         gRingReaderThread1->mRingReader.mDropCount,
         gRingReaderThread1->mRingReader.mMaxDeltaRead,
         gRingReaderThread1->mRingReader.mOverwriteCount,
         gRingReaderThread1->mRingReader.mTestPassCount,
         gRingReaderThread1->mRingReader.mTestFailCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
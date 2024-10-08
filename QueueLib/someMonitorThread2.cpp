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

#include "someQueueParms.h"
#include "someQueueReaderThread2.h"

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
   BaseClass::mTimerPeriod = gQueueParms.mMonitorThreadPeriod;

   // Set member variables.
   mShowCode = 0;

   // Bind member variables.
   mMon_NextWriteIndex.bind((long long*)&SM::gShare->mTestQueue.mNextWriteIndex);
   mMon_LastReadIndex.bind((long long*)&gQueueReaderThread2->mQueueReader.mLastReadIndex);
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
   if (gQueueReaderThread2->mStopFlag) return;

   update();

   TestQueueReader* tReader = &gQueueReaderThread2->mQueueReader;

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
         gQueueReaderThread2->mThreadCurrentProcessor,
         SM::gShare->mTestQueue.mNextWriteIndex,
         gQueueReaderThread2->mQueueReader.mLastReadIndex,
         gQueueReaderThread2->mQueueReader.available(),
         gQueueReaderThread2->mQueueReader.mNotReadyCount1,
         gQueueReaderThread2->mQueueReader.mNotReadyCount2,
         gQueueReaderThread2->mQueueReader.mNotReadyCount3,
         gQueueReaderThread2->mQueueReader.mDropCount,
         gQueueReaderThread2->mQueueReader.mMaxDeltaRead,
         gQueueReaderThread2->mQueueReader.mOverwriteCount,
         gQueueReaderThread2->mQueueReader.mTestPassCount,
         gQueueReaderThread2->mQueueReader.mTestFailCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
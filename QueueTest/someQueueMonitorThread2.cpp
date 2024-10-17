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
#include "someQueueReaderThread.h"

#define  _SOMEQUEUEMONITORTHREAD2_CPP_
#include "someQueueMonitorThread2.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

QueueMonitorThread2::QueueMonitorThread2()
{
   // Set base class variables.
   BaseClass::setThreadName("Monitor2");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mMonitor);
   BaseClass::mTimerPeriod = 1000;

   // Set member variables.
   mShowCode = 0;

   // Bind member variables.
   mMon_CpuWriteCount.bind(&SM::gShare->mSX.mCpuWriteCount);
   mMon_CpuWritePassCount.bind(&SM::gShare->mSX.mCpuWritePassCount);
   mMon_CpuReadCount.bind(&SM::gShare->mSX.mCpuReadCount);
   mMon_CpuReadPassCount.bind(&SM::gShare->mSX.mCpuReadPassCount);
   mMon_RpuWriteCount.bind(&SM::gShare->mSX.mRpuWriteCount);
   mMon_RpuWritePassCount.bind(&SM::gShare->mSX.mRpuWritePassCount);
   mMon_RpuReadCount.bind(&SM::gShare->mSX.mRpuReadCount);
   mMon_RpuReadPassCount.bind(&SM::gShare->mSX.mRpuReadPassCount);
}

// Update status variables.
void QueueMonitorThread2::update()
{
   mMon_CpuWriteCount.update();
   mMon_CpuWritePassCount.update();
   mMon_CpuReadCount.update();
   mMon_CpuReadPassCount.update();
   mMon_RpuWriteCount.update();
   mMon_RpuWritePassCount.update();
   mMon_RpuReadCount.update();
   mMon_RpuReadPassCount.update();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void QueueMonitorThread2::executeOnTimer(int aTimeCount)
{
   update();

   int tUpSize = SM::gShare->mUpValQueue.size();
   int tDownSize = SM::gShare->mDownValQueue.size();

   int tProcNum = 9;
   if (gQueueReaderThread) tProcNum = gQueueReaderThread->mThreadCurrentProcessor;

   if (mShowCode == 1)
   {
      Prn::print(Prn::Show1, "UpSize                   %-10lld", tUpSize);
      Prn::print(Prn::Show1, "CpuWriteCount            %-10lld  %lld",
         mMon_CpuWriteCount.mValue, mMon_CpuWriteCount.mDelta);
      Prn::print(Prn::Show1, "CpuWritePassCount        %-10lld  %lld",
         mMon_CpuWritePassCount.mValue, mMon_CpuWritePassCount.mDelta);
      Prn::print(Prn::Show1, "CpuWriteFullCount        %-10lld", SM::gShare->mSX.mCpuWriteFullCount);

      Prn::print(Prn::Show1, "CpuReadCount             %-10lld  %lld",
         mMon_CpuReadCount.mValue, mMon_CpuReadCount.mDelta);
      Prn::print(Prn::Show1, "CpuReadPassCount         %-10lld  %lld",
         mMon_CpuReadPassCount.mValue, mMon_CpuReadPassCount.mDelta);
      Prn::print(Prn::Show1, "CpuReadEmptyCount        %-10lld", SM::gShare->mSX.mCpuReadEmptyCount);
      Prn::print(Prn::Show1, "CpuReadErrorCount        %-10lld", SM::gShare->mSX.mCpuReadErrorCount);
      Prn::print(Prn::Show1, "");

      Prn::print(Prn::Show1, "DownSize                 %-10lld", tDownSize);
      Prn::print(Prn::Show1, "RpuWriteCount            %-10lld  %lld",
         mMon_RpuWriteCount.mValue, mMon_RpuWriteCount.mDelta);
      Prn::print(Prn::Show1, "RpuWritePassCount        %-10lld  %lld",
         mMon_RpuWritePassCount.mValue, mMon_RpuWritePassCount.mDelta);
      Prn::print(Prn::Show1, "RpuWriteFullCount        %-10lld", SM::gShare->mSX.mRpuWriteFullCount);

      Prn::print(Prn::Show1, "RpuReadCount             %-10lld  %lld",
         mMon_RpuReadCount.mValue, mMon_RpuReadCount.mDelta);
      Prn::print(Prn::Show1, "RpuReadPassCount         %-10lld  %lld",
         mMon_RpuReadPassCount.mValue, mMon_RpuReadPassCount.mDelta);
      Prn::print(Prn::Show1, "RpuReadEmptyCount        %-10lld", SM::gShare->mSX.mRpuReadEmptyCount);
      Prn::print(Prn::Show1, "RpuReadErrorCount        %-10lld", SM::gShare->mSX.mRpuReadErrorCount);
      Prn::print(Prn::Show1, "");
   }

   if (mShowCode == 2)
   {
      Prn::print(Prn::Show1, "Cpu %1d UD %3d  %3d$   WR %5lld %5lld %5lld RD %5lld %5lld %5lld ERR %lld",
         tProcNum, tUpSize, tUpSize,
         SM::gShare->mSX.mCpuWriteCount,
         SM::gShare->mSX.mCpuWritePassCount,
         SM::gShare->mSX.mCpuWriteFullCount,
         SM::gShare->mSX.mCpuReadCount,
         SM::gShare->mSX.mCpuReadPassCount,
         SM::gShare->mSX.mCpuReadEmptyCount,
         SM::gShare->mSX.mCpuReadErrorCount);
   }

   if (mShowCode == 3)
   {
      Prn::print(Prn::Show1, "Rpu %1d UD %3d  %3d$   WR %5lld %5lld %5lld RD %5lld %5lld %5lld ERR %lld",
         tProcNum, tUpSize, tUpSize,
         SM::gShare->mSX.mRpuWriteCount,
         SM::gShare->mSX.mRpuWritePassCount,
         SM::gShare->mSX.mRpuWriteFullCount,
         SM::gShare->mSX.mRpuReadCount,
         SM::gShare->mSX.mRpuReadPassCount,
         SM::gShare->mSX.mRpuReadEmptyCount,
         SM::gShare->mSX.mRpuReadErrorCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
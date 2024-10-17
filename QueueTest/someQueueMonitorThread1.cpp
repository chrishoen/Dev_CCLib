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

#define  _SOMEQUEUEMONITORTHREAD1_CPP_
#include "someQueueMonitorThread1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

QueueMonitorThread1::QueueMonitorThread1()
{
   // Set base class variables.
   BaseClass::setThreadName("Monitor1");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mMonitor);
   BaseClass::mTimerPeriod = 1000;

   // Set member variables.
   mShowCode = 0;

   // Bind member variables.
   mMon_WriteCount.bind(&SM::gShare->mSX.mCpuWriteCount);
   mMon_WritePassCount.bind(&SM::gShare->mSX.mCpuWritePassCount);
   mMon_ReadCount.bind(&SM::gShare->mSX.mCpuReadCount);
   mMon_ReadPassCount.bind(&SM::gShare->mSX.mCpuReadPassCount);
}

// Update status variables.
void QueueMonitorThread1::update()
{
   mMon_WriteCount.update();
   mMon_WritePassCount.update();
   mMon_ReadCount.update();
   mMon_ReadPassCount.update();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void QueueMonitorThread1::executeOnTimer(int aTimeCount)
{
   update();

   int tSize = -1;
   if (SM::gShare->mSX.mQueueSelect == 1) tSize = SM::gShare->mValQueue.size();
   if (SM::gShare->mSX.mQueueSelect >= 1) tSize = SM::gShare->mObjQueue.size();

   int tProcNum = 9;
   if (gQueueReaderThread) tProcNum = gQueueReaderThread->mThreadCurrentProcessor;

   if (mShowCode == 1)
   {
      Prn::print(Prn::Show1, "Size                     %-10lld", tSize);
      Prn::print(Prn::Show1, "WriteCount               %-10lld  %lld",
         mMon_WriteCount.mValue, mMon_WriteCount.mDelta);
      Prn::print(Prn::Show1, "WritePassCount           %-10lld  %lld",
         mMon_WritePassCount.mValue, mMon_WritePassCount.mDelta);
      Prn::print(Prn::Show1, "WriteFullCount           %-10lld", SM::gShare->mSX.mCpuWriteFullCount);

      Prn::print(Prn::Show1, "ReadCount                %-10lld  %lld",
         mMon_ReadCount.mValue, mMon_ReadCount.mDelta);
      Prn::print(Prn::Show1, "ReadPassCount            %-10lld  %lld",
         mMon_ReadPassCount.mValue, mMon_ReadPassCount.mDelta);
      Prn::print(Prn::Show1, "ReadEmptyCount           %-10lld", SM::gShare->mSX.mCpuReadEmptyCount);
      Prn::print(Prn::Show1, "ReadErrorCount           %-10lld", SM::gShare->mSX.mCpuReadErrorCount);
      Prn::print(Prn::Show1, "");
   }

   if (mShowCode == 2)
   {
      Prn::print(Prn::Show1, "%1d %3d $   WR %5lld %5lld %5lld RD %5lld %5lld %5lld ERR %lld",
         tProcNum, tSize,
         SM::gShare->mSX.mCpuWriteCount,
         SM::gShare->mSX.mCpuWritePassCount,
         SM::gShare->mSX.mCpuWriteFullCount,
         SM::gShare->mSX.mCpuReadCount,
         SM::gShare->mSX.mCpuReadPassCount,
         SM::gShare->mSX.mCpuReadEmptyCount,
         SM::gShare->mSX.mCpuReadErrorCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
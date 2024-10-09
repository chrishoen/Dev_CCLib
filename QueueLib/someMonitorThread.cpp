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
#include "someQueueReaderThread1.h"
#include "someQueueReaderThread2.h"

#define  _SOMEMONITORTHREAD1_CPP_
#include "someMonitorThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MonitorThread::MonitorThread()
{
   // Set base class variables.
   BaseClass::setThreadName("Monitor");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mMonitor);
   BaseClass::mTimerPeriod = gQueueParms.mMonitorThreadPeriod;

   // Set member variables.
   mShowCode = 0;

   // Bind member variables.
   mMon_WriteCount.bind(&SM::gShare->mSX.mWriteCount);
   mMon_ReadCount.bind(&SM::gShare->mSX.mReadCount);
}

// Update status variables.
void MonitorThread::update()
{
   mMon_WriteCount.update();
   mMon_ReadCount.update();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void MonitorThread::executeOnTimer(int aTimeCount)
{
   update();

   int tSize = -1;
   if (SM::gShare->mSX.mQueueSelect == 1) tSize = SM::gShare->mValueQueue.size();
   if (SM::gShare->mSX.mQueueSelect == 2) tSize = SM::gShare->mObjectQueue.size();

   int tProcNum = 9;
   if (gQueueReaderThread1) tProcNum = gQueueReaderThread1->mThreadCurrentProcessor;
   if (gQueueReaderThread2) tProcNum = gQueueReaderThread2->mThreadCurrentProcessor;

   if (mShowCode == 1)
   {
      Prn::print(Prn::Show1, "Size                     %-10lld", tSize);
      Prn::print(Prn::Show1, "WriteCount               %-10lld  %lld",
         mMon_WriteCount.mValue, mMon_WriteCount.mDelta);
      Prn::print(Prn::Show1, "WritePassCount           %-10lld", SM::gShare->mSX.mWritePassCount);
      Prn::print(Prn::Show1, "WriteFullCount           %-10lld", SM::gShare->mSX.mWriteFullCount);

      Prn::print(Prn::Show1, "ReadCount                %-10lld  %lld",
         mMon_ReadCount.mValue, mMon_ReadCount.mDelta);
      Prn::print(Prn::Show1, "ReadPassCount            %-10lld", SM::gShare->mSX.mReadPassCount);
      Prn::print(Prn::Show1, "ReadEmptyCount           %-10lld", SM::gShare->mSX.mReadEmptyCount);
      Prn::print(Prn::Show1, "ReadErrorCount           %-10lld", SM::gShare->mSX.mReadErrorCount);
      Prn::print(Prn::Show1, "");
   }

   if (mShowCode == 2)
   {
      Prn::print(Prn::Show1, "%1d %3d $   WR %5lld %5lld %5lld RD %5lld %5lld %5lld ERR %lld",
         tProcNum, tSize,
         SM::gShare->mSX.mWriteCount,
         SM::gShare->mSX.mWritePassCount,
         SM::gShare->mSX.mWriteFullCount,
         SM::gShare->mSX.mReadCount,
         SM::gShare->mSX.mReadPassCount,
         SM::gShare->mSX.mReadEmptyCount,
         SM::gShare->mSX.mReadErrorCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
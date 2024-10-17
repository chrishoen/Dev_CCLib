#pragma once

/*==============================================================================
Monitor thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsTimerThread.h"
#include "risMonitor.h"

namespace Some
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class QueueMonitorThread2 : public Ris::Threads::BaseTimerThread
{
public:
   typedef Ris::Threads::BaseTimerThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Select prints.
   int mShowCode;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. Monitor variables.

   // Queue buffer indices.
   Ris::Monitor<volatile int> mMon_CpuWriteCount;
   Ris::Monitor<volatile int> mMon_CpuWritePassCount;
   Ris::Monitor<volatile int> mMon_CpuReadCount;
   Ris::Monitor<volatile int> mMon_CpuReadPassCount;
   Ris::Monitor<volatile int> mMon_RpuWriteCount;
   Ris::Monitor<volatile int> mMon_RpuWritePassCount;
   Ris::Monitor<volatile int> mMon_RpuReadCount;
   Ris::Monitor<volatile int> mMon_RpuReadPassCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   QueueMonitorThread2();

   // Update monitor variables.
   void update();

   // Base class overloads.
   void executeOnTimer(int aTimeCount) override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _SOMEQUEUEMONITORTHREAD2_CPP_
          QueueMonitorThread2* gQueueMonitorThread2 = 0;
#else
   extern QueueMonitorThread2* gQueueMonitorThread2;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



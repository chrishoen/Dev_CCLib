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

class MonitorThread2 : public Ris::Threads::BaseTimerThread
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

   // Ring buffer indices.
   Ris::Monitor<long long> mMon_NextWriteIndex;
   Ris::Monitor<long long> mMon_LastReadIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   MonitorThread2();

   // Update monitor variables.
   void update();

   // Base class overloads.
   void executeOnTimer(int aTimeCount) override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _SOMEMONITORTHREAD2_CPP_
          MonitorThread2* gMonitorThread2 = 0;
#else
   extern MonitorThread2* gMonitorThread2;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



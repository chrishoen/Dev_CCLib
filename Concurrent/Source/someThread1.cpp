/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"
#include "someShare.h"
#include "GSettings.h"

#define  _SOMETHREAD1_CPP_
#include "someThread1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Thread1::Thread1() 
{
#if 0
   // Set thread priority
   BaseClass::setThreadPriorityHigh();
   BaseClass::mThreadAffinityMask = 0x20;
   BaseClass::mThreadIdealProcessor = 5;
#endif
   // Members
   mTerminateFlag = false;
}

//******************************************************************************

void Thread1::threadInitFunction()
{
   Prn::print(0,"Thread1::threadInitFunction");
}

//******************************************************************************

void Thread1::threadRunFunction()
{
   while(1)
   {
      threadSleep(1000);
      Prn::print(Prn::ThreadRun1,"Thread1::threadRunFunction");
      if (mTerminateFlag) break;
   }
}

//******************************************************************************

void Thread1::threadExitFunction()
{
   Prn::print(0,"Thread1::threadExitFunction");
}

//******************************************************************************

void Thread1::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace


/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "ccSharedMemory.h"
#include "ccSharedSynch.h"

#define  _SOMETHREAD1_CPP_
#include "someThread1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Thread1::Thread1()
{
   // Set base class thread priority
   BaseClass::setThreadPriorityHigh();
   mTerminateFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Thread1::threadRunFunction()
{
   Prn::print(Prn::ThreadRun1, "Thread1::threadRunFunction BEGIN");
   while (true)
   {
      CC::gSharedSynch.getSemaphore();
      if (mTerminateFlag) break;

      int tCount = 99999;
      if (CC::gSharedSynch.mQueue.tryRead(&tCount))
      {
         Prn::print(Prn::ThreadRun1, "CC::gSharedMemory.getSemaphore %d",tCount);
      }
      else
      {
         Prn::print(Prn::ThreadRun1, "CC::gSharedMemory.getSemaphore EMPTY");
      }
   }
   Prn::print(Prn::ThreadRun1, "Thread1::threadRunFunction END");
}

//******************************************************************************

void Thread1::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wake up thread.
   CC::gSharedSynch.putSemaphore();
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace
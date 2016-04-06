/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "ccSharedMemory.h"

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
      CC::gSharedMemory.getSemaphore();
      if (mTerminateFlag) break;
      Prn::print(Prn::ThreadRun1, "CC::gSharedMemory.getSemaphore");
   }
   Prn::print(Prn::ThreadRun1, "Thread1::threadRunFunction END");
}

//******************************************************************************

void Thread1::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wake up thread.
   CC::gSharedMemory.putSemaphore();
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace
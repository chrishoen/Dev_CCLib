/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"
#include "my_functions.h"

#include "someCallerThread.h"

#define  _SOMESTATUSTHREAD_CPP_
#include "someStatusThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

StatusThread::StatusThread() 
{
   // Thread Members
   mTerminateFlag = false;
   mTPFlag = false;

}

//******************************************************************************

void StatusThread::threadRunFunction()
{
   char tString1[40];
   while(1)
   {
      threadSleep(1000);
      if (mTerminateFlag) break;

      if (!mTPFlag) continue;

      Prn::print(Prn::ThreadRun1, "%d$   %s",
         gCallerThread->mRecursiveAnchor.mCallType,
         my_stringLLU(tString1, gCallerThread->mRecursiveAnchor.mCallCount));
   }
}

//******************************************************************************

void StatusThread::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace


/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"
#include "my_functions.h"

#include "LFFreeList.h"
#include "LFIntQueue.h"
#include "someShare.h"
#include "GSettings.h"

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
}

//******************************************************************************

void StatusThread::threadInitFunction()
{
   Prn::print(0,"StatusThread::threadInitFunction");
}

//******************************************************************************

void StatusThread::threadRunFunction()
{
   char tString1[40];
   char tString2[40];
   while(1)
   {
      threadSleep(1000);
      if (mTerminateFlag) break;

      Prn::print(Prn::ThreadRun1, "Status%d   %s   %s %8d",
         gShare.mMode,
         my_stringLLU(tString1,gShare.mWriter[0].mCount),
         my_stringLLU(tString2,gShare.mReader.mCount),
         LFIntQueue::listSize());
   }
}

//******************************************************************************

void StatusThread::threadExitFunction()
{
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


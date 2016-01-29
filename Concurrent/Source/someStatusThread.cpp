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
   char tString[40];
   while(1)
   {
      threadSleep(1000);
      if (mTerminateFlag) break;

      if (gShare.mMode != 8)
      {
         Prn::print(Prn::ThreadRun1, "Status%d   %s   %s %8d",
            gShare.mMode,
            my_stringLLU(tString,gShare.mWriter[0].mCount),
            my_stringLLU(tString,gShare.mReader.mCount),
            LFIntQueue::listSize());
      }
      else
      {
         Prn::print(Prn::ThreadRun1, "Status%d %8llu %8llu %8d",
            gShare.mMode,
            gShare.mWriter[0].mPassCount,
            gShare.mWriter[0].mFailCount,
            LFFreeList::listSize());
      }

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


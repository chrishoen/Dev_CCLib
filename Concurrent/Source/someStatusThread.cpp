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

   //Support
   mProcString[0]=0;

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
      if (gShare.mTerminateFlag) break;

      updateProcString();
      if (gShare.mMode != 8)
      {
         Prn::print(Prn::ThreadRun1, "%d %s$   %s   %s %8d",
            gShare.mMode,
            mProcString,
            my_stringLLU(tString1, gShare.mWriter[0].mCount),
            my_stringLLU(tString2, gShare.mReader.mCount),
            LFIntQueue::listSize());
      }
      else
      {
         Prn::print(Prn::ThreadRun1, "%d %s$   %s   %s %8d",
            gShare.mMode,
            mProcString,
            my_stringLLU(tString1, gShare.mWriter[0].mCount),
            my_stringLLU(tString2, gShare.mReader.mCount),
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

//******************************************************************************

void StatusThread::updateProcString()
{
   for (int i = 0; i < gShare.mNumWriters; i++)
   {
      mProcString[i] = '0' + gShare.mWriterProcessor[i];
   }
   mProcString[gShare.mNumWriters] = '0' + gShare.mReaderProcessor;
   mProcString[gShare.mNumWriters+1] = 0;

}
}//namespace


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
      switch (gShare.mMode)
      {
         case 1:
         {
            int tQueueSize;
            if (gShare.mType==1) tQueueSize = LFIntQueue::size();
            if (gShare.mType==2) tQueueSize = gShare.mPointerQueue.size();
            if (gShare.mType==3) tQueueSize = gShare.mBlockQueue.size();
            if (gShare.mType==4) tQueueSize = gShare.mBlockFreeList.size();
            Prn::print(Prn::ThreadRun1, "%s$   %s   %s %8d",
               mProcString,
               my_stringLLU(tString1, gShare.mWriter[0].mCount),
               my_stringLLU(tString2, gShare.mReader.mCount),
               tQueueSize);
         }
         break;
         case 2:
         {
            int tQueueSize;
            if (gShare.mType==1) tQueueSize = LFIntQueue::size();
            if (gShare.mType==2) tQueueSize = gShare.mPointerQueue.size();
            if (gShare.mType==3) tQueueSize = gShare.mBlockQueue.size();
            if (gShare.mType==4) tQueueSize = gShare.mBlockFreeList.size();
            Prn::print(Prn::ThreadRun1, "%s$   %s   %s %8d",
               mProcString,
               my_stringLLU(tString1, gShare.mWriterReader[0].mWriteCount),
               my_stringLLU(tString2, gShare.mWriterReader[0].mReadCount),
               tQueueSize);
         }
         break;
         case 3:
         {
            Prn::print(Prn::ThreadRun1, "%s$%d   %s",
               mProcString,
               gShare.mTest,
               my_stringLLU(tString1, gShare.mTester.mCount));
         }
         break;
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


/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <Windows.h>
#include "prnPrint.h"
#include "my_functions.h"

#define  _SOMECALLERTHREAD_CPP_
#include "someCallerThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

CallerThread::CallerThread() 
{
   // BaseClass
   BaseClass::setThreadPriorityHigh();

   BaseClass::mThreadAffinityMask = 0x20;
   BaseClass::mThreadIdealProcessor = 5;

   // Thread Members
   mTerminateFlag = false;

   mCallFlag = false;;
   mDelay = 100;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CallerThread::abortCall()
{
   mCallFlag=false;
}

void CallerThread::callFunction(RecursiveFunction aFunction)
{
   if (mCallQueue.isPut())
   {
      mCallQueue.put(aFunction);
      mRecursiveAnchor.reset();
      mCallFlag=true;
   }
}

void CallerThread::enqueueFunction(RecursiveFunction aFunction)
{
   if (!mCallFlag) return;

   if (mCallQueue.isPut())
   {
      mCallQueue.put(aFunction);
   }
}
//******************************************************************************

void CallerThread::threadRunFunction()
{
   while (!mTerminateFlag)
   {
      threadSleep(mDelay);
      if (mCallFlag && mCallQueue.isGet())
      {
         RecursiveFunction tFunction;
         mCallQueue.get(tFunction);
         tFunction(&mRecursiveAnchor);
         mRecursiveAnchor.mCount++;
      }
      else
      {
//       threadSleep(mDelay);
      }
   }
}

//******************************************************************************

void CallerThread::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace


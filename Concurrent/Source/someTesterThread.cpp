/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <Windows.h>

#include "someShare.h"
#include "GSettings.h"

#define  _SOMETESTERTHREAD_CPP_
#include "someTesterThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

TesterThread::TesterThread() 
{
   // Settings Members
   mSleepLower = gGSettings.mSleepLower;
   mSleepUpper = gGSettings.mSleepUpper;
   mWriteLower = gGSettings.mWriteLower;
   mWriteUpper = gGSettings.mWriteUpper;

   // BaseClass
   BaseClass::setThreadPriorityHigh();

   BaseClass::mThreadAffinityMask = 0x02;
   BaseClass::mThreadIdealProcessor = 1;

   // Thread Members
   mTerminateFlag = false;
}

//******************************************************************************

void TesterThread::threadInitFunction()
{
   Prn::print(0,"TesterThread::threadInitFunction");
}

//******************************************************************************

void TesterThread::threadRunFunction()
{
   try
   {
      gShare.mTester.startTrial();
      while (1)
      {
         // Sleep
         threadSleep(my_irand(mSleepLower, mSleepUpper));
         // Thread loop termination
         if (gGSettings.mTerminate != 0)
         {
            if (gShare.mTester.mCount > gGSettings.mTerminate)
            {
               gShare.mTerminateFlag = true;
            }
         }
         if (mTerminateFlag) break;
         if (gShare.mTerminateFlag) break;

         // Write
         gShare.mWriterProcessor[0] = GetCurrentProcessorNumber();
         gShare.mTester.test(my_irand(mWriteLower, mWriteUpper));
      }
      gShare.mTester.finishTrial();
   }
   catch (...)
   {
      Ris::Threads::halt("TesterThread::exception");
   }
}

//******************************************************************************

void TesterThread::threadExitFunction()
{
   gShare.mTester.show();
}

//******************************************************************************

void TesterThread::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace


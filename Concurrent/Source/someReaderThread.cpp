/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <Windows.h>
#include "prnPrint.h"
#include "my_functions.h"
#include "someShare.h"
#include "GSettings.h"
#include "LFBackoff.h"

#define  _SOMEREADERTHREAD_CPP_
#include "someReaderThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

ReaderThread::ReaderThread() 
{
   // BaseClass
   BaseClass::setThreadPriorityHigh();

   // Thread Members
   mTerminateFlag = false;
   mSleepLower = gGSettings.mSleepLower;
   mSleepUpper = gGSettings.mSleepUpper;

   // Writer Members
   mReadLower = gGSettings.mReadLower;
   mReadUpper = gGSettings.mReadUpper;
}

//******************************************************************************

void ReaderThread::threadInitFunction()
{
   Prn::print(0,"ReaderThread::threadInitFunction");
   LFBackoff::initialize(gGSettings.mBackoff1,gGSettings.mBackoff2);
   gShare.mReader.initialize();
}

//******************************************************************************

void ReaderThread::threadRunFunction()
{
   try
   {
      while (1)
      {
         threadSleep(my_irand(mSleepLower, mSleepUpper));
         if (mTerminateFlag) break;
         gShare.mReaderProc = GetCurrentProcessorNumber();
         gShare.mReader.read(my_irand(mReadLower, mReadUpper));
      }
   }
   catch (...)
   {
      Ris::Threads::halt("ReaderThread::exception");
   }
}

//******************************************************************************

void ReaderThread::threadExitFunction()
{
   gShare.mReader.flush();
   gShare.mReader.show();
}

//******************************************************************************

void ReaderThread::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace


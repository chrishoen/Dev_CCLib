/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"
#include "my_functions.h"
#include "someShare.h"
#include "GSettings.h"

#define  _SOMEREADERTHREAD_CPP_
#include "someReaderThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

ReaderThread::ReaderThread() 
{
#if 0
   // Set thread priority
   BaseClass::setThreadPriorityHigh();
   BaseClass::mThreadAffinityMask = 0x20;
   BaseClass::mThreadIdealProcessor = 5;
#endif

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
   gShare.mReader.initialize();
}

//******************************************************************************

void ReaderThread::threadRunFunction()
{
   while(1)
   {
      threadSleep(my_irand(mSleepLower,mSleepUpper));
      if (mTerminateFlag) break;

      gShare.mReader.read(my_irand(mReadLower,mReadUpper));
   }
}

//******************************************************************************

void ReaderThread::threadExitFunction()
{
   gShare.mReader.read();
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

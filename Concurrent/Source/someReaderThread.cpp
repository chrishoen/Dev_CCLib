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
   mSleepLower =  900;
   mSleepUpper = 1000;

   // Reader Members
   mReadLower =  900;
   mReadUpper = 1100;
}

//******************************************************************************

void ReaderThread::threadInitFunction()
{
   Prn::print(0,"ReaderThread::threadInitFunction");
   mReader.initialize();
}

//******************************************************************************

void ReaderThread::threadRunFunction()
{
   while(1)
   {
      threadSleep(my_irand(mSleepLower,mSleepUpper));
      if (mTerminateFlag) break;

      mReader.read(my_irand(mReadLower,mReadUpper));
   }
}

//******************************************************************************

void ReaderThread::threadExitFunction()
{
   Prn::print(0,"ReaderThread::threadExitFunction");
   mReader.read(0);
   mReader.show();
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


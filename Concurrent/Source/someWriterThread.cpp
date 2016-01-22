/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"
#include "my_functions.h"
#include "someShare.h"
#include "GSettings.h"

#define  _SOMEWRITERTHREAD_CPP_
#include "someWriterThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

WriterThread::WriterThread() 
{
#if 0
   // Set thread priority
   BaseClass::setThreadPriorityHigh();
   BaseClass::mThreadAffinityMask = 0x20;
   BaseClass::mThreadIdealProcessor = 5;
#endif

   // Thread Members
   mTerminateFlag = false;
   mSleepLower = 900;
   mSleepUpper = 1000;

   // Writer Members
   mWriteLower =  9000;
   mWriteUpper = 11000;
}

//******************************************************************************

void WriterThread::threadInitFunction()
{
   Prn::print(0,"WriterThread::threadInitFunction");
}

//******************************************************************************

void WriterThread::threadRunFunction()
{
   while(1)
   {
      threadSleep(my_irand(mSleepLower,mSleepUpper));
      if (mTerminateFlag) break;

      gShare.mWriter.write(my_irand(mWriteLower,mWriteUpper));

   }
}

//******************************************************************************

void WriterThread::threadExitFunction()
{
   gShare.mWriter.show();
}

//******************************************************************************

void WriterThread::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace


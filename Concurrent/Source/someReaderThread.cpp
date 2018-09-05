/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "someShare.h"
#include "Parms.h"

#define  _SOMEREADERTHREAD_CPP_
#include "someReaderThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

ReaderThread::ReaderThread() 
{
   // Settings Members
   mSleepLower = gParms.mSleepLower;
   mSleepUpper = gParms.mSleepUpper;
   mReadLower  = gParms.mReadLower;
   mReadUpper  = gParms.mReadUpper;

   // BaseClass
   BaseClass::setThreadPriorityHigh();

   BaseClass::mThreadAffinityMask = 0x02;
   BaseClass::mThreadIdealProcessor = 1;

   // Thread Members
   mTerminateFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ReaderThread::threadInitFunction()
{
   Prn::print(0,"ReaderThread::threadInitFunction");
   gShare.mReader.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ReaderThread::threadRunFunction()
{
   if (gShare.mMode==8) return;
   try
   {
      gShare.mReader.startTrial();
      while (1)
      {
         // Sleep
         threadSleep(my_irand(mSleepLower, mSleepUpper));
         if (mTerminateFlag) break;
         if (gShare.mTerminateFlag) break;

         // Read 
         gShare.mReaderProcessor = BaseClass::getThreadProcessorNumber();
         gShare.mReader.read(my_irand(mReadLower, mReadUpper));
      }
      gShare.mReader.finishTrial();
   }
   catch (...)
   {
      Ris::Threads::halt("ReaderThread::exception");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ReaderThread::threadExitFunction()
{
   gShare.mReader.flush();
   gShare.mReader.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ReaderThread::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wait for terminate
   waitForThreadTerminate();
}   

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


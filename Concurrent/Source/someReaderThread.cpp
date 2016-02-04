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
   BaseClass::setThreadPriorityLow();

   BaseClass::mThreadAffinityMask = 0x02;
   BaseClass::mThreadIdealProcessor = 1;

   // Thread Members
   mTerminateFlag = false;
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
   if (gShare.mMode==8) return;
   try
   {
      gShare.mReader.startTrial();
      while (1)
      {
         if (mTerminateFlag) break;
         if (gShare.mTerminateFlag) break;

         gShare.mReaderProc = GetCurrentProcessorNumber();
         gShare.mReader.read(10000);
      }
      gShare.mReader.finishTrial();
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


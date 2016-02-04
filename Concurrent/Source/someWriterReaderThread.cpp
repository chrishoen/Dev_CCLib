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

#define  _SOMEWRITERTHREAD_CPP_
#include "someWriterReaderThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

WriterReaderThread::WriterReaderThread(int aIdent) 
{
   // BaseClass
   BaseClass::setThreadPriorityLow();

   switch (aIdent)
   {
   case 0:
      BaseClass::mThreadAffinityMask = 0x04;
      BaseClass::mThreadIdealProcessor = 2;
      break;
   case 1:
      BaseClass::mThreadAffinityMask = 0x08;
      BaseClass::mThreadIdealProcessor = 3;
      break;
   case 2:
      BaseClass::mThreadAffinityMask = 0x10;
      BaseClass::mThreadIdealProcessor = 4;
      break;
   case 3:
      BaseClass::mThreadAffinityMask = 0x20;
      BaseClass::mThreadIdealProcessor = 5;
      break;
   }

   // Thread Members
   mTerminateFlag = false;
   mIdent = aIdent;
}

//******************************************************************************

void WriterReaderThread::threadInitFunction()
{
   Prn::print(0,"WriterReaderThread::threadInitFunction");
}

//******************************************************************************

void WriterReaderThread::threadRunFunction()
{
   try
   {
      gShare.mWriterReader[mIdent].startTrial();
      while (1)
      {
         // Thread loop termination
         if (gGSettings.mTerminate != 0)
         {
            if (gShare.mWriterReader[mIdent].mWriteCount > gGSettings.mTerminate)
            {
               gShare.mTerminateFlag = true;
            }
         }
         if (mTerminateFlag) break;
         if (gShare.mTerminateFlag) break;

         // Write
         gShare.mWriterProcessor[mIdent] = GetCurrentProcessorNumber();
         gShare.mWriterReader[mIdent].writeread(10000);
      }
      gShare.mWriterReader[mIdent].finishTrial();
   }
   catch (...)
   {
      Ris::Threads::halt("WriterReaderThread::exception");
   }
}

//******************************************************************************

void WriterReaderThread::threadExitFunction()
{
   gShare.mWriterReader[mIdent].show();
}

//******************************************************************************

void WriterReaderThread::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace


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
#include "someWriterThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

WriterThread::WriterThread(int aIdent) 
{
   // BaseClass
   BaseClass::setThreadPriorityHigh();

   // Thread Members
   mTerminateFlag = false;
   mSleepLower = gGSettings.mSleepLower;
   mSleepUpper = gGSettings.mSleepUpper;

   // Writer Members
   mWriteLower = gGSettings.mWriteLower;
   mWriteUpper = gGSettings.mWriteUpper;
   mIdent = aIdent;
}

//******************************************************************************

void WriterThread::threadInitFunction()
{
   Prn::print(0,"WriterThread::threadInitFunction");
}

//******************************************************************************

void WriterThread::threadRunFunction()
{
   try
   {
      while (1)
      {
         threadSleep(my_irand(mSleepLower, mSleepUpper));

         if (gGSettings.mTerminate != 0)
         {
            if (gShare.mWriter[mIdent].mCount > gGSettings.mTerminate)
            {
               gShare.mTerminateFlag = true;
            }
         }
         if (mTerminateFlag) break;
         if (gShare.mTerminateFlag) break;

         gShare.mWriterProc[mIdent] = GetCurrentProcessorNumber();
         gShare.mWriter[mIdent].write(my_irand(mWriteLower, mWriteUpper));

      }
   }
   catch (...)
   {
      Ris::Threads::halt("WriterThread::exception");
   }
}

//******************************************************************************

void WriterThread::threadExitFunction()
{
   gShare.mWriter[mIdent].show();
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


/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"

#define  _SOMETHREADS_CPP_
#include "someThreads.h"
namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Threads::Threads()
{
   mWriterThread=0;
   mReaderThread=0;
   mStatusThread=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::start()
{
   Prn::print(0,"Threads::start*******************************");

   mReaderThread = new ReaderThread;
   mReaderThread->launchThread();

   mWriterThread = new WriterThread;
   mWriterThread->launchThread();

   mStatusThread = new StatusThread;
   mStatusThread->launchThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::stop()
{
   Prn::print(0,"Threads::stopping****************************");
   Prn::print(0,"");

   if (mStatusThread)
   {
      mStatusThread->shutdownThread();
      delete mStatusThread;
      mStatusThread = 0;
   }

   if (mWriterThread)
   {
      mWriterThread->shutdownThread();
      delete mWriterThread;
      mWriterThread = 0;
   }

   if (mReaderThread)
   {
      mReaderThread->shutdownThread();
      delete mReaderThread;
      mReaderThread = 0;
   }

   Prn::print(0,"Threads::stopped*****************************");
}

}//namespace

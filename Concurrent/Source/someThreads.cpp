/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
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
   mWriterThread = new WriterThread;
   mWriterThread->launchThread();

   mReaderThread = new ReaderThread;
   mReaderThread->launchThread();

   mStatusThread = new StatusThread;
   mStatusThread->launchThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::stop()
{
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

   if (mStatusThread)
   {
      mStatusThread->shutdownThread();
      delete mStatusThread;
      mStatusThread = 0;
   }
}

}//namespace

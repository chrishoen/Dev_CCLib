/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "prnPrint.h"
#include "GSettings.h"

#define  _SOMETHREADS_CPP_
#include "someThreads.h"
namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Threads::Threads()
{
   reset();
}

void Threads::reset()
{
   mNumWriters = gGSettings.mNumWriters;
   if (mNumWriters > cMaxNumWriters) mNumWriters = cMaxNumWriters;

   for (int i=0;i<cMaxNumWriters;i++) mWriterThread[i]=0;
   mReaderThread=0;
   mStatusThread=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::start()
{
   Prn::print(0,"Threads::start*******************************");
   reset();

   mReaderThread = new ReaderThread;
   mReaderThread->launchThread();

   for (int i = 0; i < mNumWriters; i++)
   {
      mWriterThread[i] = new WriterThread(i);
      mWriterThread[i]->launchThread();
   }

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

   for (int i = 0; i < mNumWriters; i++)
   {
      if (mWriterThread[i])
      {
         mWriterThread[i]->shutdownThread();
         delete mWriterThread[i];
         mWriterThread[i] = 0;
      }
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

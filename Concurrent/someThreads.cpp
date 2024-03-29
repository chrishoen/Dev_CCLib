/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "Parms.h"
#include "someShare.h"

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
   mNumWriters = gParms.mNumWriters;
   if (mNumWriters > cMaxNumWriters) mNumWriters = cMaxNumWriters;

   for (int i = 0; i < cMaxNumWriters; i++)
   {
      mWriterThread[i] = 0;
   }

   mReaderThread=0;
   mTesterThread=0;
   mStatusThread=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::start1()
{
   Prn::print(0,"Threads::start1******************************* %d",gShare.mType);
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

void Threads::start2()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::start3()
{
   Prn::print(0,"Threads::start7*******************************");
   reset();

   mTesterThread = new TesterThread;
   mTesterThread->launchThread();

   mStatusThread = new StatusThread;
   mStatusThread->launchThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::start4()
{
   Prn::print(0, "Threads::start4******************************* %d", gShare.mType);
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

void Threads::stop1()
{
   Prn::print(0,"Threads::stopping1****************************");
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

   Prn::print(0,"Threads::stopped1*****************************");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::stop2()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::stop3()
{
   Prn::print(0,"Threads::stopping3****************************");
   Prn::print(0,"");

   if (mStatusThread)
   {
      mStatusThread->shutdownThread();
      delete mStatusThread;
      mStatusThread = 0;
   }

   if (mTesterThread)
   {
      mTesterThread->shutdownThread();
      delete mTesterThread;
      mTesterThread = 0;
   }

   Prn::print(0,"Threads::stopped3*****************************");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::stop4()
{
   Prn::print(0, "Threads::stopping4****************************");
   Prn::print(0, "");

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

   Prn::print(0, "Threads::stopped4*****************************");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::start()
{
   switch (gShare.mMode)
   {
   case 1: start1(); break;
   case 2: start2(); break;
   case 3: start3(); break;
   case 4: start4(); break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Threads::stop()
{
   switch (gShare.mMode)
   {
   case 1: stop1(); break;
   case 2: stop2(); break;
   case 3: stop3(); break;
   case 4: stop4(); break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

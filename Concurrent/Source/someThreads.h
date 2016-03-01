#ifndef _SOMETHREADS_H_
#define _SOMETHREADS_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "someWriterThread.h"
#include "someReaderThread.h"
#include "someWriterReaderThread.h"
#include "someTesterThread.h"
#include "someStatusThread.h"


namespace Some
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class Threads
{
public:
   Threads();

   void reset();

   void start1();
   void start2();
   void start3();
   void start();

   void stop1();
   void stop2();
   void stop3();
   void stop();

   static const int cMaxNumWriters = 10;
   int mNumWriters;

   WriterThread*       mWriterThread       [cMaxNumWriters];
   WriterReaderThread* mWriterReaderThread [cMaxNumWriters];
   ReaderThread*       mReaderThread;
   TesterThread*       mTesterThread;
   StatusThread*       mStatusThread;
};

//******************************************************************************
// Global instance

#ifdef _SOMETHREADS_CPP_
          Threads gThreads;
#else
   extern Threads gThreads;
#endif

//******************************************************************************
}//namespace

#endif

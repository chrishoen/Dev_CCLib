#ifndef _SOMETHREADS_H_
#define _SOMETHREADS_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "someWriterThread.h"
#include "someReaderThread.h"
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
   void start();
   void stop();

   static const int cMaxNumWriters = 10;
   WriterThread* mWriterThread[cMaxNumWriters];
   int mNumWriters;

   ReaderThread* mReaderThread;
   StatusThread* mStatusThread;
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

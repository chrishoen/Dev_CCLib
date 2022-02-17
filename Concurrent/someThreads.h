#pragma once

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "someWriterThread.h"
#include "someReaderThread.h"
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
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxNumWriters = 10;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   int mNumWriters;

   WriterThread*       mWriterThread[cMaxNumWriters];
   ReaderThread*       mReaderThread;
   TesterThread*       mTesterThread;
   StatusThread*       mStatusThread;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   Threads();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   void start1();
   void start2();
   void start3();
   void start4();
   void start();

   void stop1();
   void stop2();
   void stop3();
   void stop4();
   void stop();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SOMETHREADS_CPP_
          Threads gThreads;
#else
   extern Threads gThreads;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

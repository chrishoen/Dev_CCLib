#ifndef _SOMEWRITERREADERTHREAD_H_
#define _SOMEWRITERREADERTHREAD_H_

/*==============================================================================

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risThreadsThreads.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class WriterReaderThread : public Ris::Threads::BaseThread
{
public:

   // Constructor
   typedef Ris::Threads::BaseThread BaseClass;
   WriterReaderThread(int aIdent); 

   //Base class overloads.
   void threadInitFunction();
   void threadRunFunction();
   void threadExitFunction();
   void shutdownThread();

   // Writer Members
   int    mIdent;

   // Thread Members
   bool  mTerminateFlag;
   int   mWriteLower;
   int   mWriteUpper;
   int   mSleepLower;
   int   mSleepUpper;
};

//******************************************************************************
}//namespace

#endif


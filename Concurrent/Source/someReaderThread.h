#ifndef _SOMEREADERTHREAD_H_
#define _SOMEREADERTHREAD_H_

/*==============================================================================

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risThreads.h"
#include "someReader.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class ReaderThread : public Ris::Threads::BaseThread
{
public:

   // Constructor
   typedef Ris::Threads::BaseThread BaseClass;
   ReaderThread(); 

   //Base class overloads.
   void threadInitFunction();
   void threadRunFunction();
   void threadExitFunction();
   void shutdownThread();

   // Reader Members
   Reader mReader;
   int    mReadLower;
   int    mReadUpper;

   // Thread Members
   bool  mTerminateFlag;
   int   mSleepLower;
   int   mSleepUpper;
};

//******************************************************************************
}//namespace

#endif


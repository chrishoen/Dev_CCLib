#ifndef _SOMEREADERTHREAD_H_
#define _SOMEREADERTHREAD_H_

/*==============================================================================

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risThreads.h"

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

   // Thread Members
   bool  mTerminateFlag;
   int   mReadLower;
   int   mReadUpper;
   int   mSleepLower;
   int   mSleepUpper;
};

//******************************************************************************
}//namespace

#endif


#ifndef _SOMEWRITERTHREAD_H_
#define _SOMEWRITERTHREAD_H_

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

class WriterThread : public Ris::Threads::BaseThread
{
public:

   // Constructor
   typedef Ris::Threads::BaseThread BaseClass;
   WriterThread(); 

   //Base class overloads.
   void threadInitFunction();
   void threadRunFunction();
   void threadExitFunction();
   void shutdownThread();

   // Writeer Members
   int    mWriteLower;
   int    mWriteUpper;

   // Thread Members
   bool  mTerminateFlag;
   int   mSleepLower;
   int   mSleepUpper;
};

//******************************************************************************
}//namespace

#endif


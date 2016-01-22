#ifndef _SOMEWRITERTHREAD_H_
#define _SOMEWRITERTHREAD_H_

/*==============================================================================

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risThreads.h"
#include "someWriter.h"

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
   Writer mWriter;
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


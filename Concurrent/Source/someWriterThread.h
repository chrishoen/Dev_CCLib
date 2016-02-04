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
   WriterThread(int aIdent); 

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


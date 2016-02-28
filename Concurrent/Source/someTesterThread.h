#ifndef _SOMETESTERTHREAD_H_
#define _SOMETESTERTHREAD_H_

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

class TesterThread : public Ris::Threads::BaseThread
{
public:

   // Constructor
   typedef Ris::Threads::BaseThread BaseClass;
   TesterThread(); 

   //Base class overloads.
   void threadInitFunction();
   void threadRunFunction();
   void threadExitFunction();
   void shutdownThread();

   // Tester Members
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


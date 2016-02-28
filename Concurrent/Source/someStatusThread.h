#ifndef _SOMESTATUSTHREAD_H_
#define _SOMESTATUSTHREAD_H_

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

class StatusThread : public Ris::Threads::BaseThread
{
public:

   // Constructor
   typedef Ris::Threads::BaseThread BaseClass;
   StatusThread(); 

   //Base class overloads.
   void threadInitFunction();
   void threadRunFunction();
   void threadExitFunction();
   void shutdownThread();

   // Thread Members
   bool  mTerminateFlag;

   // Support
   void updateProcString();
   char mProcString[20];
};

//******************************************************************************
}//namespace

#endif


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
   void threadRunFunction();
   void shutdownThread();

   // Thread Members
   bool  mTerminateFlag;
   bool  mTPFlag;

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef   _SOMESTATUSTHREAD_CPP_
          StatusThread* gStatusThread;
#else
   extern StatusThread* gStatusThread;
#endif

//******************************************************************************
}//namespace

#endif


#ifndef _SOMEWRITERREADERTHREAD_H_
#define _SOMEWRITERREADERTHREAD_H_

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
};

//******************************************************************************
}//namespace

#endif


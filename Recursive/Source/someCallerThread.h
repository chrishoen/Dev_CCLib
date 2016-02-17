#ifndef _SOMECALLERTHREAD_H_
#define _SOMECALLERTHREAD_H_

/*==============================================================================

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <functional>
#include "risThreads.h"
#include "risContainers.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class RecursiveAnchor
{
public:
   int mCount;

   inline RecursiveAnchor()
   {
      reset();
   }

   inline void reset()
   {
      mCount=0;
   }

};

typedef std::function<void(RecursiveAnchor*)> RecursiveFunction;

//******************************************************************************
//******************************************************************************
//******************************************************************************

class CallerThread : public Ris::Threads::BaseThread
{
public:
   //---------------------------------------------------------------------------
   // Class

   typedef Ris::Threads::BaseThread BaseClass;

   CallerThread(); 

   // Thread base class overloads.
   void threadRunFunction();
   void shutdownThread();

   // Thread Members
   bool  mTerminateFlag;

   //---------------------------------------------------------------------------
   // Caller Members

   RecursiveAnchor mRecursiveAnchor;
   bool mCallFlag;
   int  mDelay;
   Ris::Containers::Queue<RecursiveFunction,100> mCallQueue;

   void abortCall();
   void callFunction(RecursiveFunction aFunction);
   void enqueueFunction(RecursiveFunction aFunction);

};

//******************************************************************************
// Global instance

#ifdef   _SOMECALLERTHREAD_CPP_
          CallerThread* gCallerThread;
#else
   extern CallerThread* gCallerThread;
#endif

//******************************************************************************
}//namespace

#endif


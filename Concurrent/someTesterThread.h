#pragma once

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
   typedef Ris::Threads::BaseThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Tester Members.
   int    mIdent;

   // Thread Members.
   bool  mTerminateFlag;
   int   mWriteLower;
   int   mWriteUpper;
   int   mSleepLower;
   int   mSleepUpper;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   TesterThread(); 

   // Base class overloads.
   void threadInitFunction();
   void threadRunFunction();
   void threadExitFunction();
   void shutdownThread();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


#pragma once

/*==============================================================================
This file provides a set of variables that are used to define thread
priorities and processor number for threads in these programs.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsPriorities.h"

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a set of variables that are used to define thread
// priorities and thread single processor numbers for threads in these
// programs.

class Priorities
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   Ris::Threads::Priority mMasterLong;
   Ris::Threads::Priority mMasterShort;
   Ris::Threads::Priority mSlave;
   Ris::Threads::Priority mTimer;
   Ris::Threads::Priority mQCall;

   Ris::Threads::Priority mProc;
   Ris::Threads::Priority mSerial;
   Ris::Threads::Priority mMonitor;

   Ris::Threads::Priority mStrobe;
   Ris::Threads::Priority mSend;
   Ris::Threads::Priority mRecv;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   Priorities();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _CMNPRIORITIES_CPP_
          Priorities gPriorities;
#else
   extern Priorities gPriorities;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


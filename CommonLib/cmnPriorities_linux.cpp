/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _CMNPRIORITIES_CPP_
#include "cmnPriorities.h"

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

Priorities::Priorities()
{
   mMasterLong        = Ris::Threads::Priority(-1, 50);
   mMasterShort       = Ris::Threads::Priority(-1, 80);
   mSlave             = Ris::Threads::Priority(-1, 60);
   mTimer             = Ris::Threads::Priority(-1, 82);
   mQCall             = Ris::Threads::Priority(-1, 60);

   mProc              = Ris::Threads::Priority(-1, 11);
   mSerial            = Ris::Threads::Priority(-1, 10);
   mMonitor           = Ris::Threads::Priority(-1, 60);

   mStrobe            = Ris::Threads::Priority(-1, 98);
   mSend              = Ris::Threads::Priority(-1, 97);
   mRecv              = Ris::Threads::Priority(-1, 98);

   mRingWriter        = Ris::Threads::Priority(-1, 81);
   mRingReader        = Ris::Threads::Priority(-1, 80);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

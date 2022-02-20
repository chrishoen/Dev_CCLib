//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMERINGPARMS_CPP_
#include "someRingParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

RingParms::RingParms()
{
   reset();
}

void RingParms::reset()
{
   BaseClass::reset();
   if (Ris::portableIsWindows())
   {
      BaseClass::setFilePath("c:/aaa_prime/files/Ring_Parms.txt");
   }
   else
   {
      BaseClass::setFilePath_RelativeToBaseDir("files/Ring_Parms.txt");
   }

   mTestMode = 1;
   mMonitorThreadPeriod = 0;
   mStatPeriod = 0;
   mPollProcessor = false;

   mWriterThreadProcessor = -1;
   mWriterThreadPriority = 80;
   mWriterThreadPeriodUs1 = 0;
   mWriterThreadPeriodUs2 = 0;

   mReaderThreadProcessor = -1;
   mReaderThreadPriority = 80;
   mReaderThreadPeriodUs1 = 0;
   mReaderThreadPeriodUs2 = 0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void RingParms::show()
{
   printf("\n");
   printf("RingParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("TestMode                 %-10d\n", mTestMode);
   printf("\n");
   printf("MonitorThreadPeriod      %-10d\n", mMonitorThreadPeriod);
   printf("StatPeriod               %-10d\n", mStatPeriod);
   printf("PollProcessor            %-10s\n", my_string_from_bool(mPollProcessor));
   printf("\n");
   printf("WriterThreadProcessor    %-10d\n", mWriterThreadProcessor);
   printf("WriterThreadPriority     %-10d\n", mWriterThreadPriority);
   printf("WriterThreadPeriodUs     %-10d  %-10d\n", mWriterThreadPeriodUs1, mWriterThreadPeriodUs2);
   printf("\n");
   printf("ReaderThreadProcessor    %-10d\n", mReaderThreadProcessor);
   printf("ReaderThreadPriority     %-10d\n", mReaderThreadPriority);
   printf("ReaderThreadPeriodUs     %-10d  %-10d\n", mReaderThreadPeriodUs1, mReaderThreadPeriodUs2);
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void RingParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TestMode"))                mTestMode = aCmd->argInt(1);

   if (aCmd->isCmd("MonitorThreadPeriod"))     mMonitorThreadPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("StatPeriod"))              mStatPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("PollProcessor"))           mPollProcessor = aCmd->argBool(1);

   if (aCmd->isCmd("WriterThreadProcessor"))   mWriterThreadProcessor = aCmd->argInt(1);
   if (aCmd->isCmd("WriterThreadPriority"))    mWriterThreadPriority = aCmd->argInt(1);
   if (aCmd->isCmd("WriterThreadPeriodUs"))
   {
      mWriterThreadPeriodUs1 = aCmd->argInt(1);
      mWriterThreadPeriodUs2 = aCmd->argInt(2);
   }

   if (aCmd->isCmd("ReaderThreadProcessor"))   mReaderThreadProcessor = aCmd->argInt(1);
   if (aCmd->isCmd("ReaderThreadPriority"))    mReaderThreadPriority = aCmd->argInt(1);
   if (aCmd->isCmd("ReaderThreadPeriodUs"))
   {
      mReaderThreadPeriodUs1 = aCmd->argInt(1);
      mReaderThreadPeriodUs2 = aCmd->argInt(2);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void RingParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
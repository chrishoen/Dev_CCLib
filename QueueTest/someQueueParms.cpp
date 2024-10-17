//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMEQUEUEPARMS_CPP_
#include "someQueueParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

QueueParms::QueueParms()
{
   reset();
}

void QueueParms::reset()
{
   BaseClass::reset();
   if (Ris::portableIsWindows())
   {
      BaseClass::setFilePath("c:/aaa_prime/files/Queue_Parms.txt");
   }
   else
   {
      BaseClass::setFilePath_RelativeToBaseDir("files/Queue_Parms.txt");
   }

   mScope = 1;
   mSelect = 1;
   mMonitorThreadPeriod = 0;
   mStatPeriod = 0;
   mPollProcessor = false;

   mWriterThreadProcessor = -1;
   mWriterThreadPriority = 80;
   mWriterThreadMeanMs = 0;
   mWriterThreadRandomUs = 0;

   mReaderThreadProcessor = -1;
   mReaderThreadPriority = 80;

   mWriteTestMode = 0;
   mReadTestMode = 0;
   mNumWrites = 1;
   mReadSleepMeanMs = 0;
   mReadSleepRandomUs = 0;

   mWriteSuspendRandom = 0;
   mReadSuspendRandom = 0;
   mSuspendSleepMeanMs = 0;
   mSuspendSleepRandomMs = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void QueueParms::show()
{
   printf("\n");
   printf("QueueParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("Scope                        %-10d\n", mScope);
   printf("Select                       %-10d\n", mSelect);

   printf("\n");
   printf("MonitorThreadPeriod          %-10d\n", mMonitorThreadPeriod);
   printf("StatPeriod                   %-10d\n", mStatPeriod);
   printf("PollProcessor                %-10s\n", my_string_from_bool(mPollProcessor));
   printf("\n");
   printf("WriterThreadProcessor        %-10d\n", mWriterThreadProcessor);
   printf("WriterThreadPriority         %-10d\n", mWriterThreadPriority);
   printf("WriterThreadMeanMs           %-10d\n", mWriterThreadMeanMs);
   printf("WriterThreadRandomUs         %-10d\n", mWriterThreadRandomUs);
   printf("\n");
   printf("ReaderThreadProcessor        %-10d\n", mReaderThreadProcessor);
   printf("ReaderThreadPriority         %-10d\n", mReaderThreadPriority);
   printf("\n");
   printf("WriteTestMode                %-10d\n", mWriteTestMode);
   printf("ReadTestMode                 %-10d\n", mReadTestMode);
   printf("NumWrites                    %-10d\n", mNumWrites);
   printf("\n");
   printf("ReadSleepMeanMs              %-10d\n", mReadSleepMeanMs);
   printf("ReadSleepRandomUs            %-10d\n", mReadSleepRandomUs);
   printf("\n");
   printf("WriteSuspendRandom           %-10d\n", mWriteSuspendRandom);
   printf("ReadSuspendRandom            %-10d\n", mReadSuspendRandom);
   printf("SuspendSleepMeanMs           %-10d\n", mSuspendSleepMeanMs);
   printf("SuspendSleepRandomMs         %-10d\n", mSuspendSleepRandomMs);
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void QueueParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("Scope"))                   mScope = aCmd->argInt(1);
   if (aCmd->isCmd("Select"))                  mSelect = aCmd->argInt(1);

   if (aCmd->isCmd("MonitorThreadPeriod"))     mMonitorThreadPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("StatPeriod"))              mStatPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("PollProcessor"))           mPollProcessor = aCmd->argBool(1);

   if (aCmd->isCmd("WriterThreadProcessor"))   mWriterThreadProcessor = aCmd->argInt(1);
   if (aCmd->isCmd("WriterThreadPriority"))    mWriterThreadPriority = aCmd->argInt(1);
   if (aCmd->isCmd("WriterThreadMeanMs"))      mWriterThreadMeanMs = aCmd->argInt(1);
   if (aCmd->isCmd("WriterThreadRandomUs"))    mWriterThreadRandomUs = aCmd->argInt(1);

   if (aCmd->isCmd("ReaderThreadProcessor"))   mReaderThreadProcessor = aCmd->argInt(1);
   if (aCmd->isCmd("ReaderThreadPriority"))    mReaderThreadPriority = aCmd->argInt(1);

   if (aCmd->isCmd("WriteTestMode"))           mWriteTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("ReadTestMode"))            mReadTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("NumWrites"))               mNumWrites = aCmd->argInt(1);

   if (aCmd->isCmd("ReadSleepMeanMs"))         mReadSleepMeanMs = aCmd->argInt(1);
   if (aCmd->isCmd("ReadSleepRandomUs"))       mReadSleepRandomUs = aCmd->argInt(1);

   if (aCmd->isCmd("WriteSuspendRandom"))      mWriteSuspendRandom = aCmd->argInt(1);
   if (aCmd->isCmd("ReadSuspendRandom"))       mReadSuspendRandom = aCmd->argInt(1);
   if (aCmd->isCmd("SuspendSleepMeanMs"))      mSuspendSleepMeanMs = aCmd->argInt(1);
   if (aCmd->isCmd("SuspendSleepRandomMs"))    mSuspendSleepRandomMs = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void QueueParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
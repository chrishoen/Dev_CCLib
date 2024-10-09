//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMERINGPARMS_CPP_
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

   mMonitorThreadPeriod = 0;
   mStatPeriod = 0;
   mPollProcessor = false;

   mWriterThreadProcessor = -1;
   mWriterThreadPriority = 80;
   mWriterThreadMeanMs = 0;
   mWriterThreadRandomUs = 0;

   mReaderThreadProcessor = -1;
   mReaderThreadPriority = 80;
   mReaderThreadMeanMs = 0;
   mReaderThreadRandomUs = 0;

   mSelect = 0;
   mWriteTestMode = 0;
   mReadTestMode = 0;
   mNumWrites = 1;
   mSleepAfterNotReadyUs = 0;
   mSleepAfterOverwriteUs = 0;

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
   printf("ReaderThreadMeanMs           %-10d\n", mReaderThreadMeanMs);
   printf("ReaderThreadRandomUs         %-10d\n", mReaderThreadRandomUs);
   printf("\n");
   printf("Select                       %-10d\n", mSelect);
   printf("\n");
   printf("WriteTestMode                %-10d\n", mWriteTestMode);
   printf("ReadTestMode                 %-10d\n", mReadTestMode);
   printf("NumWrites                    %-10d\n", mNumWrites);
   printf("SleepAfterNotReadyUs         %-10d\n", mSleepAfterNotReadyUs);
   printf("mSleepAfterOverwriteUs       %-10d\n", mSleepAfterOverwriteUs);
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

   if (aCmd->isCmd("MonitorThreadPeriod"))     mMonitorThreadPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("StatPeriod"))              mStatPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("PollProcessor"))           mPollProcessor = aCmd->argBool(1);

   if (aCmd->isCmd("WriterThreadProcessor"))   mWriterThreadProcessor = aCmd->argInt(1);
   if (aCmd->isCmd("WriterThreadPriority"))    mWriterThreadPriority = aCmd->argInt(1);
   if (aCmd->isCmd("WriterThreadMeanMs"))      mWriterThreadMeanMs = aCmd->argInt(1);
   if (aCmd->isCmd("WriterThreadRandomUs"))    mWriterThreadRandomUs = aCmd->argInt(1);

   if (aCmd->isCmd("ReaderThreadProcessor"))   mReaderThreadProcessor = aCmd->argInt(1);
   if (aCmd->isCmd("ReaderThreadPriority"))    mReaderThreadPriority = aCmd->argInt(1);
   if (aCmd->isCmd("ReaderThreadMeanMs"))      mReaderThreadMeanMs = aCmd->argInt(1);
   if (aCmd->isCmd("ReaderThreadRandomUs"))    mReaderThreadRandomUs = aCmd->argInt(1);

   if (aCmd->isCmd("Select"))                  mSelect = aCmd->argInt(1);

   if (aCmd->isCmd("WriteTestMode"))           mWriteTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("ReadTestMode"))            mReadTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("NumWrites"))               mNumWrites = aCmd->argInt(1);
   if (aCmd->isCmd("SleepAfterNotReadyUs"))    mSleepAfterNotReadyUs = aCmd->argInt(1);
   if (aCmd->isCmd("SleepAfterOverwriteUs"))   mSleepAfterOverwriteUs = aCmd->argInt(1);

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
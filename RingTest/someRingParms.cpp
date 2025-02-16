//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"
#include "cmnPaths.h"

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
   resetVars();
}

void RingParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath(Cmn::get_files_filepath("Ring_Parms.txt"));
   resetVars();
}

void RingParms::resetVars()
{
   mScope = 1;

   mWriteTestMode = 0;
   mReadTestMode = 0;
   mNumWrites = 1;

   mWriteSleepMeanMs = 0;
   mWriteSleepRandomUs = 0;
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

void RingParms::show()
{
   printf("\n");
   printf("RingParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("Scope                        %-10d\n", mScope);

   printf("\n");
   printf("WriteTestMode                %-10d\n", mWriteTestMode);
   printf("ReadTestMode                 %-10d\n", mReadTestMode);
   printf("NumWrites                    %-10d\n", mNumWrites);
   printf("\n");
   printf("WriteSleepMeanMs             %-10d\n", mWriteSleepMeanMs);
   printf("WriteSleepRandomUs           %-10d\n", mWriteSleepRandomUs);
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

void RingParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("Scope"))                   mScope = aCmd->argInt(1);

   if (aCmd->isCmd("WriteTestMode"))           mWriteTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("ReadTestMode"))            mReadTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("NumWrites"))               mNumWrites = aCmd->argInt(1);

   if (aCmd->isCmd("WriteSleepMeanMs"))        mWriteSleepMeanMs = aCmd->argInt(1);
   if (aCmd->isCmd("WriteSleepRandomUs"))      mWriteSleepRandomUs = aCmd->argInt(1);
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

void RingParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnDefs.h"
#include "risCmdLineFile.h"

#define  _SOMEMEMORYPARMS_CPP_
#include "someMemoryParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

MemoryParms::MemoryParms()
{
   reset();
}

void MemoryParms::reset()
{
   BaseClass::reset();
   if (Ris::portableIsWindows())
   {
      BaseClass::setFilePath("c:/aaa_prime/files/Memory_Parms.txt");
   }
   else
   {
      BaseClass::setFilePath("/opt/prime/files/Memory_Parms.txt");
   }

   mTimerPeriod = 0;
   mAddress1 = 0;
   mNumPages1 = 1;

   mDevPath[0] = 0;
   mTestCode1 = 0;
   mTestCode2 = 0;

   mPollProcessor = false;
   mStatPeriod = 0;
   mPeriodUs = 0;

   mHighProcess = false;
   mPrintViewEnable = false;
   mPrintViewIPAddress[0] = 0;
   mTraceLogEnable = false;
   mTraceLogVerbose = false;

   mMuRole = Cmn::cMuRole_Cpu;
   mMuTestMode = Cmn::cMuTestMode_Downlink;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void MemoryParms::show()
{
   printf("\n");
   printf("MemoryParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("Address1                   %-12x\n", mAddress1);
   printf("NumPages1                  %-12d\n", mNumPages1);
   printf("Offset1                    %-12x\n", mOffset1);

   printf("\n");
   printf("DevPath                    %-12s\n", mDevPath);
   printf("TestCode1                  %-12d\n", mTestCode1);
   printf("TestCode2                  %-12d\n", mTestCode2);

   printf("\n");
   printf("PollProcessor              %-12s\n", my_string_from_bool(mPollProcessor));
   printf("StatPeriod                 %-12d\n", mStatPeriod);
   printf("PeriodUs                   %-12d\n", mPeriodUs);

   printf("\n");
   printf("TimerPeriod                %-12d\n", mTimerPeriod);
   printf("HighProcess                %-12s\n", my_string_from_bool(mHighProcess));

   printf("\n");
   printf("TraceLogEnable             %-12s\n", my_string_from_bool(mTraceLogEnable));
   printf("TraceLogVerbose            %-12s\n", my_string_from_bool(mTraceLogVerbose));

   printf("\n");
   printf("PrintViewEnable            %-12s\n", my_string_from_bool(mPrintViewEnable));
   printf("PrintViewIPAddress         %-12s\n", mPrintViewIPAddress);

   printf("\n");
   printf("MuRole                     %-12s\n", Cmn::asStringMuRole(mMuRole));
   printf("MuTestMode                 %-12s\n", Cmn::asStringMuTestMode(mMuTestMode));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void MemoryParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("Address1"))              mAddress1 = aCmd->argUnsigned(1);
   if (aCmd->isCmd("NumPages1"))             mNumPages1 = aCmd->argInt(1);
   if (aCmd->isCmd("Offset1"))               mOffset1 = aCmd->argInt(1);

   if (aCmd->isCmd("DevPath"))               aCmd->copyArgString(1, mDevPath, cMaxStringSize);
   if (aCmd->isCmd("TestCode1"))             mTestCode1 = aCmd->argInt(1);
   if (aCmd->isCmd("TestCode2"))             mTestCode2 = aCmd->argInt(1);

   if (aCmd->isCmd("PollProcessor"))         mPollProcessor = aCmd->argBool(1);
   if (aCmd->isCmd("StatPeriod"))            mStatPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("PeriodUs"))              mPeriodUs = aCmd->argInt(1);

   if (aCmd->isCmd("TimerPeriod"))           mTimerPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("HighProcess"))           mHighProcess = aCmd->argBool(1);
   if (aCmd->isCmd("PrintViewEnable"))       mPrintViewEnable = aCmd->argBool(1);
   if (aCmd->isCmd("PrintViewIPAddress"))    aCmd->copyArgString(1, mPrintViewIPAddress, cMaxStringSize);
   if (aCmd->isCmd("TraceLogEnable"))        mTraceLogEnable = aCmd->argBool(1);
   if (aCmd->isCmd("TraceLogVerbose"))       mTraceLogVerbose = aCmd->argBool(1);

   if (aCmd->isCmd("MuRole")) mMuRole = Cmn::getFromString_MuRole(aCmd->argString(1));
   if (aCmd->isCmd("MuTestMode")) mMuTestMode = Cmn::getFromString_MuTestMode(aCmd->argString(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void MemoryParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
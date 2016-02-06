/*==============================================================================

==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "risCmdLineFile.h"
#include "risPortableCalls.h"

#define  _GSETTINGS_CPP_
#include "GSettings.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

GSettings::GSettings()
{
   mMode        =    1;
   mTest        =    1;
   mNumWriters  =    1;
   mAllocate    = 1000;
   mTerminate   = 0;

   mWriteLower  =  900;
   mWriteUpper  = 1100;
   mReadLower   =  900;
   mReadUpper   = 1100;
   mSleepLower  =  900;
   mSleepUpper  = 1100;

   mXLimit = 0.0;

   mBackQueue1=0.0;
   mBackQueue2=0.0;
   mBackList1=0.0;
   mBackList2=0.0;

   mDelay1=0;
   mDelay2=0;
   mDelayWrite=0;
   mDelayRead=0;
}

//******************************************************************************

void GSettings::show()
{
   printf("GSettings   Mode          %11d\n",    mMode);
   printf("GSettings   Test          %11d\n",    mTest);
   printf("GSettings   NumWriters    %11d\n",    mNumWriters);
   printf("GSettings   Allocate      %11d\n",    mAllocate);
   printf("GSettings   Terminate     %11d\n",    mTerminate);
   printf("GSettings   WriteLower    %11d\n",    mWriteLower);
   printf("GSettings   WriteUpper    %11d\n",    mWriteUpper);
   printf("GSettings   ReadLower     %11d\n",    mReadLower);
   printf("GSettings   ReadUpper     %11d\n",    mReadUpper);
   printf("GSettings   SleepLower    %11d\n",    mSleepLower);
   printf("GSettings   SleepUpper    %11d\n",    mSleepUpper);
   printf("GSettings   XLimit        %11.1f\n",  mXLimit);
   printf("GSettings   BackQueue1    %11.1f\n",  mBackQueue1);
   printf("GSettings   BackQueue2    %11.1f\n",  mBackQueue2);
   printf("GSettings   BackList1     %11.1f\n",  mBackList1);
   printf("GSettings   BackList2     %11.1f\n",  mBackList2);
   printf("GSettings   Delay1        %11d\n",    mDelay1);
   printf("GSettings   Delay2        %11d\n",    mDelay2);
   printf("GSettings   DelayWrite    %11d\n",    mDelayWrite);
   printf("GSettings   DelayRead     %11d\n",    mDelayRead);
}

//******************************************************************************
// Base class overload, called for each line in the file

void GSettings::execute(Ris::CmdLineCmd* aCmd)
{
   // Read variables
   if(aCmd->isCmd("Mode"))         mMode        = aCmd->argInt (1);
   if(aCmd->isCmd("Test"))         mTest        = aCmd->argInt (1);
   if(aCmd->isCmd("NumWriters"))   mNumWriters  = aCmd->argInt (1);
   if(aCmd->isCmd("Allocate"))     mAllocate    = aCmd->argInt (1);
   if(aCmd->isCmd("Terminate"))    mTerminate   = aCmd->argInt (1);
   if(aCmd->isCmd("Allocate"))     mAllocate    = aCmd->argInt (1);
   if(aCmd->isCmd("WriteLower"))   mWriteLower  = aCmd->argInt (1);
   if(aCmd->isCmd("WriteUpper"))   mWriteUpper  = aCmd->argInt (1);
   if(aCmd->isCmd("ReadLower"))    mReadLower   = aCmd->argInt (1);
   if(aCmd->isCmd("ReadUpper"))    mReadUpper   = aCmd->argInt (1);
   if(aCmd->isCmd("SleepLower"))   mSleepLower  = aCmd->argInt (1);
   if(aCmd->isCmd("SleepUpper"))   mSleepUpper  = aCmd->argInt (1);
   if(aCmd->isCmd("XLimit"))       mXLimit      = aCmd->argDouble (1);
   if(aCmd->isCmd("BackQueue1"))   mBackQueue1  = aCmd->argDouble (1);
   if(aCmd->isCmd("BackQueue2"))   mBackQueue2  = aCmd->argDouble (1);
   if(aCmd->isCmd("BackList1"))    mBackList1   = aCmd->argDouble (1);
   if(aCmd->isCmd("BackList2"))    mBackList2   = aCmd->argDouble (1);
   if(aCmd->isCmd("Delay1"))       mDelay1      = aCmd->argInt (1);
   if(aCmd->isCmd("Delay2"))       mDelay2      = aCmd->argInt (1);
   if(aCmd->isCmd("DelayWrite"))   mDelayWrite  = aCmd->argInt (1);
   if(aCmd->isCmd("DelayRead"))    mDelayRead   = aCmd->argInt (1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void GSettings::readFromFileName(char* aFileName)
{
   char tFilePath[200];

   strcpy(tFilePath, Ris::portableGetSettingsDir());

   if (aFileName != 0)
   {
      strcat(tFilePath, aFileName);
   }
   else
   {
      strcat(tFilePath, "ConcurrentSettings.txt");
   }

   readFromFilePath(tFilePath);
}

//******************************************************************************

void GSettings::readFromFilePath(char* aFilePath)
{ 
   Ris::CmdLineFile tCmdLineFile;

   // Open command line file
   if (!tCmdLineFile.open(aFilePath))
   {
	   printf("GSettings::readFromFilePath FAIL %s\n",aFilePath);
      return;
   }

   // Read command line file, execute commands for each line in the file,
   // using this command line executive
   tCmdLineFile.execute(this);

   // Close command line file
   tCmdLineFile.close();

   printf("GSettings::readFromFilePath PASS %s\n", aFilePath);
}


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
   mMultiplier  = 1000;
   mAllocate    = 1000;
   mWriteLower  =  900;
   mWriteUpper  = 1100;
   mReadLower   =  900;
   mReadUpper   = 1100;
   mSleepLower  =  900;
   mSleepUpper  = 1100;
   mXLimit = 0.0;
   mBackoff1=0;
   mBackoff2=0;
}

//******************************************************************************

void GSettings::show()
{
   printf("GSettings   Mode          %9d\n",  mMode);
   printf("GSettings   Test          %9d\n",  mTest);
   printf("GSettings   NumWriters    %9d\n",  mNumWriters);
   printf("GSettings   Multiplier    %9d\n",  mMultiplier);
   printf("GSettings   Allocate      %9d\n",  mAllocate);
   printf("GSettings   WriteLower    %9d\n",  mWriteLower);
   printf("GSettings   WriteUpper    %9d\n",  mWriteUpper);
   printf("GSettings   ReadLower     %9d\n",  mReadLower);
   printf("GSettings   ReadUpper     %9d\n",  mReadUpper);
   printf("GSettings   SleepLower    %9d\n",  mSleepLower);
   printf("GSettings   SleepUpper    %9d\n",  mSleepUpper);
   printf("GSettings   Backoff1      %9d\n",  mBackoff1);
   printf("GSettings   Backoff2      %9d\n",  mBackoff2);
}

//******************************************************************************
// Base class overload, called for each line in the file

void GSettings::execute(Ris::CmdLineCmd* aCmd)
{
   // Read variables
   if(aCmd->isCmd("Mode"))         mMode        = aCmd->argInt (1);
   if(aCmd->isCmd("Test"))         mTest        = aCmd->argInt (1);
   if(aCmd->isCmd("NumWriters"))   mNumWriters  = aCmd->argInt (1);
   if(aCmd->isCmd("Multiplier"))   mMultiplier  = aCmd->argInt (1);
   if(aCmd->isCmd("Allocate"))     mAllocate    = aCmd->argInt (1)*mMultiplier;
   if(aCmd->isCmd("WriteLower"))   mWriteLower  = aCmd->argInt (1)*mMultiplier;
   if(aCmd->isCmd("WriteUpper"))   mWriteUpper  = aCmd->argInt (1)*mMultiplier;
   if(aCmd->isCmd("ReadLower"))    mReadLower   = aCmd->argInt (1)*mMultiplier;
   if(aCmd->isCmd("ReadUpper"))    mReadUpper   = aCmd->argInt (1)*mMultiplier;
   if(aCmd->isCmd("SleepLower"))   mSleepLower  = aCmd->argInt (1);
   if(aCmd->isCmd("SleepUpper"))   mSleepUpper  = aCmd->argInt (1);
   if(aCmd->isCmd("XLimit"))       mXLimit      = aCmd->argDouble (1);
   if(aCmd->isCmd("Backoff1"))     mBackoff1    = aCmd->argInt (1);
   if(aCmd->isCmd("Backoff2"))     mBackoff2    = aCmd->argInt (1);
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


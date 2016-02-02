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
   mTerminate   = 0;
   mSleepLower  =  900;
   mSleepUpper  = 1100;
   mThreadMode  =    1;
   mXLimit = 0.0;
   mBackoff1=0;
   mBackoff2=0;
}

//******************************************************************************

void GSettings::show()
{
   printf("GSettings   Mode          %11d\n",   mMode);
   printf("GSettings   Test          %11d\n",   mTest);
   printf("GSettings   NumWriters    %11d\n",   mNumWriters);
   printf("GSettings   Multiplier    %11d\n",   mMultiplier);
   printf("GSettings   Allocate      %11d\n",   mAllocate);
   printf("GSettings   WriteLower    %11d\n",   mWriteLower);
   printf("GSettings   WriteUpper    %11d\n",   mWriteUpper);
   printf("GSettings   ReadLower     %11d\n",   mReadLower);
   printf("GSettings   ReadUpper     %11d\n",   mReadUpper);
   printf("GSettings   Terminate     %11d\n",   mTerminate);
   printf("GSettings   SleepLower    %11d\n",   mSleepLower);
   printf("GSettings   SleepUpper    %11d\n",   mSleepUpper);
   printf("GSettings   ThreadMode    %11d\n",   mThreadMode);
   printf("GSettings   XLimit        %11.1f\n", mXLimit);
   printf("GSettings   Backoff1      %11d\n",    mBackoff1);
   printf("GSettings   Backoff2      %11d\n",    mBackoff2);
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
   if(aCmd->isCmd("Terminate"))    mTerminate   = aCmd->argInt (1)*mMultiplier;
   if(aCmd->isCmd("SleepLower"))   mSleepLower  = aCmd->argInt (1);
   if(aCmd->isCmd("SleepUpper"))   mSleepUpper  = aCmd->argInt (1);
   if(aCmd->isCmd("ThreadMode"))   mThreadMode  = aCmd->argInt (1);
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


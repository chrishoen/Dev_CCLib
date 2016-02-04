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
   mXLimit = 0.0;
   mBackoff1=0;
   mBackoff2=0;
   mDelay1=0;
   mDelay2=0;
   mDelayWrite=0;
   mDelayRead=0;
}

//******************************************************************************

void GSettings::show()
{
   printf("GSettings   Mode          %11d\n",   mMode);
   printf("GSettings   Test          %11d\n",   mTest);
   printf("GSettings   NumWriters    %11d\n",   mNumWriters);
   printf("GSettings   Allocate      %11d\n",   mAllocate);
   printf("GSettings   Terminate     %11d\n",   mTerminate);
   printf("GSettings   XLimit        %11.1f\n", mXLimit);
   printf("GSettings   Backoff1      %11d\n",    mBackoff1);
   printf("GSettings   Backoff2      %11d\n",    mBackoff2);
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
   if(aCmd->isCmd("XLimit"))       mXLimit      = aCmd->argDouble (1);
   if(aCmd->isCmd("Backoff1"))     mBackoff1    = aCmd->argInt (1);
   if(aCmd->isCmd("Backoff2"))     mBackoff2    = aCmd->argInt (1);
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


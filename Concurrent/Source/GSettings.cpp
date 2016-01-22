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
   mTestThread = 1;
   mTestNumber = 1;
}

//******************************************************************************

void GSettings::show()
{
   printf("GSettings   TestThread   %d\n",mTestThread);
   printf("GSettings   TimerThread  %d\n",mTimerThread);
   printf("GSettings   TestNumber   %d\n",mTestNumber);
}

//******************************************************************************
// Base class overload, called for each line in the file

void GSettings::execute(Ris::CmdLineCmd* aCmd)
{
   // Read variables
   if(aCmd->isCmd("TESTTHREAD"))   mTestThread  = aCmd->argInt (1);
   if(aCmd->isCmd("TIMERTHREAD"))  mTimerThread = aCmd->argInt (1);
   if(aCmd->isCmd("TESTNUMBER"))   mTestNumber  = aCmd->argInt (1);
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
      strcat(tFilePath, "ThreadTestSettings.txt");
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


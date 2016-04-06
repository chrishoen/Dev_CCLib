//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>

#include "my_functions.h"
#include "risCmdLineFile.h"
#include "risPortableCalls.h"

#define  _GSETTINGS_CPP_
#include "GSettings.h"


//******************************************************************************

GSettings::GSettings()
{
   mSection[0]=0;

   mMyAppNumber = 0;
   mMyAppRole = 0;

}

void GSettings::show()
{
   printf("GSettings ******* %s\n", mSection);

   printf("MyAppRole                 %d\n", mMyAppRole);
   printf("MyAppNumber               %d\n", mMyAppNumber);
   printf("NumBytes                  %d\n", mNumBytes);

   printf("GSettings ******* %s\n", mSection);
}

//******************************************************************************
// For a given command line "Begin Section", this returns true
// if "Section", the first command line argument, is the same as the section 
// specified in initialize.

bool GSettings::isMySection(Ris::CmdLineCmd* aCmd)
{
   bool tFlag=false;

   if (aCmd->numArg()==1)
   {
      if (aCmd->isArgString(1,mSection))
      {
         tFlag=true;
      }
   }

   return tFlag;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is called for each command line in the settings file.
// It processes commands, with arguments
// BEGIN starts a section, END exits a section
// Only commands for a section are processed

void GSettings::execute(Ris::CmdLineCmd* aCmd)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Section commands


	if(aCmd->isCmd("SectionBegin"      ))  mSectionFlag=isMySection(aCmd);
   if(aCmd->isCmd("SectionEnd"        ))  mSectionFlag=false;

   if (!mSectionFlag) return;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Only process commands for the section specified in initialize.

   if(aCmd->isCmd("MyAppNumber"     ))   mMyAppNumber = aCmd->argInt(1);
   if(aCmd->isCmd("NumBytes"        ))   mNumBytes = aCmd->argInt(1);
}



//******************************************************************************
//******************************************************************************
//******************************************************************************
// Specific execute 

//******************************************************************************
//******************************************************************************
//******************************************************************************

bool GSettings::initialize(char* aSection)
{ 
   // File path
   char tFilePath[200];

   strcpy(tFilePath, "C:\\MyLib\\Settings\\SharedMemorySettings.txt");

   // Copy arguments
   strcpy(mSection,aSection);

   // Get AppRole
   mMyAppRole = 0;
   if (strcmp(mSection, "MemServer") == 0)
   {
      mMyAppRole = cMemServer;
   }
   if (strcmp(mSection, "MemClient") == 0)
   {
      mMyAppRole = cMemServer;
   }

   // Apply settings file to this executive   
   Ris::CmdLineFile tCmdLineFile;

   if (tCmdLineFile.open(tFilePath))
   {
      tCmdLineFile.execute(this);
      tCmdLineFile.close();
      return true;
   }
   else
   {
      printf("GSettings::file open failed\n");
      return false;
   }
}





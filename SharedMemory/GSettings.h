#ifndef _GSETTINGS_H_
#define _GSETTINGS_H_
/*==============================================================================

This file contains settings. 

==============================================================================*/

//**********************************************************************
//**********************************************************************
//**********************************************************************

#include "risCmdLineFile.h"

//**********************************************************************
//**********************************************************************
//**********************************************************************
// GSettings class, inherits from BaseCmdLineExec to process
// command lines from a command line file.
// Each application reads its own print settings from a common settings
// file. 

class GSettings : public Ris::BaseCmdLineExec
{
public:

   //---------------------------------------------------------------------------
   // GSettings members.

   static const int cMaxStringSize = 30;

   int  mMyAppNumber;
   int  mNumBytes;

   //---------------------------------------------------------------------------
   // Infrastucture. Constructor and such

   typedef Ris::BaseCmdLineExec BaseClass;
   GSettings();
   void show();

   // Baseclass override, executes for each line in the settings
   // command line file

   void execute(Ris::CmdLineCmd* aCmd);

   // Initialize.
   // aGSettingsFileName is the settings filename. aSection is the settings
   // file section that each application extracts its settings from. 
   // aSectionMode specifies the section mode. Each section begins with a 
   // command line, such as "Begin CmdFile Default", where "Begin" is the 
   // command ,"CmdFile" is  first argument and denotes the section and
   // "Default" is the second argument and denotes the section mode.

   bool initialize(char* aSection);

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Section

   char mSection[200];
   char mSectionMode[200];

   bool isMySection(Ris::CmdLineCmd* aCmd);
   bool mSectionFlag;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _GSETTINGS_CPP_
        GSettings gGSettings;
#else
        extern GSettings gGSettings;
#endif


#endif


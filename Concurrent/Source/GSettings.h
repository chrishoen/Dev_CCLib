#ifndef _GSETTINGS_H_
#define _GSETTINGS_H_

/*==============================================================================

Global application settings

==============================================================================*/
#include "risCmdLineFile.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************


class GSettings : public Ris::BaseCmdLineExec
{
public:
   //---------------------------------------------------------------------------
   // Settings

   int   mAllocate;

   int   mSleepLower;
   int   mSleepUpper;

   int   mNumWriters;

   int   mWriteLower;
   int   mWriteUpper;

   int   mReadLower;
   int   mReadUpper;

   // Settings
   //---------------------------------------------------------------------------

   //---------------------------------------------------------------------------
   // Constructor

   typedef Ris::BaseCmdLineExec BaseClass;
   GSettings();
   void show();

   //---------------------------------------------------------------------------
   // Read from settings file

   void readFromFileName(char* aFileName=0);
   void readFromFilePath(char* aFilePath=0);

   //---------------------------------------------------------------------------
   // Execute

   void execute(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _GSETTINGS_CPP_
        GSettings       gGSettings;
#else
extern  GSettings       gGSettings;
#endif

//******************************************************************************

#endif


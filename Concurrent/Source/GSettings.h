#ifndef _GSETTINGS_H_
#define _GSETTINGS_H_

/*==============================================================================

Global application settings

==============================================================================*/
#include "risCmdLineFile.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************st


class GSettings : public Ris::BaseCmdLineExec
{
public:
   //---------------------------------------------------------------------------
   // Settings

   int     mMode;
   int     mTest;
   int     mNumWriters;

   int     mAllocate;
   int     mTerminate;

   double  mXLimit;
   int     mBackoff1;
   int     mBackoff2;

   int     mDelay1;
   int     mDelay2;
   int     mDelayWrite;
   int     mDelayRead;


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


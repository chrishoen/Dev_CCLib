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

   static const int   cTestThread_None           = 0;
   static const int   cTimerThread_None          = 0;

   static const int   cTestThread_Thread1        = 1;
   static const int   cTestThread_ApcThread      = 2;
   static const int   cTestThread_QCallThread1   = 3;

   static const int   cTimerThread_Thread1        = 1;
   static const int   cTimerThread_Thread2        = 2;
   static const int   cTimerThread_Thread3        = 3;
   static const int   cTimerThread_ApcThread      = 4;

   int   mTestNumber;
   int   mTestThread;
   int   mTimerThread;

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


//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"
#include "cmnPaths.h"

#define  _SMSHAREPARMS_CPP_
#include "smShareParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ShareParms::ShareParms()
{
   resetVars();
}

void ShareParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath(Cmn::get_files_filepath("Share_Parms.txt"));
   resetVars();
}

void ShareParms::resetVars()
{
   mScope = 1;
   mAddress1 = 0;
   mNumPages1 = 1;
   mOffset1 = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ShareParms::show()
{
   printf("\n");
   printf("ShareParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("Scope                      %-12d\n", mScope);
   printf("Address1                   %-12x\n", mAddress1);
   printf("NumPages1                  %-12d\n", mNumPages1);
   printf("Offset1                    %-12x\n", mOffset1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ShareParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("Scope"))                 mScope = aCmd->argUnsigned(1);
   if (aCmd->isCmd("Address1"))              mAddress1 = aCmd->argUnsigned(1);
   if (aCmd->isCmd("NumPages1"))             mNumPages1 = aCmd->argInt(1);
   if (aCmd->isCmd("Offset1"))               mOffset1 = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void ShareParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
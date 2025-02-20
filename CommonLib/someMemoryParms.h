#pragma once

/*==============================================================================
Parameters class whose values are read from a command file. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that contains parameter member variables. The values of
// the parameters are set by reading a text file that contains command lines.
// Each command line is of the form "command argument1 argument2 ...".
// 
// The command files are partitioned into different sections and only one
// section can be read at a time to set member variables that are specified
// in it.
//
// The command files are managed by a CmdLineFile object. This opens the 
// file, reads each line in it, parses the line into a CmdLineCmd command 
// object, passes the command object to this object for command execution,
// and then closes the file. 
//
// This class inherits from BaseCmdLineParms, which inherits from 
// BaseCmdLineExec. BaseCmdLineParms provides a method that uses a
// CmdLineFile object to read and process the file. BaseCmdLineExec provides
// an abstract execute(cmd) method to which inheritors provide an overload
// that is called by the CmdLineFile object for each command in the file.
// This execute method then sets a member variables, according to the
// command.
// 
// This class can contain member variables that also inherit from
// BaseCmdLineExec. This provides for command files that have a nested
// structure. If so, then this class is the root.
// 

class MemoryParms : public Ris::BaseCmdLineParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 100;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Main thread timer period.
   int mTimerPeriod;

   // Addresses.
   unsigned mAddress1;
   int mNumPages1;
   unsigned mOffset1;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. KMod.

   // Device path.
   char mDevPath[cMaxStringSize];

   // Test codes.
   int mTestCode1;
   int mTestCode2;

   // Periodic variables.
   bool mPollProcessor;
   int  mStatPeriod;
   int  mPeriodUs;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true then use high process priority.
   bool mHighProcess;

   // If true then enable print view and initialize it with the
   // given ip address. Print view routes debug prints from the
   // backend threads to print view consoles on a host.
   bool mPrintViewEnable;
   char mPrintViewIPAddress[30];

   // Trace variables.
   bool mTraceLogEnable;
   bool mTraceLogVerbose;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Mu test parameters.
   int mMuRole;
   int mMuTestMode;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   typedef Ris::BaseCmdLineParms BaseClass;
   MemoryParms();
   void reset() override;
   void show();

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Calculate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand() override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SOMEMEMORYPARMS_CPP_
   MemoryParms gMemoryParms;
#else
   extern MemoryParms gMemoryParms;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
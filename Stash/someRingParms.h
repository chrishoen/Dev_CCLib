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

class RingParms : public Ris::BaseCmdLineParms
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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. git test

   // Scope 1,2. cpu,rpu
   int mScope;

   // Monitor variables.
   int mMonitorThreadPeriod;
   int mStatPeriod;
   bool mPollProcessor;

   // Thread variables.
   int mWriterThreadProcessor;
   int mWriterThreadPriority;
   int mWriterThreadMeanMs;
   int mWriterThreadRandomUs;

   // Thread variables.
   int mReaderThreadProcessor;
   int mReaderThreadPriority;

   // Test mode.
   int mWriteTestMode;
   int mReadTestMode;
   int mNumWrites;

   // Read sleep times.
   int mReadSleepMeanMs;
   int mReadSleepRandomUs;

   // Suspend test variables.
   int mWriteSuspendRandom;
   int mReadSuspendRandom;
   int mSuspendSleepMeanMs;
   int mSuspendSleepRandomMs;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastucture.

   // Constructor,
   typedef Ris::BaseCmdLineParms BaseClass;
   RingParms();
   void reset();
   void resetVars();
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

#ifdef _SOMERINGPARMS_CPP_
   RingParms gRingParms;
#else
   extern RingParms gRingParms;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
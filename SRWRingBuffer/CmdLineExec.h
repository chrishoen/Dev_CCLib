#pragma once

/*==============================================================================
Program command line executive.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"
#include "ccSRWObjectRingBuffer.h"
#include "ccSRWValueRingBuffer.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   CC::SRWObjectRingBuffer<int, 4> mObjectRing;
   CC::SRWValueRingBuffer<int, 4> mValueRing;

   int mWriteArray[1000];
   int mReadArray[1000];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastructure.

   CmdLineExec();
   void reset() override;
   void init();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Base class override. Execute a command line command. It calls one of
   // the following specific command execution functions. This is called by
   // the owner of this object to pass command line commands to it. 
   void execute(Ris::CmdLineCmd* aCmd) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Execute specific commands.
   void executePutObject(Ris::CmdLineCmd* aCmd);
   void executeGetObject(Ris::CmdLineCmd* aCmd);
   void executeAtObject(Ris::CmdLineCmd* aCmd);
   void executeMarkObject(Ris::CmdLineCmd* aCmd);
   void executeShowObject(Ris::CmdLineCmd* aCmd);

   void executePutValue(Ris::CmdLineCmd* aCmd);
   void executeGetValue(Ris::CmdLineCmd* aCmd);
   void executeAtValue(Ris::CmdLineCmd* aCmd);
   void executeMarkValue(Ris::CmdLineCmd* aCmd);
   void executeShowValue(Ris::CmdLineCmd* aCmd);

   void executePutArray(Ris::CmdLineCmd* aCmd);
   void executeGetArray(Ris::CmdLineCmd* aCmd);
   void executeShowArray(Ris::CmdLineCmd* aCmd);

   void executeGo1(Ris::CmdLineCmd* aCmd);
   void executeGo2(Ris::CmdLineCmd* aCmd);
   void executeGo3(Ris::CmdLineCmd* aCmd);
   void executeGo4(Ris::CmdLineCmd* aCmd);
   void executeGo5(Ris::CmdLineCmd* aCmd);
   void executeGo6(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************


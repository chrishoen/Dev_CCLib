#pragma once

/*==============================================================================
Program command line executive.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"
#include "ccSRSWValueQueue.h"
#include "ccSRSWObjectQueue.h"
#include "someClass1.h"

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

   CC::SRSWValueQueue<int, 5> mIntQueue;
   CC::SRSWObjectQueue<Some::Class1, 5> mObjectQueue;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastructure.

   CmdLineExec();
   void reset() override;

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
   void executeVWrite(Ris::CmdLineCmd* aCmd);
   void executeVRead(Ris::CmdLineCmd* aCmd);
   void executeVShow(Ris::CmdLineCmd* aCmd);

   void executeOWrite(Ris::CmdLineCmd* aCmd);
   void executeORead(Ris::CmdLineCmd* aCmd);
   void executeOShow(Ris::CmdLineCmd* aCmd);

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


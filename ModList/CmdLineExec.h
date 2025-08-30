#pragma once

#include "risCmdLineExec.h"
#include "ccModList.h"

//******************************************************************************
// specific command line executive
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

   CC::ModList<int,5> mList;
   CmdLineExec();

   void reset();
   void execute(Ris::CmdLineCmd* aCmd);

   void executeWriteTail(Ris::CmdLineCmd* aCmd);
   void executeReadHead(Ris::CmdLineCmd* aCmd);

   void executeGo1(Ris::CmdLineCmd* aCmd);
   void executeGo2(Ris::CmdLineCmd* aCmd);
   void executeGo3(Ris::CmdLineCmd* aCmd);
   void executeGo4(Ris::CmdLineCmd* aCmd);
   void executeGo5(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************


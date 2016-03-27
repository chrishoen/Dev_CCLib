#ifndef _CMDLINEEXEC_H_
#define _CMDLINEEXEC_H_

#include "risCmdLineExec.h"

//******************************************************************************
// specific command line executive
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

  CmdLineExec();

  void reset();
  void execute(Ris::CmdLineCmd* aCmd);

  void executeGo11 (Ris::CmdLineCmd* aCmd);
  void executeGo12 (Ris::CmdLineCmd* aCmd);
  void executeGo20 (Ris::CmdLineCmd* aCmd);
  void executeGo21 (Ris::CmdLineCmd* aCmd);
  void executeGo22 (Ris::CmdLineCmd* aCmd);
  void executeGo31 (Ris::CmdLineCmd* aCmd);
  void executeGo32 (Ris::CmdLineCmd* aCmd);
  void executeGo41 (Ris::CmdLineCmd* aCmd);
  void executeGo42 (Ris::CmdLineCmd* aCmd);
  void executeGo43 (Ris::CmdLineCmd* aCmd);
  void executeGo44 (Ris::CmdLineCmd* aCmd);
  void executeGo5  (Ris::CmdLineCmd* aCmd);
  void executeGo6  (Ris::CmdLineCmd* aCmd);
  void executeGo7  (Ris::CmdLineCmd* aCmd);
  void executeGo8  (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
#endif


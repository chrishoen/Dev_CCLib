#ifndef _CMDLINEEXEC_H_
#define _CMDLINEEXEC_H_

#include <windows.h>
#include "risCmdLineExec.h"
#include "ccTokenStack.h"

//******************************************************************************
// specific command line executive
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

  CmdLineExec();

  void reset();
  void execute(Ris::CmdLineCmd* aCmd);

  void executeGo1(Ris::CmdLineCmd* aCmd);
  void executeGo2(Ris::CmdLineCmd* aCmd);
  void executeGo3(Ris::CmdLineCmd* aCmd);

  void executePush (Ris::CmdLineCmd* aCmd);
  void executePop  (Ris::CmdLineCmd* aCmd);

  LONG mCount;

  CC::TokenStack mStack;
};

//******************************************************************************
#endif


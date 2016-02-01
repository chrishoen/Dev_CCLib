#ifndef _CMDLINEEXEC_H_
#define _CMDLINEEXEC_H_

#include "risCmdLineExec.h"

//******************************************************************************
// specific command line sequencer
//******************************************************************************
class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

  CmdLineExec();

  void reset();
  void execute(Ris::CmdLineCmd* aCmd);

  void executeGo1    (Ris::CmdLineCmd* aCmd);
  void executeGo2    (Ris::CmdLineCmd* aCmd);
  void executeGo3    (Ris::CmdLineCmd* aCmd);
  void executeGo4    (Ris::CmdLineCmd* aCmd);

  void executeWrite  (Ris::CmdLineCmd* aCmd);
  void executeRead   (Ris::CmdLineCmd* aCmd);

  void executeStart  (Ris::CmdLineCmd* aCmd);
  void executeStop   (Ris::CmdLineCmd* aCmd);
  void executeShow   (Ris::CmdLineCmd* aCmd);

  void executeTime1  (Ris::CmdLineCmd* aCmd);
  void executeTime2  (Ris::CmdLineCmd* aCmd);

};
//******************************************************************************
#endif


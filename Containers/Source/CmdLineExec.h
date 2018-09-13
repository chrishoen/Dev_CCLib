#ifndef _CMDLINEEXEC_H_
#define _CMDLINEEXEC_H_

#include "ccLFPointerQueue.h"
#include "ccLFValueQueue.h"
#include "ccLFObjectQueue.h"
#include "ccLMObjectQueue.h"
#include "ccSRSWValueQueue.h"
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

  void executeGo1(Ris::CmdLineCmd* aCmd);
  void executeGo2(Ris::CmdLineCmd* aCmd);
  void executeGo3(Ris::CmdLineCmd* aCmd);

  void executeWriteP (Ris::CmdLineCmd* aCmd);
  void executeReadP  (Ris::CmdLineCmd* aCmd);
  void executeWriteK (Ris::CmdLineCmd* aCmd);
  void executeReadK  (Ris::CmdLineCmd* aCmd);
  void executeWriteI (Ris::CmdLineCmd* aCmd);
  void executeReadI  (Ris::CmdLineCmd* aCmd);

  int mCount;
//CC::LFValueQueue<int>      mIntQueue;
  CC::SRSWValueQueue<int>     mIntQueue;
//CC::LFObjectQueue          mObjectQueue;
  CC::LMObjectQueue          mObjectQueue;
  CC::LFPointerQueue<void*>  mPointerQueue;
};

//******************************************************************************
#endif


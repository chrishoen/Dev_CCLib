#ifndef _CMDLINEEXEC_H_
#define _CMDLINEEXEC_H_

#include "risCmdLineExec.h"
#include "someMyBlockA.h"

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
   void executeGo4(Ris::CmdLineCmd* aCmd);

   void executeCreate   (Ris::CmdLineCmd* aCmd);
   void executeDestroy  (Ris::CmdLineCmd* aCmd);
   void executeShow     (Ris::CmdLineCmd* aCmd);

   Some::MyBlockA* mMyBlockA;
};

//******************************************************************************
#endif


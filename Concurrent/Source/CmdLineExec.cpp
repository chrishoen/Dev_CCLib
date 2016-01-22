
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "prnPrint.h"

#include "CmdLineExec.h"

#include "someMessage.h"
#include "someThread1.h"
#include "someShare.h"

using namespace Some;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
   for (int i=0;i<100;i++) printf("\n",i);
}
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("GO1"   ))  executeGo1   (aCmd);
   if(aCmd->isCmd("GO2"   ))  executeGo2   (aCmd);
   if(aCmd->isCmd("GO3"   ))  executeGo3   (aCmd);
   if(aCmd->isCmd("GO4"   ))  executeGo4   (aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   IntMessage tMsg1;
   tMsg1.mIdent  = 3;
   tMsg1.mSeqNum = 5;
   Prn::print(0, "sizeof %d", sizeof(IntMessage));
   Prn::print(0, "%08X", *tMsg1.ptr());

}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}


#include "stdafx.h"


#include "CmdLineExec.h"

#include "someQueueParms.h"
#include "someQueueReaderThread1.h"
#include "someQueueWriterThread.h"
#include "someMonitorThread.h"
using namespace Some;

//******************************************************************************
//******************************************************************************
//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("TP"))   Some::gQueueWriterThread->mTPFlag = aCmd->argBool(1);
   if (aCmd->isCmd("GO1"))  executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))  executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))  executeGo3(aCmd);
   if (aCmd->isCmd("Parms"))  executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::special(int aSpecial)
{
   gMonitorThread->mShowCode = aSpecial;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
void CmdLineExec::executeGo1 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   Some::gQueueParms.reset();
   Some::gQueueParms.readSection("default");
   Some::gQueueParms.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************




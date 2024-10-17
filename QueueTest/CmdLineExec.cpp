#include "stdafx.h"


#include "CmdLineExec.h"

#include "someQueueParms.h"
#include "someQueueReaderThread.h"
#include "someQueueWriterThread.h"
#include "someQueueMonitorThread1.h"
#include "someQueueMonitorThread2.h"
#include "smShare.h"
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
   if (aCmd->isCmd("TP"))     Some::gQueueWriterThread->mTPFlag = aCmd->argBool(1);
   if (aCmd->isCmd("T"))      Some::gQueueWriterThread->mTPFlag = true;
   if (aCmd->isCmd("D"))      Some::gQueueWriterThread->mTPFlag = false;

   if (aCmd->isCmd("RD"))     executeRead(aCmd);
   if (aCmd->isCmd("WR"))     executeWrite(aCmd);
   if (aCmd->isCmd("GO1"))    executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))    executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))    executeGo3(aCmd);
   if (aCmd->isCmd("Parms"))  executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "gCpuShare->mN1              %d", SM::gShare->mCpuSync1);
   Prn::print(0, "gCpuShare->mN1              %d", SM::gShare->mCpuSync2);
   Prn::print(0, "gRpuShare->mN1              %d", SM::gShare->mRpuSync1);
   Prn::print(0, "gRpuShare->mN1              %d", SM::gShare->mRpuSync2);
   Prn::print(0, "");
   Prn::print(0, "Some::gQueueParms.mScope    %d", Some::gQueueParms.mScope);
   Prn::print(0, "gRpuShare->mSX.mQueueSelect %d", SM::gShare->mSX.mQueueSelect);
}

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 100);
   SM::gShare->mCpuSync1 = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::special(int aSpecial)
{
   if (gQueueMonitorThread1) gQueueMonitorThread1->mShowCode = aSpecial;
   if (gQueueMonitorThread2) gQueueMonitorThread2->mShowCode = aSpecial;
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




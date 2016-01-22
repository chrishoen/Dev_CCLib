
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
   aCmd->setArgDefault(1,100);
   aCmd->setArgDefault(2,100);

   gShare.mWriter.write (aCmd->argInt(1));
   gShare.mReader.read  (aCmd->argInt(2));

   gShare.mWriter.show();
   gShare.mReader.show();

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


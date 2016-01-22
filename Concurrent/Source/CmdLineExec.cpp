
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "prnPrint.h"
#include "my_functions.h"

#include "CmdLineExec.h"

#include "someThreads.h"
#include "someShare.h"

using namespace Some;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
// for (int i=0;i<100;i++) printf("\n",i);
   gShare.initialize();
}
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RES"   ))  reset();

   if(aCmd->isCmd("GO1"   ))  executeGo1   (aCmd);
   if(aCmd->isCmd("W"     ))  executeWrite (aCmd);
   if(aCmd->isCmd("R"     ))  executeRead  (aCmd);
   if(aCmd->isCmd("START" ))  executeStart (aCmd);
   if(aCmd->isCmd("STOP"  ))  executeStop  (aCmd);
   if(aCmd->isCmd("X"     ))  executeStop  (aCmd);
   if(aCmd->isCmd("SHOW"  ))  executeShow  (aCmd);


   if(aCmd->isCmd("GO2"   ))  executeGo2   (aCmd);
   if(aCmd->isCmd("GO3"   ))  executeGo3   (aCmd);
   if(aCmd->isCmd("GO4"   ))  executeGo4   (aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 100);
   aCmd->setArgDefault(2, 100);

   gShare.mWriter.write(aCmd->argInt(1));
   gShare.mReader.read(aCmd->argInt(2));

   gShare.mWriter.show();
   gShare.mReader.show();
}

//******************************************************************************

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,100);

   gShare.mWriter.write (aCmd->argInt(1));
   gShare.mWriter.show();
}

//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,0);

   gShare.mReader.read  (aCmd->argInt(1));
   gShare.mReader.show();
}

//******************************************************************************

void CmdLineExec::executeStart(Ris::CmdLineCmd* aCmd)
{
   gShare.initialize();
   gThreads.start();
}

//******************************************************************************

void CmdLineExec::executeStop(Ris::CmdLineCmd* aCmd)
{
   gThreads.stop();
}

//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   gShare.update();
   gShare.show();
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   for (int i = 0; i < 30; i++)
   {
      Prn::print(0, "rand %d", my_irand(11, 18));
   }
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}


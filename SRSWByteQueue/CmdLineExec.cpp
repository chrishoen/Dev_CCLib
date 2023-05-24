#include "stdafx.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#include "ccSRSWByteQueue.h"
#include "ccSRSWValueQueue.h"
#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

SRSWByteQueue gQueue;
char gMemory[2000];

CC::SRSWValueQueue<char, 4> gQueue2;

CmdLineExec::CmdLineExec()
{
   SRSWByteQueue_initialize(&gQueue, gMemory, 4);
   gQueue2.reset();
}

void CmdLineExec::reset()
{
   SRSWByteQueue_reset(&gQueue);
   gQueue2.reset();
   Prn::print(0, "RESET %d", SRSWByteQueue_size(&gQueue));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"))   reset();
   if (aCmd->isCmd("W22"))    executeWrite(aCmd);
   if (aCmd->isCmd("R22"))    executeRead(aCmd);
   if (aCmd->isCmd("SHOW22")) executeShow(aCmd);

   if (aCmd->isCmd("W"))      executeWrite2(aCmd);
   if (aCmd->isCmd("R"))      executeRead2(aCmd);
   if (aCmd->isCmd("S"))      executeShow2(aCmd);


   if (aCmd->isCmd("GO1"))    executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))    executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))    executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))    executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))    executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))    executeGo6(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   char tChar = aCmd->argInt(1);

   if (SRSWByteQueue_tryWrite(&gQueue, tChar))
   {
      Prn::print(0, "WRITE PASS  $$ %d", SRSWByteQueue_size(&gQueue));
   }
   else
   {
      Prn::print(0, "WRITE FAIL  $$ %d", SRSWByteQueue_size(&gQueue));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   char tChar = 0;

   if (SRSWByteQueue_tryRead(&gQueue, &tChar))
   {
      Prn::print(0, "READ PASS   $$ %d", SRSWByteQueue_size(&gQueue), (int)tChar);
   }
   else
   {
      Prn::print(0, "READ FAIL   $$ %d", SRSWByteQueue_size(&gQueue));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "SIZE  $$ %d", SRSWByteQueue_size(&gQueue));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWrite2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   char tChar = aCmd->argInt(1);

   if (gQueue2.tryWrite(tChar))
   {
      Prn::print(0, "WRITE2 PASS  $$ %d", gQueue2.size());
   }
   else
   {
      Prn::print(0, "WRITE2 FAIL  $$ %d", gQueue2.size());
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRead2(Ris::CmdLineCmd* aCmd)
{
   char tChar = 0;

   if (gQueue2.tryRead(&tChar))
   {
      Prn::print(0, "READ2 PASS   $$ %d", gQueue2.size());
   }
   else
   {
      Prn::print(0, "READ2 FAIL   $$ %d", gQueue2.size());
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow2(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "SIZE2  $$ %d", gQueue2.size());
   Prn::print(0, "PUTI   $$ %d", gQueue2.mPutIndex);
   Prn::print(0, "GETI   $$ %d", gQueue2.mGetIndex);

   for (int i = 0; i < 5; i++)
   {
      Prn::print(0, "%d %d", i, gQueue2.mElement[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   printf("printf\n");
   Prn::print(0, "Prn::print 0");
   Prn::print(Prn::Show1, "Prn::print Prn::Show1");
   Prn::print(Prn::Show2, "Prn::print Prn::Show");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}


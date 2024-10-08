#include "stdafx.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
   mIntQueue.reset();
   mObjectQueue.reset();
   Prn::print(0, "RESET");
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
   if (aCmd->isCmd("VW"))     executeVWrite(aCmd);
   if (aCmd->isCmd("VR"))     executeVRead(aCmd);
   if (aCmd->isCmd("VS"))     executeVShow(aCmd);

   if (aCmd->isCmd("OW"))     executeOWrite(aCmd);
   if (aCmd->isCmd("OR"))     executeORead(aCmd);
   if (aCmd->isCmd("OS"))     executeOShow(aCmd);

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

void CmdLineExec::executeVWrite(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tValue = aCmd->argInt(1);

   if (mIntQueue.tryWrite(tValue))
   {
      Prn::print(0, "PUT PASS  $$ %d", mIntQueue.size());
   }
   else
   {
      Prn::print(0, "PUT FAIL  $$ %d", mIntQueue.size());
   }
}

void CmdLineExec::executeVRead(Ris::CmdLineCmd* aCmd)
{
   int tValue = 0;

   if (mIntQueue.tryRead(&tValue))
   {
      Prn::print(0, "GET PASS   $$ %d", tValue);
   }
   else
   {
      Prn::print(0, "GET FAIL   $$ %d", mIntQueue.size());
   }
}

void CmdLineExec::executeVShow(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "SIZE   $$ %d", mIntQueue.size());
   Prn::print(0, "PUTI   $$ %d", mIntQueue.mWriteIndex);
   Prn::print(0, "GETI   $$ %d", mIntQueue.mReadIndex);

   for (int i = 0; i < 5; i++)
   {
      Prn::print(0, "%d %d", i, mIntQueue.mElement[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeOWrite(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   if (Some::Class1* tClass1 = mObjectQueue.startWrite())
   {
      tClass1->mCode1 = aCmd->argInt(1);
      mObjectQueue.finishWrite();
      Prn::print(0, "PUT PASS  $$ %d", mObjectQueue.size());
   }
   else
   {
      Prn::print(0, "PUT FAIL  $$ %d", mObjectQueue.size());
   }
}

void CmdLineExec::executeORead(Ris::CmdLineCmd* aCmd)
{
   if (Some::Class1* tClass1 = mObjectQueue.startRead())
   {
      Prn::print(0, "PUT PASS  $$ %d", tClass1->mCode1);
      mObjectQueue.finishRead();
   }
   else
   {
      Prn::print(0, "PUT FAIL  $$ %d", mObjectQueue.size());
   }
}

void CmdLineExec::executeOShow(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "SIZE   $$ %d", mObjectQueue.size());
   Prn::print(0, "PUTI   $$ %d", mObjectQueue.mWriteIndex);
   Prn::print(0, "GETI   $$ %d", mObjectQueue.mReadIndex);

   for (int i = 0; i < 5; i++)
   {
      Prn::print(0, "%d %d", i, mObjectQueue.mElement[i]);
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


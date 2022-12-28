#include "stdafx.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
   Prn::print(0, "RESET");
   mRingBuffer.initialize();
   for (int i = 0; i < 4; i++)
   {
      mRingBuffer.doWrite(i);
   }
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
   if (aCmd->isCmd("PUT"))    executePut(aCmd);
   if (aCmd->isCmd("GET"))    executeGet(aCmd);
   if (aCmd->isCmd("AT"))     executeAt(aCmd);
   if (aCmd->isCmd("MARK1"))  executeMark1(aCmd);
   if (aCmd->isCmd("MARK2"))  executeMark2(aCmd);
   if (aCmd->isCmd("SHOW"))   executeShow(aCmd);

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

void CmdLineExec::executePut(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   int tValue = aCmd->argInt(1);

   mNDelay.doPut(tValue);
   Prn::print(0, "PUT %s", my_string_from_bool(mNDelay.mFullFlag));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGet(Ris::CmdLineCmd* aCmd)
{
   int tValue = mNDelay.doGet();
   Prn::print(0, "GET %d", tValue);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeAt(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   int tIndex = aCmd->argInt(1);

   int tValue = mNDelay.elementAt(tIndex);
   Prn::print(0, "AT  %d", tValue);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeMark1(Ris::CmdLineCmd* aCmd)
{
   for (int i = 0; i < 4; i++)
   {
      mNDelay.elementAt(i) *= -1;
   }
}

void CmdLineExec::executeMark2(Ris::CmdLineCmd* aCmd)
{
   for (int i = 0; i < 4; i++)
   {
      mNDelay.elementAt(i) += 1000 + 100 * i;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "FullFlag    %s", my_string_from_bool(mNDelay.mFullFlag));
   Prn::print(0, "PutIndex    %d", mNDelay.mPutIndex);

   Prn::print(0, "");
   for (int i = 0; i < 4; i++)
   {
      Prn::print(0, "elementAt    %d %d", i, mNDelay.elementAt(i));
   }

   Prn::print(0, "");
   for (int i = 4; i --> 0;)
   {
      Prn::print(0, "history      %d %d", i, mNDelay.elementAt(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "GO1");
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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}


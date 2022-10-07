#include "stdafx.h"

#include "ccRingBufferEx.h"
#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CC::MemoryRingBuffer<short, 5, 0> mRingBuffer;
CC::RingBufferWriter mRingWriter;
CC::RingBufferReader mRingReader;

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
   Prn::print(0, "RESET");
   mRingBuffer.initialize();
   mRingWriter.initialize(&mRingBuffer, &mRingBuffer.mElementArrayMemory);
   mRingReader.initialize(&mRingBuffer, &mRingBuffer.mElementArrayMemory);
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
   short tValue = (short)aCmd->argInt(1);
   mRingWriter.doWrite(&tValue);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGet(Ris::CmdLineCmd* aCmd)
{
   short tValue = 0;
   if (mRingReader.doRead(&tValue))
   {
      Prn::print(0, "GET %d", tValue);
   }
   else
   {
      Prn::print(0, "GET EMPTY");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "AVAILABLE %d", mRingReader.available());
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


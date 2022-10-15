#include "stdafx.h"

#include "ccRingBufferEx.h"
#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CC::MemoryRingBuffer<short, 10, 0> mRingBuffer;
CC::RingBufferWriter mRingWriter;
CC::RingBufferReader mRingReader;

short mWriteArray[1000];
short mReadArray[1000];

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
   Prn::print(0, "RESET");
   mRingBuffer.initialize();
   mRingWriter.initialize(&mRingBuffer, &mRingBuffer.mElementArrayMemory);
   mRingReader.initialize(&mRingBuffer, &mRingBuffer.mElementArrayMemory);
   short tDummy = -99;
   mRingWriter.doWrite(&tDummy);
   mRingReader.doRead(&tDummy);

   for (int i = 0; i < 1000; i++)
   {
      mWriteArray[i] = i;
      mReadArray[i] = 0;
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
   if (aCmd->isCmd("SHOW"))   executeShow(aCmd);
   if (aCmd->isCmd("SHOW2"))  executeShow2(aCmd);
   if (aCmd->isCmd("PUTA"))   executePutArray(aCmd);
   if (aCmd->isCmd("GETA"))   executeGetArray(aCmd);
   if (aCmd->isCmd("SHOWA"))  executeShowArray(aCmd);

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

void CmdLineExec::executePutArray(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tNumElements = aCmd->argInt(1);
   mRingWriter.doWriteArray(&mWriteArray, tNumElements);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGetArray(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tNumElements = aCmd->argInt(1);
   int tCount = mRingReader.doReadArray(&mReadArray, tNumElements);
   Prn::print(0, "GET ARRAY %d", tCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "AVAILABLE       %d", mRingReader.available());
   Prn::print(0, "mNextWriteIndex %lld", mRingBuffer.mNextWriteIndex.load(std::memory_order_acquire));
   Prn::print(0, "mLastReadIndex  %lld", mRingReader.mLastReadIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow2(Ris::CmdLineCmd* aCmd)
{
   for (int i = 0; i < 10; i++)
   {
      Prn::print(0, "%d %d", i, mRingBuffer.mElementArrayMemory[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShowArray(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "AVAILABLE %d", mRingReader.available());
   int tNumElements = aCmd->argInt(1);
   for (int i = 0; i < tNumElements; i++)
   {
      Prn::print(0, "%2d  %3d", i, mReadArray[i]);
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


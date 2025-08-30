#include "stdafx.h"

#include <atomic>

#include "prnPrint.h"
#include "CmdLineExec.h"

using namespace std;

// change201
//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("WT"     ))  executeWriteTail(aCmd);
   if(aCmd->isCmd("RH"     ))  executeReadHead(aCmd);
   if(aCmd->isCmd("WH"     ))  executeWriteHead(aCmd);
   if(aCmd->isCmd("RT"     ))  executeReadTail(aCmd);
   if(aCmd->isCmd("PH"     ))  executePeekHead(aCmd);
   if(aCmd->isCmd("PT"     ))  executePeekTail(aCmd);

   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWriteTail(Ris::CmdLineCmd* aCmd)
{
   int tValue = aCmd->argInt(1);
   if (mList.tryWriteTail(tValue))
   {
      Prn::print(0, "WriteTail pass %d", mList.size());
   }
   else
   {
      Prn::print(0, "WriteTail fail %d", mList.size());
   }
}

void CmdLineExec::executeReadHead(Ris::CmdLineCmd* aCmd)
{
   int tValue = 0;
   if (mList.tryReadHead(&tValue))
   {
      Prn::print(0, "ReadHead pass %d : %d", mList.size(), tValue);
   }
   else
   {
      Prn::print(0, "ReadHead fail %d", mList.size());
   }

}

void CmdLineExec::executeWriteHead(Ris::CmdLineCmd* aCmd)
{
   int tValue = aCmd->argInt(1);
   if (mList.tryWriteHead(tValue))
   {
      Prn::print(0, "WriteHead pass %d", mList.size());
   }
   else
   {
      Prn::print(0, "WriteHead fail %d", mList.size());
   }
}

void CmdLineExec::executeReadTail(Ris::CmdLineCmd* aCmd)
{
   int tValue = 0;
   if (mList.tryReadTail(&tValue))
   {
      Prn::print(0, "ReadTail pass %d : %d", mList.size(), tValue);
   }
   else
   {
      Prn::print(0, "ReadTail fail %d", mList.size());
   }

}

void CmdLineExec::executePeekHead(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "PeekHead %d", mList.size());
   int tValue = 0;
   for (int i = 0; i < mList.size(); i++)
   {
      if (mList.tryPeekHead(i, &tValue))
      {
         Prn::print(0, "PeekHead pass %d %d : %d", i, mList.size(), tValue);
      }
      else
      {
         Prn::print(0, "PeekHead fail %d %d", mList.size());
      }
   }
}

void CmdLineExec::executePeekTail(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "PeekTail %d", mList.size());
   int tValue = 0;
   for (int i = 0; i < mList.size(); i++)
   {
      if (mList.tryPeekTail(i, &tValue))
      {
         Prn::print(0, "PeekTail pass %d %d : %d", i, mList.size(), tValue);
      }
      else
      {
         Prn::print(0, "PeekTail fail %d %d", mList.size());
      }
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
   Prn::print(0, "sizeof(size_t)  %d", (int)sizeof(size_t));
   Prn::print(0, "sizeof(int[10]) %d", (int)sizeof(int[10]));
   Prn::print(0, "sizeof(atomic<int>[10]) %d", (int)sizeof(atomic<int>[10]));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


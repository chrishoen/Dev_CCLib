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
   Prn::print(0, "WriteTail %d", mList.size());
   int tValue = aCmd->argInt(1);
   if (mList.tryWriteTail(tValue))
   {
      Prn::print(0, "WriteTail done %d", mList.size());
   }
   else
   {
      Prn::print(0, "WriteTail fail %d", mList.size());
   }
}

void CmdLineExec::executeReadHead(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "ReadHead %d", mList.size());
   int tValue = 0;
   if (mList.tryReadHead(&tValue))
   {
      Prn::print(0, "ReadHead done %d : %d", mList.size(), tValue);
   }
   else
   {
      Prn::print(0, "ReadHead fail %d", mList.size());
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


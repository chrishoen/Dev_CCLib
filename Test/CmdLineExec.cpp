#include "stdafx.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#include "risProgramTime.h"
#include "risBitUtils.h"
#include "my_functions.h"
#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
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

typedef union PackedS
{
   unsigned char mUint8;
   unsigned short mUint16;
   unsigned int mUint32;
   int mInt32;
} PackedT;

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   PackedT tP; tP.mInt32 = 0;
   tP.mUint8 = 0xff;
   Prn::print(0, "mUint8     %x", tP.mInt32);

   tP.mUint8 += 1;
   Prn::print(0, "mUint8     %x", tP.mInt32);

   tP.mUint8 += 1;
   Prn::print(0, "mUint8     %x", tP.mInt32);

   tP.mUint8 = 0;
   tP.mUint8 -= 1;

   Prn::print(0, "mUint8     %x", tP.mInt32);
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
   Prn::print(0, "Ris::portableGetBinDir() %s", Ris::portableGetBinDir());
   Prn::print(0, "Ris::portableGetBinDir() %s", Ris::portableGetBinDir());
   double tTime = Ris::getProgramTime();
   unsigned int tTimeMS = Ris::getCpuTimeUIntMS();

   Prn::print(0, "Ris::getProgramTime           %10.6f", tTime);
   Prn::print(0, "Ris::getCpuTimeUIntMs         %10d", tTimeMS);
}


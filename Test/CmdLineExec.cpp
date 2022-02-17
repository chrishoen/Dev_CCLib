#include "stdafx.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "string.h"

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

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   static const long long cInvalidValue = -9223372036854775807;
   long long tValue = cInvalidValue;

   Prn::print(0, "tValue    %0llx", tValue);
   Prn::print(0, "tValue    %lld", tValue);

   Prn::print(0, "LLONG_MIN %0llx", LLONG_MIN);
   Prn::print(0, "LLONG_MIN %lld", LLONG_MIN);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   long long tValue1 = LLONG_MIN;
   long long tValue2 = -tValue1;

   Prn::print(0, "tValue1   %0llx", tValue1);
   Prn::print(0, "tValue1   %lld", tValue1);
   Prn::print(0, "tValue2   %0llx", tValue2);
   Prn::print(0, "tValue2   %lld", tValue2);


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
   Prn::print(0, "Ris::portableGetCurrentDir() %s", Ris::portableGetCurrentDir());
   Prn::print(0, "Ris::portableGetProgramDir() %s", Ris::portableGetProgramDir());
   double tTime = Ris::getProgramTime();
   unsigned int tTimeMS = Ris::getCpuTimeUIntMS();

   Prn::print(0, "Ris::getProgramTime           %10.6f", tTime);
   Prn::print(0, "Ris::getCpuTimeUIntMs         %10d", tTimeMS);
}


#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "risContainers.h"

#include "risLUT.h"

#include "CmdLineExec.h"

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
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}

//******************************************************************************

typedef struct Flags1
{
   bool mFirstChild :1;
   bool mLastChild  :1;
} Flags1;

typedef union Flags2
{
   struct
   {
      bool mFirstChild : 1;
      bool mLastChild : 1;
   };
   unsigned char mValue;
} Flags2;

void test_function1(Flags1* aFlags)
{
   aFlags->mFirstChild = true;
}
void test_function2(Flags2* aFlags)
{
   aFlags->mFirstChild = true;
}
void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Flags1 tFlags;
   tFlags.mFirstChild = true;
   Prn::print(0, 0, "sizeof Flags %d", sizeof(Flags1));

}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Flags2 tFlags;
   tFlags.mFirstChild = true;
   tFlags.mValue = 0;
   Prn::print(0, 0, "sizeof Flags %d", sizeof(Flags2));
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "CmdLineExec.h"

using namespace std;

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
//******************************************************************************
//******************************************************************************

typedef union
{
    struct 
    { 
      short mShort1;  
      short mShort2;  
    };
    int mLong;

} MyUnion1;


MyUnion1 MyUnion1Con(int aN1,int aN2)
{
   MyUnion1 tX;
   tX.mShort1 = aN1;
   tX.mShort2 = aN2;
   return tX;
}

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   MyUnion1 tS;
   tS.mShort1 = 1;
   tS.mShort2 = 2;

   Prn::print(0, "sizeof MyUnion1 %d", sizeof(MyUnion1));

   Prn::print(0, "MyUnion1 %d %d %08X",
      tS.mShort1,
      tS.mShort2,
      tS.mLong);

   tS.mLong = 0x00070008;
   Prn::print(0, "MyUnion1 %d %d %08X",
      tS.mShort1,
      tS.mShort2,
      tS.mLong);

   atomic<MyUnion1> tAS;
   Prn::print(0, "MyUnion1 lockfree %d", tAS.is_lock_free());

   MyUnion1 tX = MyUnion1Con(5,6);

   Prn::print(0, "MyUnion11 %d %d %08X",
      tX.mShort1,
      tX.mShort2,
      tX.mLong);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
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


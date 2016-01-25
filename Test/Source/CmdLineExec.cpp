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

typedef union
{
    struct    
    { 
      unsigned short mShort1;  
      unsigned short mShort2;  
    } Parms;
    unsigned mData;
} MyStruct1;

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   MyStruct1 tS;
   tS.mData = 0;
   tS.Parms.mShort1 = 1;
}

//******************************************************************************

typedef union
{
    struct    
    { 
      unsigned short mUShort1;  
      unsigned short mUShort2;  
    };
    unsigned mULong;
} MyStruct2;

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   MyStruct2 tS;
   tS.mUShort1 = 1;
   tS.mUShort2 = 2;

   Prn::print(0, "sizeof MyStruct2 %d", sizeof(MyStruct2));

   Prn::print(0, "MyStruct2 %d %d %08X",
      tS.mUShort1,
      tS.mUShort2,
      tS.mULong);

   tS.mULong = 0x00070008;
   Prn::print(0, "MyStruct2 %d %d %08X",
      tS.mUShort1,
      tS.mUShort2,
      tS.mULong);

   atomic<MyStruct2> tAS;
   Prn::print(0, "MyStruct2 lockfree %d", tAS.is_lock_free());

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


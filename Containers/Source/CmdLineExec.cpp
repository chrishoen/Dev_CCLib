#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "someClass1.h"
#include "LFPointerQueue.h"

#include "CmdLineExec.h"
using namespace Some;

//******************************************************************************

CmdLineExec::CmdLineExec()
{
   mCount=0;
   LFPointerQueue::initialize();
}

//******************************************************************************

void CmdLineExec::reset()
{
   mCount=0;
   LFPointerQueue::initialize();
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1  (aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2  (aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3  (aCmd);
   if(aCmd->isCmd("W"      ))  executeWrite(aCmd);
   if(aCmd->isCmd("R"      ))  executeRead(aCmd);
}

//******************************************************************************


void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
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
} MyStruct;

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   MyStruct tS;
   tS.mData = 0;
   tS.Parms.mShort1 = 1;
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   mCount++;
   Class1A* tObject = new Class1A;
   tObject->mCode1 = mCount;

   bool tStatus = LFPointerQueue::writePtr(tObject);
   if (tStatus)
   {
      Prn::print(0, "WRITE PASS      $$ %d", mCount);
   }
   else
   {
      Prn::print(0, "WRITE FAIL");
   }
}

//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   Class1A* tObject = (Class1A*)LFPointerQueue::readPtr();

   if (tObject)
   {
      Prn::print(0, "READ  PASS      $$ %d", tObject->mCode1);
      delete tObject;
   }
   else
   {
      Prn::print(0, "READ  FAIL");
   }
}

#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "prnPrint.h"
#include "someClass1.h"

#include "CmdLineExec.h"
using namespace Some;

//******************************************************************************

CmdLineExec::CmdLineExec()
{
   mCount=0;
   mPointerQueue.initialize(4);
}

//******************************************************************************

void CmdLineExec::reset()
{
   mCount=0;
   mPointerQueue.initialize(4);
   mBlockQueue.initialize(4,sizeof(Class1A));
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1    (aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2    (aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3    (aCmd);
   if(aCmd->isCmd("WP"     ))  executeWriteP (aCmd);
   if(aCmd->isCmd("RP"     ))  executeReadP  (aCmd);
   if(aCmd->isCmd("W"      ))  executeWriteB (aCmd);
   if(aCmd->isCmd("R"      ))  executeReadB  (aCmd);
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
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWriteP(Ris::CmdLineCmd* aCmd)
{
   mCount++;
   Class1A* tObject = new Class1A;
   tObject->mCode1 = mCount;

   bool tStatus = mPointerQueue.writePtr(tObject);
   if (tStatus)
   {
      Prn::print(0, "WRITE PASS      $$ %d", mCount);
   }
   else
   {
      Prn::print(0, "WRITE FAIL");
      delete tObject;
   }
}

//******************************************************************************

void CmdLineExec::executeReadP(Ris::CmdLineCmd* aCmd)
{
   Class1A* tObject = (Class1A*)mPointerQueue.readPtr();

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
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWriteB(Ris::CmdLineCmd* aCmd)
{
   mCount++;

   int tIndex;
   void* tBlock = mBlockQueue.startWrite(&tIndex);
   if (tBlock)
   {
      Class1A* tObject = new(tBlock) Class1A;
      tObject->mCode1 = mCount;
      mBlockQueue.finishWrite(tIndex);

      Prn::print(0, "WRITE PASS      $$ %d", mCount);
   }
   else
   {
      Prn::print(0, "WRITE FAIL");
   }
}

//******************************************************************************

void CmdLineExec::executeReadB(Ris::CmdLineCmd* aCmd)
{
   int tIndex;
   Class1A* tObject = (Class1A*)mBlockQueue.startRead(&tIndex);

   if (tObject)
   {
      Prn::print(0, "READ  PASS      $$ %d        %d", tObject->mCode1,tObject->mCode2);
      mBlockQueue.finishRead(tIndex);
   }
   else
   {
      Prn::print(0, "READ  FAIL");
   }
}

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

// int tSize = CC::LFValueQueue<int>::getMemorySize(4);
// mIntQueue.initialize(4,malloc(tSize));
}

//******************************************************************************

void CmdLineExec::reset()
{
   mCount=1000;
   mIntQueue.initialize(4);
   mPointerQueue.initialize(4);
   mPacketQueue.initialize(4,sizeof(Class1A));

   printf("sizeof(Class1A) %d\n",sizeof(Class1A));
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
   if(aCmd->isCmd("WK"     ))  executeWriteK (aCmd);
   if(aCmd->isCmd("RK"     ))  executeReadK  (aCmd);
   if(aCmd->isCmd("WI"     ))  executeWriteI (aCmd);
   if(aCmd->isCmd("RI"     ))  executeReadI  (aCmd);
   if(aCmd->isCmd("W"      ))  executeWriteK (aCmd);
   if(aCmd->isCmd("R"      ))  executeReadK  (aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWriteK(Ris::CmdLineCmd* aCmd)
{
   mCount++;

   int tIndex;
   void* tPacket = mPacketQueue.startWrite(&tIndex);
   if (tPacket)
   {
      Class1A* tObject = new(tPacket) Class1A;
      tObject->mCode1 = mCount;
      mPacketQueue.finishWrite(tIndex);

      Prn::print(0, "WRITE PASS      $$ %d        %d", mCount,tIndex);
   }
   else
   {
      Prn::print(0, "WRITE FAIL");
   }
}

//******************************************************************************

void CmdLineExec::executeReadK(Ris::CmdLineCmd* aCmd)
{
   int tIndex;
   Class1A* tObject = (Class1A*)mPacketQueue.startRead(&tIndex);

   if (tObject)
   {
      Prn::print(0, "READ  PASS      $$ %d        %d", tObject->mCode1,tIndex);
//    Prn::print(0, "READ  PASS      $$ %d        %d", tObject->mCode1,tObject->mCode2);
      mPacketQueue.finishRead(tIndex);
   }
   else
   {
      Prn::print(0, "READ  FAIL");
   }
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

void CmdLineExec::executeWriteI(Ris::CmdLineCmd* aCmd)
{
   if (mIntQueue.tryWrite(++mCount))
   {
      Prn::print(0, "WRITE PASS  $$ %d", mCount);
   }
   else
   {
      Prn::print(0, "WRITE FAIL");
   }
}

//******************************************************************************

void CmdLineExec::executeReadI(Ris::CmdLineCmd* aCmd)
{
   int tCount=0;
   if (mIntQueue.tryRead(&tCount))
   {
      Prn::print(0, "READ            PASS  $$ %d", tCount);
   }
   else
   {
      Prn::print(0, "READ            FAIL");
   }
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


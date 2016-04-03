#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "ccValueQueue.h"
#include "ccValueStack.h"
#include "ccFreeListIndexStack.h"
#include "ccFreeListIndexStackSM.h"
#include "ccLFFreeListIndexStack.h"
#include "ccFreeList.h"

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
   if(aCmd->isCmd("GO6"    ))  executeGo6(aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7(aCmd);
   if(aCmd->isCmd("GO8"    ))  executeGo8(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   CC::FreeListIndexStack tStack;
   tStack.initialize(4);
   
   int tY = 999;

   Prn::print(0, "Stack %d  %d", tStack.size(),tY);

   tStack.pop(&tY);
   Prn::print(0, "Pop   %d  %d", tStack.size(),tY);

   tStack.push(tY);
   Prn::print(0, "Push  %d  %d", tStack.size(),tY);

   tStack.pop(&tY);
   Prn::print(0, "Pop   %d  %d", tStack.size(),tY);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   CC::LFFreeListIndexStack tStack;
   tStack.initialize(4);
   
   int tY = 999;

   Prn::print(0, "Stack %d", tStack.size());

   if (tStack.pop(&tY))
   {
      Prn::print(0, "Pop1   %d  %d", tStack.size(), tY);
   }
   else
   {
      Prn::print(0, "Pop1   %d  FAIL", tStack.size());
   }

   if (tStack.pop(&tY))
   {
      Prn::print(0, "Pop2   %d  %d", tStack.size(), tY);
   }
   else
   {
      Prn::print(0, "Pop2   %d  FAIL", tStack.size());
   }

   if (tStack.pop(&tY))
   {
      Prn::print(0, "Pop3   %d  %d", tStack.size(), tY);
   }
   else
   {
      Prn::print(0, "Pop3   %d  FAIL", tStack.size());
   }

   if (tStack.pop(&tY))
   {
      Prn::print(0, "Pop4   %d  %d", tStack.size(), tY);
   }
   else
   {
      Prn::print(0, "Pop4   %d  FAIL", tStack.size());
   }

   if (tStack.pop(&tY))
   {
      Prn::print(0, "Pop5   %d  %d", tStack.size(), tY);
   }
   else
   {
      Prn::print(0, "Pop5   %d  FAIL", tStack.size());
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,4);

   int tNumBlocks = aCmd->argInt(1);
   int tSize = CC::FreeListIndexStackSM::getSharedMemorySize(tNumBlocks);

   void* tMemory = malloc(tSize);
   CC::FreeListIndexStackSM tStack;
   tStack.initialize(tNumBlocks,tMemory);


   int tY = 999;

   Prn::print(0, "Stack %d  %d", tStack.size(),tY);

   tStack.pop(&tY);
   Prn::print(0, "Pop   %d  %d", tStack.size(),tY);

   tStack.push(tY);
   Prn::print(0, "Push  %d  %d", tStack.size(),tY);

   tStack.pop(&tY);
   Prn::print(0, "Pop   %d  %d", tStack.size(),tY);

   free(tMemory);
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
   CC::ValueQueue<int> tQueue;
   tQueue.initialize(4);
   
   int tY;
   tQueue.put(101);
   tQueue.put(102);
   tQueue.put(103);
   tQueue.put(104);

   Prn::print(0, "Queue %d  %d  %d", tQueue.size(), tQueue.isGet(), tQueue.elementToGet());

   tY = tQueue.get();

   Prn::print(0, "Get   %d", tY);
   Prn::print(0, "Queue %d  %d  %d", tQueue.size(), tQueue.isGet(), tQueue.elementToGet());
}

//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
   CC::ValueStack<int> tStack;
   tStack.initialize(4);
   
   int tY;
   tStack.push(101);
   tStack.push(102);
   tStack.push(103);
   tStack.push(104);

   Prn::print(0, "Stack %d", tStack.size());

   tStack.pop(&tY);

   Prn::print(0, "Get   %d", tY);

   Prn::print(0, "Stack %d", tStack.size());
}


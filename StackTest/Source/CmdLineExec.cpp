#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "ccValueQueue.h"
#include "ccValueStack.h"
#include "ccBlockPoolIndexStack.h"
#include "ccBlockPoolLFIndexStack.h"
#include "ccBlockPoolParms.h"
#include "ccBlockPoolFreeList.h"

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
   if(aCmd->isCmd("GO11"   ))  executeGo11 (aCmd);
   if(aCmd->isCmd("GO12"   ))  executeGo12 (aCmd);
   if(aCmd->isCmd("GO21"   ))  executeGo21 (aCmd);
   if(aCmd->isCmd("GO22"   ))  executeGo22 (aCmd);
   if(aCmd->isCmd("GO31"   ))  executeGo31 (aCmd);
   if(aCmd->isCmd("GO32"   ))  executeGo32 (aCmd);
   if(aCmd->isCmd("GO41"   ))  executeGo41 (aCmd);
   if(aCmd->isCmd("GO42"   ))  executeGo42 (aCmd);

   if(aCmd->isCmd("GO5"    ))  executeGo5  (aCmd);
   if(aCmd->isCmd("GO6"    ))  executeGo6  (aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7  (aCmd);
   if(aCmd->isCmd("GO8"    ))  executeGo8  (aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mPoolIndex     = 1;
   tBlockPoolParms.mBlockPoolType = CC::cBlockPoolType_FreeList;
   tBlockPoolParms.mNumBlocks     = 2;
   tBlockPoolParms.mBlockSize     = 1;

   int tSize=0;
   tSize = CC::BlockPoolFreeList::getMemorySize(&tBlockPoolParms);
   Prn::print(0, "%d",tSize);

   tBlockPoolParms.mBlockPoolType = CC::cBlockPoolType_FreeList;
   tSize = CC::BlockPoolFreeList::getMemorySize(&tBlockPoolParms);
   Prn::print(0, "%d",tSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo11(Ris::CmdLineCmd* aCmd)
{
   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mNumBlocks = 4;

   CC::BlockPoolIndexStack tStack;
   tStack.initialize(&tBlockPoolParms);
   
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

void CmdLineExec::executeGo12(Ris::CmdLineCmd* aCmd)
{
   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mNumBlocks = 4;

   CC::BlockPoolLFIndexStack tStack;
   tStack.initialize(&tBlockPoolParms);
   
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

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,4);

   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mNumBlocks = aCmd->argInt(1);

   CC::BlockPoolIndexStack tStack;
   tStack.initialize(&tBlockPoolParms);

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

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,4);

   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mNumBlocks = aCmd->argInt(1);

   CC::BlockPoolLFIndexStack tStack;
   tStack.initialize(&tBlockPoolParms);

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

void CmdLineExec::executeGo31(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,4);

   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mNumBlocks = aCmd->argInt(1);
   void* tMemory = malloc(CC::BlockPoolIndexStack::getMemorySize(&tBlockPoolParms));

   CC::BlockPoolIndexStack tStack;
   tStack.initialize(&tBlockPoolParms,tMemory);

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
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo32(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,4);

   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mNumBlocks = aCmd->argInt(1);
   void* tMemory = malloc(CC::BlockPoolIndexStack::getMemorySize(&tBlockPoolParms));

   CC::BlockPoolLFIndexStack tStack;
   tStack.initialize(&tBlockPoolParms,tMemory);

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
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo41(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,4);

   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mNumBlocks = aCmd->argInt(1);
   void* tMemory = malloc(CC::BlockPoolIndexStack::getMemorySize(&tBlockPoolParms));

   CC::BlockPoolIndexStack tStack;
   tStack.initialize(&tBlockPoolParms,tMemory);
   
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

void CmdLineExec::executeGo42(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,4);

   CC::BlockPoolParms tBlockPoolParms;
   tBlockPoolParms.mNumBlocks = aCmd->argInt(1);
   void* tMemory = malloc(CC::BlockPoolIndexStack::getMemorySize(&tBlockPoolParms));

   CC::BlockPoolIndexStack tStack;
   tStack.initialize(&tBlockPoolParms,tMemory);
   
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

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
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


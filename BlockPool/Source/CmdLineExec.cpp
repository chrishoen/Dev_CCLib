#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "risContainers.h"

#include "someClass6.h"
using namespace Some;

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   Class6A::initializeLongTermBlockPool(1000);
   Class6B::initializeLongTermBlockPool(1000);
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

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Class6A* t6A = Class6A::allocate();
   t6A->sayHello();
   t6A->deallocate();
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Class6B* t6B = Class6B::allocate();
   t6B->sayHello();
   t6B->deallocate();
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Class6A::mBlockPool.show();
   Class6B::mBlockPool.show();

   Class6A* t6A = Class6A::allocate();

   Class6A::mBlockPool.show();
   Class6B::mBlockPool.show();

   Class6B* t6B = Class6B::allocate();

   Class6A::mBlockPool.show();
   Class6B::mBlockPool.show();

   t6A->deallocate();

   Class6A::mBlockPool.show();
   Class6B::mBlockPool.show();

   t6B->deallocate();

   Class6A::mBlockPool.show();
   Class6B::mBlockPool.show();
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


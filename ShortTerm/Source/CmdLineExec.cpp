#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "ccScratchMemory.h"
#include "someClass1.h"

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

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tN = aCmd->argInt(1);

   for (int i = 0; i < tN; i++)
   {
      Some::Class1A* tX = CC::newScratchMemory<Some::Class1A>();
      tX->sayHello();
      printf("check %d %d\n", i, CC::checkScratchMemory(tX));
   }
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Some::Class1A* tX = CC::newScratchMemory<Some::Class1A>(101,102);
   tX->sayHello();
   printf("check %d\n", CC::checkScratchMemory(tX));
   delete tX;
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Some::Class1A* tX = new Some::Class1A(101,102);
   delete tX;
}

//******************************************************************************

char* getHelloWorldString(int aX)
{
   // This allocates memory for a string on the short term heap
   char* tStr = (char*)CC::allocateFromScratchMemory(100);
   // This writes to the string
   sprintf(tStr, "Hello World %d", aX);
   // Return the string
   return tStr;
}
void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   // This gets the string and printfs it and then forgets about it. The string
   // is nonpersistent, but has a lifetime long enough to be useful. The 
   // lifetime expires after the printf.

   printf("MyHelloWorld %s", getHelloWorldString(101));
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


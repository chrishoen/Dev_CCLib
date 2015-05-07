#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "ccPointerHelper.h"

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
   CC::PointerUnion<void> tPointerUnion;
   tPointerUnion.mPointer = malloc(100);
   printf("%08X\n", tPointerUnion.mAddress);
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefaultUnsigned(1,1);

   unsigned int tSize = aCmd->argUnsigned(1);

   printf("%08X %08X\n", tSize,CC::alignSizeEightBytes(tSize));
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   unsigned int tN = 0x7FFFFFF1;
   printf("%08X %08X\n", tN,((tN>>3)<<3));
}

//******************************************************************************

inline size_t MessageHeap_alignSize(size_t aSize)
{
   // If this is a 32 bit system
   if (sizeof(int*) == 4)
   {
      // Align the size to be on an eight byte boundary
      if ((aSize & 7) == 0) return aSize;
      else return ((aSize >> 3) << 3) + 8;
   }
   else
   // Else this is a 64 bit system
   {
      // Align the size to be on a sixteen byte boundary
      if ((aSize & 15) == 0) return aSize;
      else return ((aSize >> 4) << 4) + 16;
   }
}


void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   printf("sizeof(int*) %d\n", sizeof(int*));

   for (unsigned tN = 0; tN < 34; tN++)
   {
      printf("%5d %08X %08X\n", tN, tN, MessageHeap_alignSize(tN));
   }
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


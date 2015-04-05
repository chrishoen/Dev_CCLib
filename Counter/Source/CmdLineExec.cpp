#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "Modulo.h"

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
   Counter4096_128hz tCounter;
   for (int i = 0; i < 4096; i++)
   {
      tCounter.convertFromZPlus(i);
      printf("%5d %5d %5d %d\n", i,
         tCounter.mQuotient,
         tCounter.mRemainder,
         tCounter.isFirst());
   }
}
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Counter32_8hz tCounter;
   for (int i = 0; i < 32; i++)
   {
      tCounter.convertFromZPlus(i);
      printf("%5d %5d %5d\n", i,
         tCounter.mQuotient,
         tCounter.mRemainder);
   }
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Counter32_8hz tCounter;
   Counter32_8hz tInverse;
   for (int i = 0; i < 32; i++)
   {
      tCounter.convertFromZPlus(i);
      tInverse = tCounter.inverse();

      printf("%5d $$ %5d %5d   $$ %5d %5d\n", i,
         tCounter.mQuotient,
         tCounter.mRemainder,
         tInverse.mQuotient,
         tInverse.mRemainder);
   }
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Counter32_8hz tCounter;
   Counter32_8hz tInverse;
   Counter32_8hz tSum;

   for (int i = 0; i < 32; i++)
   {
      tCounter.convertFromZPlus(i);
      tInverse = tCounter.inverse();
      tSum = tCounter.add(tInverse);

      printf("%5d $$ %5d %5d   $$ %5d %5d  $$ %5d %5d\n", i,
         tCounter.mQuotient,
         tCounter.mRemainder,
         tInverse.mQuotient,
         tInverse.mRemainder,
         tSum.mQuotient,
         tSum.mRemainder);
   }
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   Counter32_8hz tCounter;
   unsigned      tZPlusM;

   for (int i = 0; i < 64; i++)
   {
      tCounter.convertFromZPlus(i);
      tZPlusM = tCounter.convertToZPlusM();
      printf("%5d %5d %5d %5d\n", i,
         tCounter.mQuotient,
         tCounter.mRemainder,
         tZPlusM);
   }
}


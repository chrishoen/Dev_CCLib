#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "ModuloMN_PowerOfTwo.h"

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

// Counter4096_128hz tCounter;
// Counter4096_128hz tInverse;
// Counter4096_128hz tSum;

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
   aCmd->setArgDefaultUnsigned(1, 0);
   aCmd->setArgDefaultUnsigned(2, 1);

   Counter32_8hz tCounter;
   Counter32_8hz tDelta(aCmd->argUnsigned(1),aCmd->argUnsigned(2));
   Counter32_8hz tSum;

   for (int i = 0; i < 32; i++)
   {
      tCounter.convertFromZPlus(i);
      tSum = tCounter.add(tDelta);

      printf("%5d $$ %5d %5d   $$ %5d %5d\n", i,
         tCounter.mQuotient,
         tCounter.mRemainder,
         tSum.mQuotient,
         tSum.mRemainder);
   }
}


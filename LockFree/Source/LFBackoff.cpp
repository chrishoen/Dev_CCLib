#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "prnPrint.h"

#include "my_functions.h"
#include "LFBackoff.h"


__declspec(thread) int gLFBackoffInitial1;
__declspec(thread) int gLFBackoffInitial2;
__declspec(thread) int gLFBackoffInitial3;
__declspec(thread) int gLFBackoffInitial4;



LFBackoff::LFBackoff(int aMode)
{
   mInitial=0;
   switch (aMode)
   {
   case 1: mInitial = gLFBackoffInitial1; break;
   case 2: mInitial = gLFBackoffInitial2; break;
   case 3: mInitial = gLFBackoffInitial3; break;
   case 4: mInitial = gLFBackoffInitial4; break;
   }
   mStep    =  2;
   mThreshold = 8000;
   mCurrent = mInitial;
   mCount=0;

}

void LFBackoff::backoff()
{
   if (mInitial==0)return;
   for (int k = 0; k < mCurrent; ++k) mCount++;
   mCurrent *= mStep;
   if ( mCurrent > mThreshold ) mCurrent = mThreshold;
}

void LFBackoff::nop(){}

void LFBackoff_reset()
{
   gLFBackoffInitial1 = 0;
   gLFBackoffInitial2 = 0;
   gLFBackoffInitial3 = 0;
   gLFBackoffInitial4 = 0;
   return;
   printf("gLFBackoffInitial %d\n",gLFBackoffInitial1);
}

void LFBackoff_reset(int aN1,int aN2)
{
   gLFBackoffInitial1 = my_irand(aN1, aN2);
   gLFBackoffInitial2 = my_irand(aN1, aN2);
   gLFBackoffInitial3 = my_irand(aN1, aN2);
   gLFBackoffInitial4 = my_irand(aN1, aN2);
   return;
   printf("gLFBackoffInitial1 %d\n",gLFBackoffInitial1);
   printf("gLFBackoffInitial2 %d\n",gLFBackoffInitial2);
   printf("gLFBackoffInitial3 %d\n",gLFBackoffInitial3);
   printf("gLFBackoffInitial4 %d\n",gLFBackoffInitial4);
}

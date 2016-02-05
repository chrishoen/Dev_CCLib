#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "CmdLineExec.h"

#include "LFIndex.h"

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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   LFIndex tY = LFIndex(1,2);
   int tI = tY.mIndex;
   AtomicLFIndex tX;

   tY = tX.load();
   tI = tX.load().mCount;

   Prn::print(0, "MyUnion11 %d %d",
      tY.mIndex,
      tY.mCount);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   LFIndex tY(1,2);
   AtomicLFIndex tX = tY;

   Prn::print(0, "tY %d %d",
      tY.mIndex,
      tY.mCount);

   Prn::print(0, "tX %d %d",
      tX.load().mIndex,
      tX.load().mCount);

   int* tPI = (int*)&tX;
   int& tRI = (int&)*tPI;
   atomic<int>& tARI = (atomic<int>&)*tPI;


   atomic<int>* tAPI1 = (atomic<int>*)&tX;
   atomic<int>& tARI2 = (atomic<int>&)*tAPI1;

   Prn::print(0, "tARI2 %d",tARI2);

   tARI2 = 8;
   Prn::print(0, "tARI2 %d",tARI2);

   Prn::print(0, "tX %d %d",
      tX.load().mIndex,
      tX.load().mCount);
}

//******************************************************************************

char* my_as_stringLLU(char* aString,unsigned long long aValue)
{
   char tString1[24];
   char tString2[24];
   char tString3[24];
   char tString4[24];
   memset(tString2, '.',23);
   memset(tString3, '.',23);
   memset(tString4, '.',23);
   tString2[23]=0;
   tString3[23]=0;
   tString4[23]=0;

   sprintf(tString1, "%llu",aValue);
   int tIndex[18] = {0,1,2, 4,5,6, 8,9,10 ,12,13,14 ,16,17,18, 20,21,22};

   int tLen1=(int)strlen(tString1);
   int tLen2=0;
   int tLen3=0;
   int tLen4=0;
   int j=0;
   char tSkip = ',';

   for (int i = 0; i< tLen1; i++)
   {
      j = tLen1-i-1;
      tString2[j] = tString1[i];
   }
   tLen2=tLen1;
   tString2[tLen2]=0;

   j=0;
   for (int i = 0; i< tLen2; i++)
   {
      tString3[j] = tString2[i];
      j++;
      if (i % 3 == 2) tString3[j++]=tSkip;
   }
   if (tString3[j-1]==tSkip)j--;

   tLen3=j;
   tString3[tLen3]=0;

   for (int i = 0; i< tLen3; i++)
   {
      j = tLen3-i-1;
      tString4[j] = tString3[i];
   }
   tLen4=tLen3;
   tString4[tLen4]=0;

   strncpy(aString,tString4,tLen4);
   aString[tLen4]=0;

   return aString;
}

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   char tString[50];
   unsigned long long tX = 100*1000000000LL;

   tX = 100876543210LL;
   Prn::print(0,"%llu", tX);
   Prn::print(0,"%s$", my_as_stringLLU(tString,tX));
   Prn::print(0,"");

   tX = 0LL;
   Prn::print(0,"%llu", tX);
   Prn::print(0,"%s$", my_as_stringLLU(tString,tX));
   Prn::print(0,"");

   tX = 210LL;
   Prn::print(0,"%llu", tX);
   Prn::print(0,"%s$", my_as_stringLLU(tString,tX));
   Prn::print(0,"");

   tX = 3210LL;
   Prn::print(0,"%llu", tX);
   Prn::print(0,"%s$", my_as_stringLLU(tString,tX));
   Prn::print(0,"");

   tX = 45100876543210LL;
   Prn::print(0,"%llu", tX);
   Prn::print(0,"%s$", my_as_stringLLU(tString,tX));
   Prn::print(0,"");

}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   for (int i = 0; i < 1000; i++)
   {
      Prn::print(0,"%08X",rand());

   }
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


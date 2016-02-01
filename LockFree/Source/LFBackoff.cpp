#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "prnPrint.h"

#include "my_functions.h"

#define  _LFBACKOFF_CPP_
#include "LFBackoff.h"


namespace LFBackoff
{
   void initialize(int aN1, int aN2)
   {
      mWaitEnable = aN2!=0;
      if (!mWaitEnable)return;

      for (int i = 0; i < cWaitArraySize; i++)
      {
         mWaitArray[i] = my_irand(aN1, aN2);
      }
      mWaitIndex=0;
      Prn::print(0, "LFBackoff::initialize %d %d %d", aN1, aN2, mWaitArray[0]);
   }

   void show()
   {
      for (int i = 0; i < cWaitArraySize-10; i++)
      {
         Prn::print(0, "%d %d", i, mWaitArray[i]);
      }
   }

}//namespace
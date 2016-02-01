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
      for (int i = 0; i < cWaitArraySize; i++)
      {
         mWaitArray[i] = my_irand(aN1, aN2);
      }
      mWaitIndex=0;
   }

}//namespace
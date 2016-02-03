#ifndef _LFBACKOFF_H_
#define _LFBACKOFF_H_

#include "my_functions.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFBackoff
{
   inline void delay(int aDelay)
   {
      if (aDelay==0)return;
      int tCount=0;
      int tLoop = my_irand(0, aDelay);
      for (int i=0;i<tLoop;i++) tCount++;
   }

}//namespace
#endif


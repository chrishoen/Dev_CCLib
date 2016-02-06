#ifndef _LFBACKOFF_H_
#define _LFBACKOFF_H_

#include <math.h>
#include "my_functions.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

class LFBackoff
{
public:

   //---------------------------------------------------------------------------
   // Members

   int  mInitial1;
   int  mInitial2;
   int  mDelay1;
   int  mDelay2;
   int  mCount;
   bool mEnable;

   //---------------------------------------------------------------------------
   // Constructor

   inline LFBackoff()
   {
      mInitial1=0;
      mInitial2=0;
      mDelay1=0;
      mDelay2=0;
      mCount=0;
      mEnable=false;
   }

   inline LFBackoff(int aDelay1,int aDelay2)
   {
      mInitial1=aDelay1;
      mInitial2=aDelay2;
      mDelay1=aDelay1;
      mDelay2=aDelay2;
      mCount=0;
      mEnable = aDelay2!=0;
   }

   //---------------------------------------------------------------------------
   // Set delays

   inline void setDelay(int aDelay1, int aDelay2)
   {
      if (aDelay2 == 0)
      {
         mEnable=false;
         return;
      }

      mInitial1 = aDelay1;
      mInitial2 = aDelay2;
      mDelay1 = mInitial1;
      mDelay2 = mInitial2;
      mCount = 0;
      mEnable = true;
   }

   inline static int convertFromUsec(double aDelay)
   {
      int tN = lround(385.79*aDelay - 38.827);
      if (tN<0) tN=0;
      return tN;
   }

   inline void setDelay(double aDelayUsec1, double aDelayUsec2)
   {
      if (aDelayUsec2 == 0.0)
      {
         mEnable = false;
         return;
      }

      mInitial1 = convertFromUsec(aDelayUsec1);
      mInitial2 = convertFromUsec(aDelayUsec2);
      mDelay1 = mInitial1;
      mDelay2 = mInitial2;
      mCount = 0;
      mEnable = true;
   }

   //---------------------------------------------------------------------------
   // Backoff

   inline void reset()
   {
      mCount=0;
      mDelay1 = mInitial1;
      mDelay2 = mInitial2;
   }

   inline void backoff()
   {
      if (!mEnable)return;

      int tDummy=0;
      int tLoop = my_irand(mDelay1,mDelay2);
      for (int i=0;i<tLoop;i++) tDummy++;

      if (++mCount < 5)
      {
         mDelay1 = mDelay1 * 2;
         mDelay2 = mDelay2 * 2;
      }
   }
};


#endif


#pragma once

#include <math.h>
#include "my_functions.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

class SoftDelay
{
public:

   //---------------------------------------------------------------------------
   // Members

   int  mDelay;
   volatile int  mCount;

   //---------------------------------------------------------------------------
   // Convert from microseconds to counts

   inline static int convertFromUsec(double aDelay)
   {
      int tN = 0;
#if defined (_MSC_VER)
      tN = lround(305 * aDelay - 6.0);
#else
      tN = lround(305 * aDelay - 6.0);
#endif
      if (tN<0) tN=0;
      return tN;
   }

   //---------------------------------------------------------------------------
   // Constructor

   inline SoftDelay()
   {
      mDelay=0;
      mCount=0;
   }

   inline SoftDelay(double aDelayUsec)
   {
      mDelay = convertFromUsec(aDelayUsec);
      mCount=0;
   }

   inline void setDelay(double aDelayUsec)
   {
      mDelay = convertFromUsec(aDelayUsec);
      mCount=0;
   }

   //---------------------------------------------------------------------------
   // Reset

   inline void reset()
   {
      mDelay=0;
      mCount=0;
   }

   //---------------------------------------------------------------------------
   // Constant backoff

   inline void delay()
   {
      for (int i=0;i<mDelay;i++) mCount++;
   }
};


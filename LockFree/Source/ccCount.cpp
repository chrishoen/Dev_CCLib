/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include "ccCount.h"
namespace CC
{
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Regionals

   int mCount = 0;
   int mMaxCount = 4;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryDecrement1()
   {
      // Guard
      if (mCount == 0) return false;

      int tCompare, tExchange, tOriginal;
      while (true)
      {
         tCompare = mCount;
         if (tCompare == 0) return false;
         tExchange = tCompare - 1;
         tOriginal = InterlockedCompareExchange((PLONG)&mCount, tExchange, tCompare);
         if (tOriginal == tCompare) return true;
      }
   }

   bool tryDecrement2(int* aCount,int aLimit)
   {
      // Guard
      if (*aCount == aLimit) return false;

      int tCompare, tExchange, tOriginal;
      while (true)
      {
         tCompare = *aCount;
         if (tCompare == aLimit) return false;
         tExchange = tCompare - 1;
         tOriginal = InterlockedCompareExchange((PLONG)aCount, tExchange, tCompare);
         if (tOriginal == tCompare) return true;
      }
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryIncrement1()
   {
      // Guard
      if (mCount == mMaxCount) return false;

      int tCompare, tExchange, tOriginal;
      while (true)
      {
         tCompare = mCount;
         if (tCompare == mMaxCount) return false;
         tExchange = tCompare - 1;
         tOriginal = InterlockedCompareExchange((PLONG)&mCount, tExchange, tCompare);
         if (tOriginal == tCompare) return true;
      }
   }

   bool tryIncrement2(int* aCount,int aLimit)
   {
      // Guard
      if (*aCount == aLimit) return false;

      int tCompare, tExchange, tOriginal;
      while (true)
      {
         tCompare = *aCount;
         if (tCompare == aLimit) return false;
         tExchange = tCompare + 1;
         tOriginal = InterlockedCompareExchange((PLONG)aCount, tExchange, tCompare);
         if (tOriginal == tCompare) return true;
      }
   }

}//namespace
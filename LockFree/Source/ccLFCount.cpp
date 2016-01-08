/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include "ccLFCount.h"
namespace CC
{
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryLFDecrement(
      int* aCount,
      int  aLimit,
      int* aOriginalCount,
      int* aNewCount)
   {
      // Guard
      if (*aCount <= aLimit) return false;

      int tCompare, tExchange, tOriginal;
      while (true)
      {
         tCompare = *aCount;
         if (tCompare <= aLimit) return false;
         tExchange = tCompare - 1;
         tOriginal = InterlockedCompareExchange((PLONG)aCount, tExchange, tCompare);
         if (tOriginal == tCompare) break;
      }

      if (aOriginalCount)
      {
         *aOriginalCount = tOriginal;
      }

      if (aNewCount)
      {
         *aNewCount = tExchange;
      }

      return true;

   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryLFIncrement(
      int* aCount,
      int  aLimit,
      int* aOriginalCount,
      int* aNewCount)
   {

      // Guard
      if (*aCount >= aLimit) return false;

      int tCompare, tExchange, tOriginal;
      while (true)
      {
         tCompare = *aCount;
         if (tCompare >= aLimit) return false;
         tExchange = tCompare + 1;
         tOriginal = InterlockedCompareExchange((PLONG)aCount, tExchange, tCompare);
         if (tOriginal == tCompare) break;
      }

      if (aOriginalCount)
      {
         *aOriginalCount = tOriginal;
      }

      if (aNewCount)
      {
         *aNewCount = tExchange;
      }

      return true;
   }

}//namespace
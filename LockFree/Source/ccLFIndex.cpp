/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include "ccLFIndex.h"
namespace CC
{
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryLFDecrement(
      int* aIndex,
      int  aLimit,
      int* aOriginalIndex,
      int* aNewIndex)
   {
      // Guard
      if (*aIndex <= aLimit) return false;

      int tCompare, tExchange, tOriginal;
      while (true)
      {
         tCompare = *aIndex;
         if (tCompare <= aLimit) return false;
         tExchange = tCompare - 1;
         tOriginal = InterlockedCompareExchange((PLONG)aIndex, tExchange, tCompare);
         if (tOriginal == tCompare) break;
      }

      // Store results
      if (aOriginalIndex)  *aOriginalIndex = tOriginal;
      if (aNewIndex)       *aNewIndex = tExchange;
      return true;

   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryLFIncrement(
      int* aIndex,
      int  aLimit,
      int* aOriginalIndex,
      int* aNewIndex)
   {

      // Guard
      if (*aIndex >= aLimit) return false;

      int tCompare, tExchange, tOriginal;
      while (true)
      {
         tCompare = *aIndex;
         if (tCompare >= aLimit) return false;
         tExchange = tCompare + 1;
         tOriginal = InterlockedCompareExchange((PLONG)aIndex, tExchange, tCompare);
         if (tOriginal == tCompare) break;
      }

      // Store results
      if (aOriginalIndex)  *aOriginalIndex = tOriginal;
      if (aNewIndex)       *aNewIndex = tExchange;
      return true;
   }

}//namespace
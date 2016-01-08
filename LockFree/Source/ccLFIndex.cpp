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
   // This attempts to decrement an index, it returns true if successful.
   // It returns false if the index is at a lower limit.
   //
   // It uses an atomic compare and exchange operation to avoid concurrency 
   // violations.
   //
   // aIndex is a pointer to an index variable that can be changed concurrently
   //    by calls to the increment and decrement functions by other threads.
   // 
   // aLimit is a lower limit for the decrement. This decrements the index down 
   //    to the lower limit and will not go below it.
   // 
   // aOriginalIndex is the value of the index before the decrement.
   //    It can be null.
   //
   // aNewIndex is the value of the index after the decrement.
   //    It can be null.
   //

   bool tryLFDecrement(
      int* aIndex,
      int  aLimit,
      int* aOriginalIndex,
      int* aNewIndex)
   {
      // Exit if the index is already at the lower limit.
      // This is not necessary, but it saves time.
      if (*aIndex <= aLimit) return false;

      // Locals
      int tCompare, tExchange, tOriginal;
      // Loop until either the current index is at the lower limit
      // or it can be decremented.
      while (true)
      {
         // Get the current index, it will be used in the compare exchange.
         tCompare = *aIndex;
         // Exit if the index was at the lower limit.
         if (tCompare <= aLimit) return false;
         // Decrement
         tExchange = tCompare - 1;
         // This atomically reads the index and compares it to what was 
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. This then returns the
         // original value from before the copmare.
         tOriginal = InterlockedCompareExchange((PLONG)aIndex, tExchange, tCompare);
         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
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
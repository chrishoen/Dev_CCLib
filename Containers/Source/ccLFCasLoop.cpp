/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include "ccLFCasLoop.h"
namespace CC
{
   bool applyLFCasLoopFunction(
      int*  aValue,
      int*  aExchange,
      int*  aOriginal,
      LFCasLoopFunction aFunction)
   {
      // Locals
      int tCompare, tExchange, tOriginal;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare = *aValue;
         tExchange = tCompare;

         // Update the exchange variable with a new value.
         // Exit the loop if unsuccessful.
         if (!aFunction(&tExchange)) return false;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         tOriginal = InterlockedCompareExchange((PLONG)aValue, tExchange, tCompare);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal == tCompare) break;
      }

      // Return the results.

      if (aExchange != NULL)
      {
         *((unsigned*)aExchange) = tExchange;
      }

      if (aOriginal != NULL)
      {
         *((unsigned*)aOriginal) = tOriginal;
      }
      return true;
   }




}//namespace
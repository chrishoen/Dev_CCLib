/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include "ccLFBounded.h"
namespace CC
{
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This attempts to decrement an value, it returns true if successful.
   // It returns false if the value is at a lower limit.
   //
   // It uses an atomic compare and exchange operation to avoid concurrency 
   // violations.
   //
   // aValue is a pointer to an integer variable that can be changed concurrently
   //    by calls to the add functions by other threads.
   // 
   // aLowerBound is a  lower bound for the add.
   // aUpperBound is an upper bound for the add.
   //    If the result of the add goes out of bounds the the add does not occurr
   //    and the operation returns false.
   // 
   // aOriginalValue is the value before the add.
   //    It can be null.
   // aNewValue is the value after the add.
   //    It can be null.
   //
   //       aLowerEndPoint <= X <= aUpperEndPoint

   bool tryLFBoundedAdd(
      int* aValue,
      int  aAdd,
      int  aLowerEndPoint,
      int  aUpperEndPoint,
      int* aOriginalValue,
      int* aNewValue)
   {
      // Locals
      int tCompare, tExchange, tOriginal;

      // Loop until either the value is out of bounds
      // or it can be added to.
      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare = *aValue;

         // Add
         tExchange = tCompare + aAdd;

         // Exit if the new value is out of bounds.
         if (tExchange < aLowerEndPoint) return false;
         if (tExchange > aUpperEndPoint) return false;

         // This atomically reads the value and compares it to what was 
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. This then returns the
         // original value from before the compare.
         tOriginal = InterlockedCompareExchange((PLONG)aValue, tExchange, tCompare);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal == tCompare) break;
      }

      // Store results
      if (aOriginalValue)  *aOriginalValue = tOriginal;
      if (aNewValue)       *aNewValue = tExchange;
      return true;
   }

}//namespace
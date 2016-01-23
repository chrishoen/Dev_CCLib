#ifndef _LFBOUNDED_H_
#define _LFBOUNDED_H_
/*==============================================================================

These support a lock free counter.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This attempts to add to a value, it returns true if successful.
// It returns false if the resulting sum would be out of bounds.
//
// It uses an atomic compare and exchange operation to avoid concurrency 
// violations.
//
// aValue is a pointer to an integer variable that can be changed concurrently
//    by calls to the add function by other threads.
// 
// aLowerEndPoint is a  lower bound for the add.
// aUpperEndPoint is an upper bound for the add.
//    If the result of the add goes outside of the end points then the add
//    does not occur and the operation returns false.
// 
// aOriginalValue is an output that is the value before the add.
// aNewValue      is an output that is the value after the add.
//    They can be null.
//
// Here, atomically:
//       Sum = *aValue + aAdd
//       IF aLowerEndPoint <= Sum <= aUpperEndPoint
//          *aValue = Sum
//          return true
//       ELSE
//          return false
//
//******************************************************************************

   bool tryLFBoundedAdd(
      int* aValue,
      int  aAdd,
      int  aLowerBound,
      int  aUpperBound,
      int* aOriginalValue,
      int* aNewValue);

//******************************************************************************

}//namespace
#endif


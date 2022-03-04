#pragma once

/*==============================================================================
signed and unsigned integer modulo arithmetic.

This provides modulo arithmetic operations on a finite target set of
non-negative integers [0 .. M - 1]. The operations are used to calculate
addresses for circular memory buffers, where the addresses rollover.

The following operations are provided. They are all closed on the given 
non-negative finite target set, they all return integers that are elements
of the set.
   addition
   subtraction
   additive inverse
   multiplication

The modulo operations constructed here always result in non-negative
remainders. Note that the c/c++ modulo operator % can result in negative
remainders. Also note that c/c++ unsigned modulo subtraction is problematic.
The operations provided are intended to overcome these issues.

The target set [0 .. M - 1] and the operations on it form an algebraic ring.
https://en.wikipedia.org/wiki/Ring_(mathematics)
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// These templates provide the ring operations for all of the signed and
// unsigned integer types. All of the operands must be of the same type.

// Map any integer into the target set.
template <typename T> void inline mod_normalize(T aMod, T* aA)
{
   T tTemp = *aA % aMod;
   if (tTemp < 0) tTemp = aMod + tTemp;
   *aA = tTemp;
}

// Addition.
template <typename T> inline T mod_add(T aMod, T aA, T aB)
{
   mod_normalize(aMod, &aA);
   mod_normalize(aMod, &aB);
   return (aA + aB) % aMod;
}

// Subtraction.
template <typename T> T inline mod_subtract(T aMod, T aA, T aB)
{
   mod_normalize(aMod, &aA);
   mod_normalize(aMod, &aB);
   return (aA >= aB) ? aA - aB : aMod - (aB - aA);
}

// Additive inverse.
template <typename T> T inline mod_minus(T aMod, T aA)
{
   mod_normalize(aMod, &aA);
   return aA == 0 ? 0 : aMod - aA;
}

// Multiplication.
template <typename T> T inline mod_mult(T aMod, T aA, T aB)
{
   mod_normalize(aMod, &aA);
   mod_normalize(aMod, &aB);
   return (aA * aB) % aMod;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

#if 0

the first column is integers -15 .. 15
the second column is normalized with mod 4
the second column is the additive inverse mod 4

-15   1   3
-14   2   2
-13   3   1
-12   0   0
-11   1   3
-10   2   2
 -9   3   1
 -8   0   0
 -7   1   3
 -6   2   2
 -5   3   1
 -4   0   0
 -3   1   3
 -2   2   2
 -1   3   1
  0   0   0
  1   1   3
  2   2   2
  3   3   1
  4   0   0
  5   1   3
  6   2   2
  7   3   1
  8   0   0
  9   1   3
 10   2   2
 11   3   1
 12   0   0
 13   1   3
 14   2   2
 15   3   1

#endif
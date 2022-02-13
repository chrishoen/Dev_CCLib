#pragma once
/*==============================================================================

This defines a class template that is used to define classes that are used
to implement counters.

These counters are specialized in that they are based on numbers that are
powers of two. Each counter class is based on integer modulo groups that
use bit shifts to implement division operations and bit masks to implement
modulo operations.

This integer modulo groups are as follows:

Modulo(M) is the group based on the positive integers modulo M.
Modulo(N) is the group based on the positive integers modulo N.

For Modulo(M): 
  The group set is {0,1,...,M-1} also known as [0..M-1].
  The binary operation on two group elements is (A + B) mod M.
  The inverse of a group element A is A==0 ? 0 : M-A.
  The group identity element is 0.

Here M = N*D

M is a power of two. For some LM,         M=2^LM.
N is a power of two. For some LN <= LM,   N=2^LN.
D is a power of two. For some LD = LM-LN, D=2^LD.

So M = N*D 
So (2^LM) = (2^LN)*(2^LD) = (2^LN)*(2^LM)/(2^LN) = (2^LM)
So LM = LN + LD

Each counter class is based on Modulo(M), where the counter is incremented
M times every clock period. Thus a clock that is incremented at 4096hz and 
has a period of one second will have an M of 4096 and the clock values will
vary as [0..4095].

The clock values are elements of Modulo(M) and are represented by ordered pairs
(q,r) of quotients and remainders that result after division by N. 
q = m div N
r = m mod N
m = q*N + r
The remainders r are elements of the group Modulo(N).

This allows construction of counters with subcounters. For example a clock
with a frequency of 4096hz and a period of one second can be represented by
a subcounter with a frequency of 1024hz and a period of one second. The
clock quotents will vary as [0..1023] and the remainders will vary as [0..3].
Or it could have a frequency of 16hz, with the quotients varying as [0..15]
and the remainders varying as [0..255].
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdatomic.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Modulo arithmetic on integers.
      
   // Modulo arithmetic operations.
   int mod_add(int aMod, int aA, int aB);
   int mod_sub(int aMod, int aA, int aB);
   int mod_mult(int aMod, int aA, int aB);
   int mod_ainverse(int aMod, int aA);

   // Modulo arithmetic finite set anchored order relations.
   // less than, less than or equal, greater than or equal, greater than.
   bool mod_order_lt(int aMod, int aAnchor, int aA);
   bool mod_order_lt(int aMod, int aAnchor, int aA, int aB);

   bool mod_order_le(int aMod, int aAnchor, int aA);
   bool mod_order_le(int aMod, int aAnchor, int aA, int aB);

   bool mod_order_ge(int aMod, int aAnchor, int aA);
   bool mod_order_ge(int aMod, int aAnchor, int aA, int aB);

   bool mod_order_gt(int aMod, int aAnchor, int aA);
   bool mod_order_gt(int aMod, int aAnchor, int aA, int aB);


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Modulo arithmetic on atomic integers.


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Modulo arithmetic on integers.

   inline int mod_add(int aMod, int aA, int aB)
   {
      return aA + aB % aMod;
   }

   inline int mod_sub(int aMod, int aA, int aB)
   {
      return aA - aB % aMod;
   }

   inline int mod_mult(int aMod, int aA, int aB)
   {
      return aA * aB % aMod;
   }

   inline int mod_ainverse(int aMod, int aA)
   {
      aA %= aMod;
      return aA == 0 ? 0 : aMod - aA;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Modulo arithmetic finite set anchored order relations.
   // less than, less than or equal, greater than or equal, greater than.

   bool mod_order_lt(int aMod, int aAnchor, int aA)
   {
      return aAnchor - aA;
   }

   bool mod_order_lt(int aMod, int aAnchor, int aA, int aB)
   {
   }

   bool mod_order_le(int aMod, int aAnchor, int aA)
   {
   }

   bool mod_order_le(int aMod, int aAnchor, int aA, int aB)
   {
   }

   bool mod_order_ge(int aMod, int aAnchor, int aA)
   {
   }

   bool mod_order_ge(int aMod, int aAnchor, int aA, int aB)
   {
   }

   bool mod_order_gt(int aMod, int aAnchor, int aA)
   {
   }

   bool mod_order_gt(int aMod, int aAnchor, int aA, int aB)
   {
   }

}//namespace

//******************************************************************************
//******************************************************************************
//******************************************************************************

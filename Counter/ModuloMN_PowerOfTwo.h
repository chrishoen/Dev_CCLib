#ifndef _MODULO_H_
#define _MODULO_H_
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
// M is a power of two. For some LM,       M=2^LM.
// N is a power of two. For some LN <= LM, N=2^LN.
// M is a multiple of N such that M = N*2^(LM-LN)
// NShift = LN, it is used to implement division by N via bit shifting.

template <unsigned M,unsigned N,unsigned NShift>
class ModuloMN_PowerOfTwo
{
public:

   typedef ModuloMN_PowerOfTwo<M, N, NShift> ThisClass;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constants

   static const unsigned cMRemainderMask = M-1;
   static const unsigned cNRemainderMask = N-1;
   static const unsigned cNQuotientShift = NShift;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members
   
   // The results of a division of Z by N are a quotient and a remainder
   // Z = Q*N + R
   // Z is an element of [0..M-1]
   // Q is an element of [0..(M/N)-1]
   // R is an element of [0..N-1]

   unsigned short mQuotient;
   unsigned short mRemainder;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constructors

   // Constructor
   inline ModuloMN_PowerOfTwo()
   {
      mQuotient  = 0;
      mRemainder = 0;
   }

   // Constructor
   inline ModuloMN_PowerOfTwo(unsigned aZ)
   {
      convertFromZPlus(aZ);
   }

   // Constructor
   inline ModuloMN_PowerOfTwo(unsigned aQuotient,unsigned aRemainder)
   {
      mQuotient  = aQuotient;
      mRemainder = aRemainder;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Conversions. Since M and N are powers of 2, division is a shift and 
   // modulo is a mask

   // Convert from a positive integer, (also known as Z superscript +)
   inline void convertFromZPlus(unsigned aZ)
   {
      // Z mod M         ; is an element of [0..M-1]
      unsigned tMRemainder = aZ & cMRemainderMask;
      // (Z mod M) div N ; is an element of [0..(M/N)-1]
      mQuotient  = tMRemainder >> cNQuotientShift;
      // (Z mod M) mod N ; is an element of [0..N-1]
      mRemainder = tMRemainder  & cNRemainderMask;
   }

   // Convert to a positive integer modulo M, is an element of [0..M-1]
   inline unsigned convertToModuloM()
   {
      // Z = Q*N + R
      return mQuotient*N + mRemainder;
   }

   // Is first in [0..N-1]
   inline bool isFirst()
   {
      return mRemainder == 0;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Group operations for Modulo(M) and Modulo(N)

   // This gives the group binary operation for Modulo(M)
   // It also gives the group binary operation for Modulo(N)
   
   inline ThisClass add(ThisClass aThat)
   {
      // Convert to [0..M-1]
      unsigned tMThis = convertToModuloM();
      unsigned tMThat = aThat.convertToModuloM();
      // Sum
      unsigned tMSum = tMThis + tMThat;
      if (tMSum >= M) tMSum = tMSum - M;
      // Return sum
      return ThisClass(tMSum);
   }

   // This gives the group inverse for Modulo(M)
   // It also gives the group inverse for Modulo(N)

   inline ThisClass inverse()
   {
      // Convert to [0..M-1]
      unsigned tMThis = convertToModuloM();
      // [0..M-1] inverse     
      unsigned tMInverse = tMThis == 0 ? 0 : M - tMThis;
      // Return inverse
      return ThisClass(tMInverse);
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // More operations

   // A = A + B
   inline void addTo(ThisClass aThat)
   {
      // Convert to [0..M-1]
      unsigned tMThis = convertToModuloM();
      unsigned tMThat = aThat.convertToModuloM();
      // Sum
      unsigned tMSum = tMThis + tMThat;
      if (tMSum >= M) tMSum = tMSum - M;
      // Return sum
      *this = ThisClass(tMSum);
   }

   // C = A - B
   inline ThisClass subrtract(ThisClass aThat)
   {
      // Convert to [0..M-1]
      unsigned tMThis = convertToModuloM();
      unsigned tMThatInverse = aThat.convertToModuloM().inverse();
      // Difference
      unsigned tMDifference = tMThis + tMThatInverse;
      if (tMDifference >= M) tMDifference = tMDifference - M;
      // Return difference
      return ThisClass(tMDifference);
   }

   // A = A - B
   inline void subrtractFrom(ThisClass aThat)
   {
      // Convert to [0..M-1]
      unsigned tMThis = convertToModuloM();
      unsigned tMThatInverse = aThat.convertToModuloM().inverse();
      // Difference
      unsigned tMDifference = tMThis + tMThatInverse;
      if (tMDifference >= M) tMDifference = tMDifference - M;
      // Return difference
      *this = ThisClass(tMDifference);
   }

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Counters with a clock frequency of 4096hz and a period of one second
//                                                                            // Quotient   Remainder
typedef ModuloMN_PowerOfTwo<4096, 4096,  12>   Counter4096_1hz;        // [0..0]     [0..4095] 
typedef ModuloMN_PowerOfTwo<4096, 2048,  11>   Counter4096_2hz;        // [0..1]     [0..2047] 
typedef ModuloMN_PowerOfTwo<4096, 1024,  10>   Counter4096_4hz;        // [0..3]     [0..1023] 
typedef ModuloMN_PowerOfTwo<4096,  512,   9>   Counter4096_8hz;        // [0..7]     [0..511]  
typedef ModuloMN_PowerOfTwo<4096,  256,   8>   Counter4096_16hz;       // [0..15]    [0..255]  
typedef ModuloMN_PowerOfTwo<4096,  128,   7>   Counter4096_32hz;       // [0..31]    [0..127]  
typedef ModuloMN_PowerOfTwo<4096,   64,   6>   Counter4096_64hz;       // [0..63]    [0..63]   
typedef ModuloMN_PowerOfTwo<4096,   32,   5>   Counter4096_128hz;      // [0..127]   [0..31]   
typedef ModuloMN_PowerOfTwo<4096,   16,   4>   Counter4096_256hz;      // [0..255]   [0..15]   
typedef ModuloMN_PowerOfTwo<4096,    8,   3>   Counter4096_512hz;      // [0..511]   [0..7]    
typedef ModuloMN_PowerOfTwo<4096,    4,   2>   Counter4096_1024hz;     // [0..1023]  [0..3]    
typedef ModuloMN_PowerOfTwo<4096,    2,   1>   Counter4096_2048hz;     // [0..2047]  [0..1]    
typedef ModuloMN_PowerOfTwo<4096,    1,   0>   Counter4096_4096hz;     // [0..4095]  [0..0]    

// Counters with a clock frequency of 32hz and a period of one second
//                                                                            // Quotient   Remainder
typedef ModuloMN_PowerOfTwo<32,      4,   2>   Counter32_8hz;          // [0..7]     [0..3]    

//******************************************************************************


#endif


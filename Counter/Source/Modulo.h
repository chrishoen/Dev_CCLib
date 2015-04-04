#ifndef _QUOTIENTGROUP_H_
#define _QUOTIENTGROUP_H_
/*==============================================================================

This defines a class template that is used to define classes that encapsulate
integer quotient groups.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <int M,int N,int NShift>
class ModuloM_ModuloN_PowerOfTwo
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constants

   static const int cMRemainderMask = M-1;
   static const int cNRemainderMask = N-1;
   static const int cNQuotientShift = NShift;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members

   int      mQuotient;
   int      mRemainder;
   bool     mFrequencyFlag;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constructors

   // Constructor
   ModuloM_ModuloN_PowerOfTwo()
   {
      mQuotient      = 0;
      mRemainder     = 0;
      mFrequencyFlag = false;
   }

   // Constructor
   ModuloM_ModuloN_PowerOfTwo(int aZ)
   {
      convertFromZ(aZ);
   }

   // Constructor
   ModuloM_ModuloN_PowerOfTwo(int aMRemainder,int aNRemainder)
   {
      mMRemainder = aMRemainder;
      mNRemainder = aNRemainder;
      mFrequencyFlag = mRemainder==0;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Conversions

   // Convert from an integer
   inline void convertFromZ(int aZ)
   {
      int tMRemainder = aZ & cMRemainderMask;
      mQuotient  = tMRemainder >> cNQuotientShift;
      mRemainder = tMRemainder  & cNRemainderMask;
      mFrequencyFlag = mRemainder==0;
   }

   // Convert to an integer
   inline int convertToZ()
   {
      return mNQuotient*N + mNRemainder;
   }

};


//******************************************************************************
//******************************************************************************
//******************************************************************************
//      Modulo Modulo Counter                                      // Quotient   Remainder
typedef ModuloM_ModuloN_PowerOfTwo<4096, 4096,  12>   Counter4096_1hz;        // [0..0]     [0..4095] 
typedef ModuloM_ModuloN_PowerOfTwo<4096, 2048,  11>   Counter4096_2hz;        // [0..1]     [0..2047] 
typedef ModuloM_ModuloN_PowerOfTwo<4096, 1024,  10>   Counter4096_4hz;        // [0..3]     [0..1023] 
typedef ModuloM_ModuloN_PowerOfTwo<4096,  512,   9>   Counter4096_8hz;        // [0..7]     [0..511]  
typedef ModuloM_ModuloN_PowerOfTwo<4096,  256,   8>   Counter4096_16hz;       // [0..15]    [0..255]  
typedef ModuloM_ModuloN_PowerOfTwo<4096,  128,   7>   Counter4096_32hz;       // [0..31]    [0..127]  
typedef ModuloM_ModuloN_PowerOfTwo<4096,   64,   6>   Counter4096_64hz;       // [0..63]    [0..63]   
typedef ModuloM_ModuloN_PowerOfTwo<4096,   32,   5>   Counter4096_128hz;      // [0..127]   [0..31]   
typedef ModuloM_ModuloN_PowerOfTwo<4096,   16,   4>   Counter4096_256hz;      // [0..255]   [0..15]   
typedef ModuloM_ModuloN_PowerOfTwo<4096,    8,   3>   Counter4096_512hz;      // [0..511]   [0..7]    
typedef ModuloM_ModuloN_PowerOfTwo<4096,    4,   2>   Counter4096_1024hz;     // [0..1023]  [0..3]    
typedef ModuloM_ModuloN_PowerOfTwo<4096,    2,   1>   Counter4096_2048hz;     // [0..2047]  [0..1]    
typedef ModuloM_ModuloN_PowerOfTwo<4096,    1,   0>   Counter4096_4096hz;     // [0..4095]  [0..0]    

//******************************************************************************


#endif


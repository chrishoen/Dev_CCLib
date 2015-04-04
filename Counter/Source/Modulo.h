#ifndef _QUOTIENTGROUP_H_
#define _QUOTIENTGROUP_H_
/*==============================================================================

This defines a class template that is used to define classes that encapsulate
integer quotient groups.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <int N>
class Mod4096ModN
{
public:
   //---------------------------------------------------------------------------
   // Members

   static const int c4096RemainderMask = 4095;
   static int mQuotientShift;
   static int mRemainderMask;

   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   Mod4096ModN()
   {
      mQuotient      = 0;
      mRemainder     = 0;
      mFrequencyFlag = false;
   }


   void convertFromZ(int aZ)
   {
      int t4096Remainder = aZ & c4096RemainderMask;
      mQuotient  = t4096Remainder >> mQuotientShift;
      mRemainder = t4096Remainder  & mRemainderMask;

      mFrequencyFlag = mRemainder==0;

   }

   //---------------------------------------------------------------------------
   // Members

   int      mQuotient;
   int      mRemainder;
   bool     mFrequencyFlag;
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
typedef Mod4096ModN<4096> Counter4096_1hz;
typedef Mod4096ModN<2048> Counter4096_2hz;
typedef Mod4096ModN<1024> Counter4096_4hz;
typedef Mod4096ModN<512>  Counter4096_8hz;
typedef Mod4096ModN<256>  Counter4096_16hz;
typedef Mod4096ModN<128>  Counter4096_32hz;
typedef Mod4096ModN<64>   Counter4096_64hz;
typedef Mod4096ModN<32>   Counter4096_128hz;
typedef Mod4096ModN<16>   Counter4096_256hz;
typedef Mod4096ModN<8>    Counter4096_512hz;
typedef Mod4096ModN<4>    Counter4096_1024hz;
typedef Mod4096ModN<2>    Counter4096_2048hz;
typedef Mod4096ModN<1>    Counter4096_4096hz;

//******************************************************************************


#endif


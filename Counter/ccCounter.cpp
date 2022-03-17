//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"


#include "ccCounter.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

CounterN::CounterN()
{
   mDivisor = 1;
   reset();
}
CounterN::CounterN(int aDivisor)
{
   mDivisor = aDivisor;
   reset();
}
void CounterN::reset()
{
   mValue = 0;
   mQuotient = 0;
   mRemainder = 0;
}
void CounterN::initialize(int aDivisor)
{
   mDivisor = aDivisor;
   reset();
}

void CounterN::set(int aValue)
{
   mValue = aValue;
   mQuotient = mValue / mDivisor;
   mRemainder = mValue % mDivisor;
}
void CounterN::increment()
{
   mValue++;
   mQuotient = mValue / mDivisor;
   mRemainder = mValue % mDivisor;
}
bool CounterN::decrement()
{
   if (--mValue < 0) mValue = 0;
   mQuotient = mValue / mDivisor;
   mRemainder = mValue % mDivisor;
   return mValue == 0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
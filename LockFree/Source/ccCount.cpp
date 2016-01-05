/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include "ccCount.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

Count::Count()
{
   // All null
   mCount    = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Count::initialize(LONG aMaxCount)
{
   mMaxCount = aMaxCount;
   mCount    = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

bool Count::increment (LONG* aCount)
{
   // Guard
   if (mCount >= mMaxCount) return false;

   LONG tOriginal = InterlockedIncrement(&mCount);

   if (tOriginal >= mMaxCount)
   {
      InterlockedDecrement(&mCount);
      return false;
   }

   *aCount = tOriginal + 1;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

bool Count::decrement (LONG* aCount)
{
   // Guard
   if (mCount < 0) return false;

   LONG tOriginal = InterlockedDecrement(&mCount);

   if (tOriginal <= 0)
   {
      InterlockedIncrement(&mCount);
      return false;
   }

   *aCount = tOriginal - 1;
   return true;
}

}//namespace
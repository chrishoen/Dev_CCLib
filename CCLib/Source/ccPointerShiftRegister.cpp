/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include "cc_functions.h"

#include <math.h>
#include <string.h>

#include "ccPointerShiftRegister.h"

namespace CC
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void PointerShiftRegister::initialize(int aSize)
{
   if (aSize > MaxSize) aSize = MaxSize;
   if (aSize < 0) aSize=0;
   mSize=aSize;
   reset();
}

//******************************************************************************

void PointerShiftRegister::reset() 
{
   mX=0;
   mCount=0;
   mIndex=mSize-1;
   mK = 0;
#if 0
   for(int i=0;i<mSize;i++)
   {
      mArray[i]=0.0;
   }
#endif
   mValid=false;
}

//******************************************************************************

void PointerShiftRegister::shiftRight(void* aX)
{
   // Adjust index to the right
   mIndex = cc_index_add(mIndex, 1, mSize);

   // Add new value to array
   mX=aX;
   mArray[mIndex]=aX;

   // Calculate number of elements
   if (mCount==mSize)
   {
      mValid=true;
   }
   else
   {
      mCount++;
      mValid=false;
   }
   
   // Update
   mK++;
}

//******************************************************************************

void PointerShiftRegister::setLeft(void* aX)
{
   // Set array left end value
   mArray[mIndex]=aX;
}

//******************************************************************************

void* PointerShiftRegister::get(int aOffset)
{
   // Guard
   if (!mValid) return 0;

   // Get index
   int tGetIndex = cc_index_sub(mIndex, aOffset, mSize);

   // Return array value at index
   return mArray[tGetIndex];
}

//******************************************************************************

void* PointerShiftRegister::getLeft()
{
   // Guard
   if (!mValid) return 0;

   // Return array value at index
   return mArray[mIndex];
}

//******************************************************************************

void* PointerShiftRegister::getRight()
{
   // Guard
   if (!mValid) return 0;

   // Get index of right end
   int tGetIndex = cc_index_sub(mIndex, (mSize - 1), mSize);

   // Return array value at index
   return mArray[tGetIndex];
}


}//namespace


/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include "cc_functions.h"
#include "ccDefs.h"

#include <math.h>
#include <string.h>

#include "ccShiftRegister.h"

namespace CC
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void ShiftRegister::initialize(int aSize)
{
   if (aSize > MaxShiftRegisterSize) aSize = MaxShiftRegisterSize;
   if (aSize < 0) aSize=0;
   mSize=aSize;
   reset();
}

//******************************************************************************

void ShiftRegister::reset() 
{
   mX=0.0;
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

void ShiftRegister::shiftRight(double aX)
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

void ShiftRegister::setLeft(double aX)
{
   // Set array left end value
   mArray[mIndex]=aX;
}

//******************************************************************************

double ShiftRegister::get(int aOffset)
{
   // Guard
   if (!mValid) return 0.0;

   // Get index
   int tGetIndex = cc_index_sub(mIndex, aOffset, mSize);

   // Return array value at index
   return mArray[tGetIndex];
}

//******************************************************************************

double ShiftRegister::getLeft()
{
   // Guard
   if (!mValid) return 0.0;

   // Return array value at index
   return mArray[mIndex];
}

//******************************************************************************

double ShiftRegister::getRight()
{
   // Guard
   if (!mValid) return 0.0;

   // Get index of right end
   int tGetIndex = cc_index_sub(mIndex, (mSize - 1), mSize);

   // Return array value at index
   return mArray[tGetIndex];
}


//******************************************************************************

void ShiftRegister::show()
{
   printf("ShiftRegister:                   %3d %8.3f $$",mIndex,mX);
   for (int j=0;j<mSize;j++)
   {
      printf("%8.3f ", get(j));
   }
   printf("\n");
}

}//namespace


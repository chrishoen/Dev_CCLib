#ifndef _CCSHIFTREGISTER_H_
#define _CCSHIFTREGISTER_H_
/*==============================================================================

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "cc_functions.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Shift register of Elements, it shifts to the right, the left end element
// is the most recent and the right end element is the latest.

template <class Element>
class ShiftRegister
{
public:
   //---------------------------------------------------------------------------
   // Members

   enum { MaxFilterSize = 200 };
   // Valid flag
   bool mValidFlag;
   // Array size
   int mSize;
   // Index of left end
   int mIndex;
   // Number of occupied elements
   int mCount;
   // Number of shifts
   int mK;
   // Input value
   Element mX;


   // Value array
   enum { MaxShiftRegisterSize = 1000 };
   Element mArray[MaxShiftRegisterSize];

   //---------------------------------------------------------------------------
   // Initialize

   void initialize(int aSize)
   {
      if (aSize > MaxShiftRegisterSize) aSize = MaxShiftRegisterSize;
      if (aSize < 0) aSize=0;
      mSize=aSize;
      reset();
   }

   //---------------------------------------------------------------------------
   // Reset

   void reset() 
   {
      mX=0.0;
      mCount=0;
      mIndex=mSize-1;
      mK = 0;
      mValidFlag=false;
   }

   //******************************************************************************

   void shiftRight(Element aX)
   {
      // Adjust index to the right
      mIndex = cc_index_add(mIndex, 1, mSize);

      // Add new value to array
      mX=aX;
      mArray[mIndex]=aX;

      // Calculate number of elements
      if (mCount==mSize)
      {
         mValidFlag=true;
      }
      else
      {
         mCount++;
         mValidFlag=false;
      }
   
      // Update
      mK++;
   }

   //******************************************************************************

   void setLeft(Element aX)
   {
      // Set array left end value
      mArray[mIndex]=aX;
   }

   //******************************************************************************

   Element get(int aOffset)
   {
      // Guard
      if (!mValidFlag) return 0.0;

      // Get index
      int tGetIndex = cc_index_sub(mIndex, aOffset, mSize);

      // Return array value at index
      return mArray[tGetIndex];
   }

   //******************************************************************************

   Element getLeft()
   {
      // Guard
      if (!mValidFlag) return 0.0;

      // Return array value at index
      return mArray[mIndex];
   }

   //******************************************************************************

   Element getRight()
   {
      // Guard
      if (!mValidFlag) return 0.0;

      // Get index of right end
      int tGetIndex = cc_index_sub(mIndex, (mSize - 1), mSize);

      // Return array value at index
      return mArray[tGetIndex];
   }



   // Members

};

}//namespace
#endif


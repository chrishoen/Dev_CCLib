#ifndef _CCSHIFTREGISTER_H_
#define _CCSHIFTREGISTER_H_
/*==============================================================================

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
   enum { MaxFilterSize = 200 };

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Shift register of doubles, it shifts to the right, the left end element
// is the most recent and the right end element is the latest.

class ShiftRegister
{
public:
   // Initialize
   void initialize(int aSize);
   void reset(); 
   void show();
   // Valid
   bool mValid;

   // Shift right and put input value at the left end.
   void shiftRight(double aX);

   // Set the left end value
   void setLeft(double aX);

   // Input value
   double mX;

   // Get value
   double get(int    aIndex);
   double getLeft();
   double getRight();

   // Members

   // Array size
   int mSize;
   // Index of left end
   int mIndex;
   // Number of occupied elements
   int mCount;
   // Number of shifts
   int mK;

   // Value array
   enum { MaxShiftRegisterSize = 1000 };
   double mArray[MaxShiftRegisterSize];
};

}//namespace
#endif


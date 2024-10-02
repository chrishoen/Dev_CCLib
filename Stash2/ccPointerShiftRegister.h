#ifndef _CCPOINTERSHIFTREGISTER_H_
#define _CCPOINTERSHIFTREGISTER_H_
/*==============================================================================

Shift register of void* pointers

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
// Shift register of pointers, it shifts to the right, the left end element
// is the most recent and the right end element is the oldest.

class PointerShiftRegister
{
public:
   //--------------------------------------------------------------------------
   // Initialize

   void initialize(int aSize);
   void reset(); 
   // Valid
   bool mValid;

   //--------------------------------------------------------------------------
   // Shift right and put input value at the left end.
   void shiftRight(void* aX);

   // Set the left end value
   void setLeft(void* aX);

   // Input value
   void* mX;

   //--------------------------------------------------------------------------
   // Get value
   void* get(int aIndex);
   void* getLeft();
   void* getRight();

   //--------------------------------------------------------------------------
   // Members

   // Array size
   int mSize;
   // Index of left end
   int mIndex;
   // Number of occupied elements
   int mCount;
   // Number of shifts
   int mK;

   //--------------------------------------------------------------------------
   // Value array
   enum { MaxSize = 1000 };
   void* mArray[MaxSize];
};


}//namespace
#endif


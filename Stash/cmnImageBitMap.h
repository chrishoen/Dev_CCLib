#pragma once
/*==============================================================================
Image bit map class.
==============================================================================*/

#include "risByteContent.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encalsulates a bit map that stores an image single color
// rectangular array in a packed byte array. Each pixel is packed into
// one bit of a single byte in the byte array. Each bit represents a pixel
// being on or off.
//
// This class inherits from byte content so that it can be included in
// byte content messages.

class ImageBitMapMemoryControl;

class ImageBitMap : public Ris::ByteContent
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Memory management control pointer.
   ImageBitMapMemoryControl* mMemoryControl;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Number of rows and columns in the correspondng rectangular array.
   int mRows;
   int mCols;

   // Number of bytes in the array.
   int mNumBytes;

   // Image color.
   int mColor[3];

   // XY offsets.
   int mOffsetX;
   int mOffsetY;

   // Array of bytes, this is dynamically allocated memory.
   // Size is rows*cols/8.
   unsigned char* mBytes;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastructure.

   // Initialize variables. Do not allocate memory.
   ImageBitMap();

   // Initialize variables, allocate memory, and increment the resource
   // counter.
   ImageBitMap(int aRows,int aCols);

   // Decrement the resource counter. If it is zero then deallocate memory.
  ~ImageBitMap();
  void resetVariables();

   // Initialize variables, allocate memory, and increment the resource
   // counter.
   void initialize(int aRows,int aCols);

   // If memory was allocated then deallocate it.
   void finalize();

   // Increment the resource counter.
   void incrementResourceCount();

   // Decrement the resource counter. If it is zero then deallocate memory.
   void decrementResourceCount();

   // Return true if memory has been allocated.
   bool isValid();
   // Return resource count. If memory has not been allocated return -1.
   int  getResourceCount();

   // Copy constructor and assignment operator. Copy variables and data
   // pointers. Do not copy data. This makes a copy of a variable that
   // points to the same allocated memory
   ImageBitMap(const ImageBitMap& aRhs); 
   ImageBitMap& operator= (const ImageBitMap& aRhs); 

   // Clone a bitmap into another bitmap.
   void cloneTo(ImageBitMap& aDestin); 

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Set and get pixel values. These access individual bits within the byte
   // array.
   void set(int aRow,int aCol,bool aBit);
   bool get(int aRow,int aCol);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show(int aPrintFilter,char* aLabel);
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Set all bits to true.
   void setAllOnes();
   // Set all bits to false.
   void setAllZeroes();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Copy to/from a byte buffer.
   void copyToFrom (Ris::ByteBuffer* aBuffer);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace





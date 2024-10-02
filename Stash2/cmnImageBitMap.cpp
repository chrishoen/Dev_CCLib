/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"
#include <atomic>

#include "cmnImageBitMap.h"

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory control. An instance of this is allocated on the heap when 
// data memory is allocated. It contains a resource count. It used so that
// separate instances of the main class can point to the same allocated data
// memory.

class ImageBitMapMemoryControl
{
public:

   // Resource count.
   std::atomic<int> mResourceCount;
   // Constructor.
   ImageBitMapMemoryControl()
   {
      mResourceCount = 0;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

ImageBitMap::ImageBitMap()
{
   mBytes = 0;
   mMemoryControl = 0;
   resetVariables();
}

ImageBitMap::ImageBitMap(int aRows,int aCols)
{
   mBytes = 0;
   mMemoryControl = 0;
   initialize(aRows,aCols);
}

void ImageBitMap::resetVariables()
{
   mRows = 0;
   mCols = 0;
   mNumBytes = 0;
   mColor[0] = 0;
   mColor[1] = 0;
   mColor[2] = 0;
   mOffsetX = 0;
   mOffsetY = 0;
}

ImageBitMap::~ImageBitMap()
{
   // If memory has already been allocated then deallocate it.
   decrementResourceCount();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void ImageBitMap::initialize(int aRows,int aCols)
{
   // If memory has already been allocated then deallocate it.
   decrementResourceCount();

   // Reset member variables to defaults.
   resetVariables();

   // Store variables.
   mRows = aRows;
   mCols = aCols;

   // Number of bits.
   int tNumBits = mRows*mCols;

   // Number of bytes.
   if (tNumBits % 8 == 0)
   {
      mNumBytes = tNumBits/8;
   }
   else
   {
      mNumBytes = (tNumBits + 8)/8;
   }

   // Allocate memory.
   if (mMemoryControl == 0)
   {
      mBytes = new unsigned char[mNumBytes];
      mMemoryControl = new ImageBitMapMemoryControl;
   }

   // Set all bits false;
   setAllZeroes();

   // Increment the resource counter.
   incrementResourceCount();
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void ImageBitMap::finalize()
{
   // If memory was allocated then deallocate it.
   if (mMemoryControl)
   {
      delete mBytes;
      delete mMemoryControl;
      mBytes = 0;
      mMemoryControl=0;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Resource count management.

void ImageBitMap::incrementResourceCount()
{
   // Guard.
   if (mMemoryControl==0) return;
   // Increment the resource count.
   mMemoryControl->mResourceCount++;
}

void ImageBitMap::decrementResourceCount()
{
   // Guard.
   if (mMemoryControl==0) return;
   // If there is no memory allocated then return.
   if (mMemoryControl->mResourceCount==0) return;

   // Decrement the resource count. If it is zero then deallocate memory.
   if (--mMemoryControl->mResourceCount == 0)
   {
      finalize();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory status.

// Return true if memory has been allocated.
bool ImageBitMap::isValid()
{
   return mMemoryControl!=0;
}

// Return resource count. If memory has not been allocated return -1.
int  ImageBitMap::getResourceCount()
{
   if (mMemoryControl==0) return -1;
   return mMemoryControl->mResourceCount;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy constructor and assignment operator. Copy variables and data
// pointers. Do not copy data. This makes a copy of a history variable 
// that points to the same allocated memory

ImageBitMap::ImageBitMap(const ImageBitMap& aRhs)
{
   memcpy(this,&aRhs,sizeof(*this));
   incrementResourceCount();
}

ImageBitMap& ImageBitMap::operator= (const ImageBitMap& aRhs)
{
   decrementResourceCount();
   memcpy(this,&aRhs,sizeof(*this));
   incrementResourceCount();
   return *this;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Clone a bitmap into another bitmap.

void ImageBitMap::cloneTo(ImageBitMap& aDestin)
{
   aDestin.initialize(this->mRows,this->mCols);
   memcpy(aDestin.mBytes,this->mBytes,this->mNumBytes);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set and get pixel values. These access individual bits within the byte
// array.

void ImageBitMap::set(int aRow, int aCol, bool aBit)
{
   // Index arithmetic.
   int tIndex = aRow*mCols + aCol;
   int tByte = tIndex/8;
   int tBit  = tIndex%8;
   // Bit mask.
   unsigned char tMask = 1 << tBit;

   // Set bit in byte array.
   if (aBit)
   {
      mBytes[tByte] |= tMask;
   }
   else
   {
      mBytes[tByte] &= ~tMask;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set and get pixel values. These access individual bits within the byte
// array.

bool ImageBitMap::get(int aRow, int aCol)
{
   // Index arithmetic.
   int tIndex = aRow*mCols + aCol;
   int tByte = tIndex/8;
   int tBit  = tIndex%8;
   // Bit mask.
   unsigned char tMask = 1 << tBit;

   return (mBytes[tByte] & tMask)!=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ImageBitMap::setAllOnes()
{
   for (int i = 0; i < mRows*mCols / 8; i++)
   {
      mBytes[i]=0xff;
   }
}

void ImageBitMap::setAllZeroes()
{
   for (int i = 0; i < mRows*mCols / 8; i++)
   {
      mBytes[i]=0x00;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ImageBitMap::show(int aPF, char* aLabel)
{
   Prn::print(aPF, "%12s %3d %3d %3d %3d\n",
      aLabel, 
      getResourceCount(),
      mRows, 
      mCols, 
      mNumBytes);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy to/from a byte buffer.

void ImageBitMap::copyToFrom(Ris::ByteBuffer* aBuffer)
{
   aBuffer->copy( &mRows );
   aBuffer->copy( &mCols );
   aBuffer->copy( &mNumBytes );

   if (aBuffer->isCopyFrom())
   {
      initialize(mRows,mCols);
   }

   aBuffer->copy( &mColor[0] );
   aBuffer->copy( &mColor[1] );
   aBuffer->copy( &mColor[2] );

   aBuffer->copy( &mOffsetX );
   aBuffer->copy( &mOffsetY );

   aBuffer->copyBlock( mBytes, mNumBytes );
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


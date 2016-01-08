#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "prnPrint.h"

#include "LFQueue.h"

namespace LFQueue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Regionals

   static const LONG cCapacity = 4;
   static const LONG cCapacityMask = 0x03;

   static int mArray[1000];
   
   int mWriteIndex = 0;
   int mReadIndex = 0;
   int mReadAvailable = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize()
   {
      mWriteIndex = 0;
      mReadAvailable = 0;
      mReadIndex = 0;

      for (int i=0;i<1000;i++)
      {
         mArray[i]=0;
      }
   }

   int available() {return mWriteIndex;}

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryStartWrite(int* aWriteIndex)
   {
      if (mReadAvailable==cCapacity) return false;

      mReadAvailable++;
      *aWriteIndex = mWriteIndex;
      if (++mWriteIndex == cCapacity) mWriteIndex=0;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryStartRead(int* aReadIndex)
   {
      if (mReadAvailable == 0) return false;

      int tReadIndex = mWriteIndex - mReadAvailable;
      if (tReadIndex < 0) tReadIndex = tReadIndex + cCapacity;
      mReadAvailable--;
      // Store result
      *aReadIndex = tReadIndex;
      mReadIndex = tReadIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void write(int aWriteIndex,int  aValue)
   {
      mArray[aWriteIndex] = aValue;
   }

   void read  (int aReadIndex,int* aValue)
   {
      *aValue = mArray[aReadIndex];
   }


}
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

   static const int cCapacity = 4;

   static int mBuffer[cCapacity];

   LONG mAvailable  = 0;
   LONG mWriteCount = 0;
   LONG mReadCount  = 0;

   bool increment (LONG* aCount);
   bool decrement (LONG* aCount);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize()
   {
      mAvailable  = 0;
      mWriteCount = 0;
      mReadCount  = 0;

      for (int i=0;i<cCapacity;i++)
      {
         mBuffer[i]=0;
      }
   }

   LONG available() {return mAvailable;}

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool increment (LONG* aCount)
   {
      // Guard
      if (*aCount >= cCapacity) return false;

      LONG tOriginal = InterlockedExchangeAdd(aCount,1);

      if (tOriginal >= cCapacity)
      {
         InterlockedDecrement(aCount);
         return false;
      }

      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool decrement (LONG* aCount)
   {
      // Guard
      if (*aCount < 0) return false;

      LONG tOriginal = InterlockedExchangeAdd(aCount,-1);

      if (tOriginal <= 0)
      {
         InterlockedIncrement(aCount);
         return false;
      }

      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool write(int aValue)
   {
      if (!increment(&mAvailable)) return false;

      ULONG tWriteCount = InterlockedExchangeAdd(&mWriteCount,1);
      ULONG tWriteIndex = tWriteCount % cCapacity;
      mBuffer[tWriteIndex] = aValue;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool read(int* aValue)
   {
      if (!decrement(&mAvailable)) return false;

      ULONG tReadCount = InterlockedExchangeAdd(&mReadCount,1);
      ULONG tReadIndex = tReadCount % cCapacity;
      *aValue = mBuffer[tReadIndex];
      return true;
   }

}
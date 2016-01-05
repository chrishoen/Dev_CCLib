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
   LONGLONG mWriteCount = 0;
   LONGLONG mReadCount  = 0;

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

   bool getWriteIndex(int* aWriteIndex)
   {
      if (!increment(&mAvailable)) return false;

      LONGLONG tWriteCount = InterlockedExchangeAdd64(&mWriteCount,1);
      LONG     tWriteIndex = tWriteCount % cCapacity;
      *aWriteIndex = tWriteIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool getReadIndex(int* aReadIndex)
   {
      if (!decrement(&mAvailable)) return false;

      LONGLONG tReadCount = InterlockedExchangeAdd64(&mReadCount,1);
      LONG     tReadIndex = tReadCount % cCapacity;
      *aReadIndex = tReadIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool write(int aValue)
   {
      int tWriteIndex=0;
      if (!getWriteIndex(&tWriteIndex)) return false;

      mBuffer[tWriteIndex] = aValue;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool read(int* aValue)
   {
      int tReadIndex=0;
      if (!getReadIndex(&tReadIndex)) return false;

      *aValue = mBuffer[tReadIndex];
      return true;
   }

}
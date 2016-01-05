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
   static const int cCapacityMask = 0x03;

   static int mBuffer[cCapacity];
   static bool mValidFlag[cCapacity];

   LONG mReadAvailable  = 0;
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
      mReadAvailable  = 0;
      mWriteCount = 0;
      mReadCount  = 0;

      for (int i=0;i<cCapacity;i++)
      {
         mBuffer[i]=0;
         mValidFlag[i]=false;
      }
   }

   LONG available() {return mReadAvailable;}

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

   bool acquireWriteIndex(int* aWriteIndex)
   {
      if (mReadAvailable >= cCapacity) return false;

      LONG tOriginal = InterlockedExchangeAdd(&mReadAvailable,1);

      if (tOriginal >= cCapacity)
      {
         InterlockedExchangeAdd(&mReadAvailable,-1);
         return false;
      }

      LONGLONG tWriteCount = InterlockedExchangeAdd64(&mWriteCount,1);
      LONG     tWriteIndex = tWriteCount % cCapacity;

      if (mValidFlag[tWriteIndex])
      {
         InterlockedExchangeAdd(&mReadAvailable, -1);
         InterlockedExchangeAdd64(&mWriteCount, -1);
         return false;
      }
      mValidFlag[tWriteIndex] = false;

      *aWriteIndex = tWriteIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void releaseWriteIndex(int aWriteIndex)
   {
      mValidFlag[aWriteIndex]=true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool acquireReadIndex(int* aReadIndex)
   {
      if (mReadAvailable <= 0) return false;

      LONG tOriginal = InterlockedExchangeAdd(&mReadAvailable,-1);

      if (tOriginal <= 0)
      {
         InterlockedExchangeAdd(&mReadAvailable,1);
         return false;
      }

      LONG tReadIndex = mReadCount % cCapacity;
      mReadCount++;

      if (!mValidFlag[tReadIndex])
      {
         InterlockedExchangeAdd(&mReadAvailable,1);
         mReadCount--;
         return false;
      }

      *aReadIndex = tReadIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void releaseReadIndex(int aReadIndex)
   {
      mValidFlag[aReadIndex]=false;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool write(int aValue)
   {
      int tWriteIndex=0;
      if (!acquireWriteIndex(&tWriteIndex)) return false;

      mBuffer[tWriteIndex] = aValue;

      releaseWriteIndex(tWriteIndex);

      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool read(int* aValue)
   {
      int tReadIndex=0;
      if (!acquireReadIndex(&tReadIndex)) return false;

      *aValue = mBuffer[tReadIndex];

      releaseReadIndex(tReadIndex);

      return true;
   }

}
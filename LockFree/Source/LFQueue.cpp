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

   static int mBuffer[cCapacity];
   
   static LONG mReadInProgress[cCapacity];

   LONG mReadAvailable  = 0;
   LONGLONG mWriteCount = 0;
   LONGLONG mReadCount  = 0;

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
         mReadInProgress[i]=FALSE;
      }
   }

   LONG available() {return mReadAvailable;}


   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool acquireWriteIndex(int* aWriteIndex)
   {
      // Guard for full, number of available reads is at capacity
      if (mReadAvailable >= cCapacity) return false;

      // Increment the number of reads that are available
      LONG tOriginal = InterlockedExchangeAdd(&mReadAvailable,1);

      // Guard for full again
      if (tOriginal >= cCapacity)
      {
         // Undo the increment and exit
         InterlockedExchangeAdd(&mReadAvailable,-1);
         return false;
      }

      // Increment the write count and get the write index from it
      LONGLONG tWriteCount = InterlockedExchangeAdd64(&mWriteCount,1);
      LONG     tWriteIndex = tWriteCount % cCapacity;

      // Store result
      *aWriteIndex = tWriteIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void releaseWriteIndex(int aWriteIndex)
   {
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool acquireReadIndex(int* aReadIndex)
   {
      // Guard for empty, number of available reads is at zero
      if (mReadAvailable <= 0) return false;

      // Increment the read count and get the read index from it
      // This doesn't need interlocks because there is only one reader.
      LONGLONG tReadCount = mReadCount++;
      LONG     tReadIndex = tReadCount % cCapacity;

      // Store result
      *aReadIndex = tReadIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void releaseReadIndex(int aReadIndex)
   {
      // Decrement the number of reads that are available
      InterlockedDecrement(&mReadAvailable);
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
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


   static const int cState_WriteStarted  = 1;
   static const int cState_WriteFinished = 2;
   static const int cState_ReadStarted   = 3;
   static const int cState_ReadFinished  = 4;


   static int mState[cCapacity];

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
         mState[i]=cState_ReadFinished;
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

      // Test state to see if there was a read acquire but not a 
      // corresponding read release
      if (mState[tWriteIndex] != cState_ReadFinished)
      {
         // Undo the increments and exit
         InterlockedExchangeAdd(&mReadAvailable, -1);
         InterlockedExchangeAdd64(&mWriteCount, -1);
         return false;
      }
      // Set state
      mState[tWriteIndex] = cState_WriteStarted;

      // Store result
      *aWriteIndex = tWriteIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void releaseWriteIndex(int aWriteIndex)
   {
      // Set state
      mState[aWriteIndex] = cState_WriteFinished;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool acquireReadIndex(int* aReadIndex)
   {
      // Guard for empty, number of available reads is at zero
      if (mReadAvailable <= 0) return false;

      // Decrement the number of reads that are available
      LONG tOriginal = InterlockedExchangeAdd(&mReadAvailable,-1);

      // Guard for empty again
      if (tOriginal <= 0)
      {
         // Undo decrement and exit
         InterlockedExchangeAdd(&mReadAvailable,1);
         return false;
      }

      // Increment the read count and get the read index from it
      // This doesn't need interlocks because there is only one reader.
      LONGLONG tReadCount = mReadCount++;
      LONG     tReadIndex = tReadCount % cCapacity;

      // Test state to see if there was a write acquire but not a 
      // corresponding write release
      if (mState[tReadIndex] != cState_WriteFinished)
      {
         InterlockedExchangeAdd(&mReadAvailable,1);
         mReadCount--;
         return false;
      }
      // Set state
      mState[tReadIndex] = cState_ReadStarted;

      // Store result
      *aReadIndex = tReadIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void releaseReadIndex(int aReadIndex)
   {
      // Set state
      mState[aReadIndex] = cState_ReadFinished;
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
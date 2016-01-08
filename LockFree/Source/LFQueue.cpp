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
   int mReadAvailable = 0;


   typedef union
   {
       struct    
       { 
         signed short mWriteIndex;  
         signed short mReadAvailable;  
       } Parms;
       signed mPacked;
   } LFQueueParms;

   LFQueueParms mParms;


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize()
   {
      mParms.mPacked=0;

      for (int i=0;i<1000;i++)
      {
         mArray[i]=0;
      }
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryStartWrite(int* aWriteIndex)
   {
      // Locals
      LFQueueParms tCompare, tExchange, tOriginal;
      int tWriteIndex;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare = mParms;
         // Exit if the queue is full
         if (tCompare.Parms.mReadAvailable==cCapacity) return false;

         // Update queue parameters for the exchange variable
         tExchange = tCompare;
         tExchange.Parms.mReadAvailable++;
         tWriteIndex = tExchange.Parms.mWriteIndex;
         if (++tExchange.Parms.mWriteIndex == cCapacity) tExchange.Parms.mWriteIndex=0;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         tOriginal.mPacked = InterlockedCompareExchange((PLONG)(&mParms.mPacked), tExchange.mPacked, tCompare.mPacked);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal.mPacked == tCompare.mPacked) break;
      }

      // Store results
      *aWriteIndex = tWriteIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void finishWrite()
   {
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   bool tryStartRead(int* aReadIndex)
   {
      LFQueueParms tParms;
      tParms.mPacked = InterlockedAdd((PLONG)(&mParms.mPacked),0);

      if (tParms.Parms.mReadAvailable == 0) return false;

      int tReadIndex = tParms.Parms.mWriteIndex - tParms.Parms.mReadAvailable;
      if (tReadIndex < 0) tReadIndex = tReadIndex + cCapacity;
      // Store result
      *aReadIndex = tReadIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void finishRead()
   {
      // Locals
      LFQueueParms tCompare, tExchange, tOriginal;

      while (true)
      {
         // Get the current value, it will be used in the compare exchange.
         tCompare = mParms;

         // Update queue parameters for the exchange variable
         tExchange = tCompare;
         tExchange.Parms.mReadAvailable--;

         // This call atomically reads the value and compares it to what was
         // previously read at the first line of this loop. If they are the
         // same then this was not concurrently preempted and so the original
         // value is replaced with the exchange value. It returns the
         // original value from before the compare.
         tOriginal.mPacked = InterlockedCompareExchange((PLONG)(&mParms.mPacked), tExchange.mPacked, tCompare.mPacked);

         // If the original and the compare values are the same then there
         // was no preemption and the exchange was a success, so exit the 
         // loop. If they were not the same then retry.
         if (tOriginal.mPacked == tCompare.mPacked) break;
      }
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
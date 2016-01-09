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

   // Queue capacity
   static const LONG cCapacity = 4;
   
   //---------------------------------------------------------------------------
   // These two variables are each 16 bits and they are packed into a 32 bit 
   // structure because the atomic compare exchange operation used works on
   // 32 bit integers. This limits the queue size to 64K elements. The only 
   // code that can safely change these variables is contained here. Any other
   // code should be read only.
   //
   // WriteIndex is used to circularly index into queue memory for write 
   // operations. ReadAvailable is used to indicate the number of reads that 
   // are available. They have the following ranges:
   //
   //      0 <= WriteIndex    <= Capacity-1
   //      0 <= ReadAvailable <= Capacity
   //
   //      IF ReadAvailable == 0        THEN the queue is empty
   //      IF ReadAvailable == Capacity THEN the queue is full
   //
   //  The ReadIndex is derived from WriteIndex and ReadAvailable.
   //
   //      ReadIndex = WriteIndex - ReadAvailable;
   //      IF ReadIndex < 0 THEN ReadIndex = ReadIndex + Capacity;
   //---------------------------------------------------------------------------

   typedef union
   {
       struct    
       { 
         unsigned short mWriteIndex;  
         unsigned short mReadAvailable;  
       } Parms;
       signed mPacked;
   } LFQueueParms;

   LFQueueParms mParms;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Regionals

   static int mArray[1000];

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
   // This is called to start a write operation. If the queue is not full then
   // it succeeds. It updates the variable pointed by the input pointer with the 
   // WriteIndex that is to be used to access queue memory for the write, it
   // increments ReadAvailable and returns true. If it fails because the queue is 
   // full then it returns false.

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
   // This is a place holder.

   void finishWrite()
   {
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to start a read operation. If the queue is not empty then it 
   // succeeds, it  updates the variable pointed by the input pointer with the 
   // ReadIndex that is to be used to access queue memory for the read and returns 
   // true. If it fails because the queue is empty then it returns false.

   bool tryStartRead(int* aReadIndex)
   {
      // Store the current parms in a temp. This doesn't need to be atomic
      // because it is assumed to run on a 32 bit architecture.
      LFQueueParms tParms;
      tParms.mPacked = mParms.mPacked;

      // Exit if the queue is empty.
      if (tParms.Parms.mReadAvailable == 0) return false;

      // Update the read index
      int tReadIndex = tParms.Parms.mWriteIndex - tParms.Parms.mReadAvailable;
      if (tReadIndex < 0) tReadIndex = tReadIndex + cCapacity;

      // Store result
      *aReadIndex = tReadIndex;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This is called to finish a read operation. It decrements ReadAvailable.

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
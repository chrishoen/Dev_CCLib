/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"


#include "someQueueParms.h"
#include "someStateSX.h"
#include "smShare.h"

#include "someQueueTester.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Regional variables.

static int gWriteValue = 0;
static int gLastReadValue = 0;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read test for cpu-cpu queues.

bool doReadTestCpu()
{
   //***************************************************************************
   // Read from the value queue.

   if (gQueueParms.mSelect == 1)
   {
      int tValue;
      // Try to read from the queue.
      SM::gShare->mSX.mCpuReadCount++;
      if (SM::gShare->mValQueue.tryRead(&tValue))
      {
         SM::gShare->mSX.mCpuReadPassCount++;
         if (tValue != 0 && tValue != -2147483648)
         {
            // If this is not the first read then check
            // the value. It should be one greater than
            // the previous value.
            if (tValue - gLastReadValue != 1)
            {
               SM::gShare->mSX.mCpuReadErrorCount++;
            }
         }
         gLastReadValue = tValue;
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuReadEmptyCount++;
         return false;
      }
   }

   //***************************************************************************
   // Read from the object queue.

   if (gQueueParms.mSelect == 2)
   {
      Some::Class1 tClass1;
      int tValue;
      // Try to read from the queue.
      SM::gShare->mSX.mCpuReadCount++;
      if (SM::gShare->mObjQueue.tryRead(&tClass1))
      {
         tValue = tClass1.mCode1;
         SM::gShare->mSX.mCpuReadPassCount++;
         if (tValue != 0 && tValue != -2147483648)
         {
            // If this is not the first read then check
            // the value. It should be one greater than
            // the previous value.
            if (tClass1.mCode1 - gLastReadValue != 1)
            {
               SM::gShare->mSX.mCpuReadErrorCount++;
            }
         }
         gLastReadValue = tValue;
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuReadEmptyCount++;
         return false;
      }
   }
   
   //***************************************************************************
   // Read from the object queue.

   if (gQueueParms.mSelect == 3)
   {
      int tValue;
      SM::gShare->mSX.mCpuReadCount++;
      if (Some::Class1* tClass1 = SM::gShare->mObjQueue.startRead())
      {
         tValue = tClass1->mCode1;
         SM::gShare->mSX.mCpuReadPassCount++;
         if (tValue != 0 && tValue != -2147483648)
         {
            // If this is not the first read then check
            // the value. It should be one greater than
            // the previous value.
            if (tClass1->mCode1 - gLastReadValue != 1)
            {
               SM::gShare->mSX.mCpuReadErrorCount++;
            }
         }
         gLastReadValue = tValue;
         SM::gShare->mObjQueue.finishRead();
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuReadEmptyCount++;
         return false;
      }
   }
   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read test for rpu-cpu downlink queues.


bool doReadTestRpu()
{
   //***************************************************************************
   // Read from the value queue.

   if (SM::gShare->mSX.mQueueSelect == 1)
   {
      int tValue;
      // Try to read from the queue.
      SM::gShare->mSX.mCpuReadCount++;
      if (SM::gShare->mDownValQueue.tryRead(&tValue))
      {
         SM::gShare->mSX.mCpuReadPassCount++;
         if (tValue != 0 && tValue != -2147483648)
         {
            // If this is not the first read then check
            // the value. It should be one greater than
            // the previous value.
            if (tValue - gLastReadValue != 1)
            {
               SM::gShare->mSX.mCpuReadErrorCount++;
            }
         }
         gLastReadValue = tValue;
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuReadEmptyCount++;
         return false;
      }
   }
   
   //***************************************************************************
   // Read from the object queue.

   if (SM::gShare->mSX.mQueueSelect == 2)
   {
      Some::Class1 tClass1;
      int tValue;
      // Try to read from the queue.
      SM::gShare->mSX.mCpuReadCount++;
      if (SM::gShare->mDownObjQueue.tryRead(&tClass1))
      {
         tValue = tClass1.mCode1;
         SM::gShare->mSX.mCpuReadPassCount++;
         if (tValue != 0 && tValue != -2147483648)
         {
            // If this is not the first read then check
            // the value. It should be one greater than
            // the previous value.
            if (tClass1.mCode1 - gLastReadValue != 1)
            {
               SM::gShare->mSX.mCpuReadErrorCount++;
            }
         }
         gLastReadValue = tValue;
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuReadEmptyCount++;
         return false;
      }
   }
   
   //***************************************************************************
   // Read from the object queue.

   if (SM::gShare->mSX.mQueueSelect == 3)
   {
      int tValue;
      SM::gShare->mSX.mCpuReadCount++;
      if (Some::Class1* tClass1 = SM::gShare->mDownObjQueue.startRead())
      {
         tValue = tClass1->mCode1;
         SM::gShare->mSX.mCpuReadPassCount++;
         if (tValue != 0 && tValue != -2147483648)
         {
            // If this is not the first read then check
            // the value. It should be one greater than
            // the previous value.
            if (tClass1->mCode1 - gLastReadValue != 1)
            {
               SM::gShare->mSX.mCpuReadErrorCount++;
            }
         }
         gLastReadValue = tValue;
         SM::gShare->mDownObjQueue.finishRead();
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuReadEmptyCount++;
         return false;
      }
   }
   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write test for cpu-cpu queues.

bool doWriteTestCpu()
{
   //***************************************************************************
   // Write to the value queue.

   if (gQueueParms.mSelect == 1)
   {
      SM::gShare->mSX.mCpuWriteCount++;
      // Try to write the value to to the queue. 
      if (SM::gShare->mValQueue.tryWrite(gWriteValue))
      {
         // The write was successful, so advance the value.
         gWriteValue++;
         SM::gShare->mSX.mCpuWritePassCount++;
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuWriteFullCount++;
         return false;
      }
   }

   //***************************************************************************
   // Write to the object queue.

   if (gQueueParms.mSelect == 2)
   {
      SM::gShare->mSX.mCpuWriteCount++;
      // Try to write the to the queue.
      Some::Class1 tClass1;
      tClass1.reset();
      tClass1.mCode1 = gWriteValue;
      if (SM::gShare->mObjQueue.tryWrite(&tClass1))
      {
         // The write was successful, so advance the value.
         gWriteValue++;
         SM::gShare->mSX.mCpuWritePassCount++;
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuWriteFullCount++;
         return false;
      }
   }

   //***************************************************************************
   // Write to the object queue.

   if (gQueueParms.mSelect == 3)
   {
      SM::gShare->mSX.mCpuWriteCount++;
      // Try to start a write the value to to the queue.
      Some::Class1* tClass1 = SM::gShare->mObjQueue.startWrite();
      if (tClass1)
      {
         // The start write was successful, so set and advance the value.
         tClass1->reset();
         tClass1->mCode1 = gWriteValue++;
         SM::gShare->mSX.mCpuWritePassCount++;
         // Finish the write.
         SM::gShare->mObjQueue.finishWrite();
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuWriteFullCount++;
         return false;
      }
   }

   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write test for rpu-cpu uplink queues.

bool doWriteTestRpu()
{
   //***************************************************************************
   // Write to the value queue.

   if (SM::gShare->mSX.mQueueSelect == 1)
   {
      SM::gShare->mSX.mCpuWriteCount++;
      // Try to write the value to to the queue. 
      if (SM::gShare->mUpValQueue.tryWrite(gWriteValue))
      {
         // The write was successful, so advance the value.
         gWriteValue++;
         SM::gShare->mSX.mCpuWritePassCount++;
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuWriteFullCount++;
         return false;
      }
   }

   //***************************************************************************
   // Write to the object queue.

   if (SM::gShare->mSX.mQueueSelect == 2)
   {
      SM::gShare->mSX.mCpuWriteCount++;
      // Try to write the to the queue.
      Some::Class1 tClass1;
      tClass1.reset();
      tClass1.mCode1 = gWriteValue;
      if (SM::gShare->mUpObjQueue.tryWrite(&tClass1))
      {
         // The write was successful, so advance the value.
         gWriteValue++;
         SM::gShare->mSX.mCpuWritePassCount++;
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuWriteFullCount++;
         return false;
      }
   }

   //***************************************************************************
   // Write to the object queue.

   if (SM::gShare->mSX.mQueueSelect == 3)
   {
      SM::gShare->mSX.mCpuWriteCount++;
      // Try to start a write the value to to the queue.
      Some::Class1* tClass1 = SM::gShare->mUpObjQueue.startWrite();
      if (tClass1)
      {
         // The start write was successful, so set and advance the value.
         tClass1->reset();
         tClass1->mCode1 = gWriteValue++;
         SM::gShare->mSX.mCpuWritePassCount++;
         // Finish the write.
         SM::gShare->mUpObjQueue.finishWrite();
         return true;
      }
      else
      {
         SM::gShare->mSX.mCpuWriteFullCount++;
         return false;
      }
   }
   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read amd 

bool doReadTest()
{
   if (gQueueParms.mScope == 1)
   {
      return doReadTestCpu();
   }
   else if(gQueueParms.mScope >= 1)
   {
      return doReadTestRpu();
   }
   return false;
}

bool doWriteTest()
{
   if (gQueueParms.mScope == 1)
   {
      return doWriteTestCpu();
   }
   else if (gQueueParms.mScope >= 1)
   {
      return doWriteTestRpu();
   }
   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

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
// No constructor

bool doReadTest()
{
   // Read from the value queue.
   if (gQueueParms.mSelect == 1)
   {
      int tValue;
      // Try to read from the queue.
      SM::gShare->mSX.mReadCount++;
      if (SM::gShare->mValueQueue.tryRead(&tValue))
      {
         SM::gShare->mSX.mReadPassCount++;
         if (tValue)
         {
            // If this is not the first read then check
            // the value. It should be one greater than
            // the previous value.
            if (tValue - gLastReadValue != 1)
            {
               SM::gShare->mSX.mReadErrorCount++;
            }
            gLastReadValue = tValue;
         }
         return true;
      }
      else
      {
         SM::gShare->mSX.mReadEmptyCount++;
         return false;
      }
   }
   // Read from the object queue.
   if (gQueueParms.mSelect == 2)
   {
      SM::gShare->mSX.mReadCount++;
      if (Some::Class1* tClass1 = SM::gShare->mObjectQueue.startRead())
      {
         SM::gShare->mSX.mReadPassCount++;
         SM::gShare->mObjectQueue.finishRead();
         return true;
      }
      else
      {
         SM::gShare->mSX.mReadEmptyCount++;
         return false;
      }
   }
   return false;
}

bool doWriteTest()
{
   // Write to the value queue.
   if (gQueueParms.mSelect == 1)
   {
      SM::gShare->mSX.mWriteCount++;
      // Try to write the value to to the queue. 
      if (SM::gShare->mValueQueue.tryWrite(gWriteValue))
      {
         // The write was successful, so advance the value.
         gWriteValue++;
         SM::gShare->mSX.mWritePassCount++;
         return true;
      }
      else
      {
         SM::gShare->mSX.mWriteFullCount++;
         return false;
      }
   }
   // Write to the object queue.
   if (gQueueParms.mSelect == 2)
   {
      SM::gShare->mSX.mWriteCount++;
      Some::Class1* tClass1 = SM::gShare->mObjectQueue.startWrite();
      if (tClass1)
      {
         tClass1->reset();
         tClass1->mCode1 = gWriteValue++;
         SM::gShare->mSX.mWritePassCount++;
         SM::gShare->mObjectQueue.finishWrite();
         return true;
      }
      else
      {
         SM::gShare->mSX.mWriteFullCount++;
         return false;
      }
   }
   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

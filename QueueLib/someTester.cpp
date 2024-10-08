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

#include "someTester.h"

namespace Some
{

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
      SM::gShare->mSX.mReadCount++;
      if (SM::gShare->mValueQueue.tryRead(&tValue))
      {
         SM::gShare->mSX.mReadPassCount++;
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
      int tValue = 0;
      SM::gShare->mSX.mWriteCount++;
      if (SM::gShare->mValueQueue.tryWrite(tValue))
      {
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
      Some::Class1* tClass1 = SM::gShare->mObjectQueue.startWrite();
      if (tClass1)
      {
         tClass1->reset();
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

/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "ccSharedMemory.h"
#include "ccSharedSynch.h"
#include "ccBlockPool.h"
#include "someMyBlockA.h"

#define  _SOMETHREAD1_CPP_
#include "someThread1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Thread1::Thread1()
{
   // Set base class thread priority
   BaseClass::setThreadPriorityHigh();
   mTerminateFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Thread1::threadRunFunction()
{
   Prn::print(Prn::ThreadRun1, "Thread1::threadRunFunction BEGIN");

   //---------------------------------------------------------------------------
   // Loop until termination.
   while (true)
   {
      //------------------------------------------------------------------------
      // Local

      bool tEmptyFlag = true;
      int tCount = 0;
      CC::BlockHandle tBlockHandle;
      Some::MyBlockA* tBlock;

      //------------------------------------------------------------------------
      // Wait for semaphore.

      CC::gSharedSynch.getSemaphore();
      // Exit on termination flag.
      if (mTerminateFlag) break;

      //------------------------------------------------------------------------
      // Try to read from int queue.

      if (CC::gSharedSynch.mIntQueue.tryRead(&tCount))
      {
         tEmptyFlag = false;
         // Print.
         Prn::print(Prn::ThreadRun1, "IntQueue        read %d",tCount);
      }

      //------------------------------------------------------------------------
      // Try to read from block handle queue.

      if (CC::gSharedSynch.mBlockHandleQueue.tryRead(&tBlockHandle))
      {
         tEmptyFlag = false;
         // Get block pointer from handle.
         tBlock = (Some::MyBlockA*)CC::BlockHandle::ptr(tBlockHandle);
         // Process block.
         tCount = tBlock->mIdentifier;
         // Destroy block.
         delete tBlock;
         // Print.
         Prn::print(Prn::ThreadRun1, "BlockHandeQueue read %d",tCount);
      }

      //------------------------------------------------------------------------
      // If both empty

      if (tEmptyFlag)
      {
         Prn::print(Prn::ThreadRun1, "Queues EMPTY");
      }
   }

   Prn::print(Prn::ThreadRun1, "Thread1::threadRunFunction END");
}

//******************************************************************************

void Thread1::shutdownThread()
{
   // Set terminate
   mTerminateFlag = true;
   // Wake up thread.
   CC::gSharedSynch.putSemaphore();
   // Wait for terminate
   waitForThreadTerminate();
}   

}//namespace
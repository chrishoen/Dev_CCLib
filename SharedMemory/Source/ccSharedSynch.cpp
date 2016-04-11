/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "cc_functions.h"


#define  _CCSHAREDSYNCH_CPP_
#include "ccSharedSynch.h"

using namespace std;

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// pimpl idiom.

class SharedSynch::Specific
{
public:
   HANDLE mSemaphore;
   HANDLE mMutex;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

SharedSynch::SharedSynch()
{
   mSpecific=0;
   // All null.
   mFreeMemoryFlag = false;
   mMemory = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destructor, deallocate the array

SharedSynch::~SharedSynch()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the stack to a fixed size. It initializes member
// variables and and the stack array, given external memory.

void SharedSynch::initialize(bool aConstructorFlag,void* aMemory)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize memory.

   // Deallocate memory, if any exists.
   finalize();

   // pimpl idiom.
   mSpecific = new SharedSynch::Specific;

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mMemory = malloc(SharedSynch::getMemorySize());
      mFreeMemoryFlag = true;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mFreeMemoryFlag = false;
   }

   // Calculate memory sizes.
   int tIntQueueSize         = LFValueQueue<int>::getMemorySize(cNumElements);
   int tBlockHandleQueueSize = LFValueQueue<BlockHandle>::getMemorySize(cNumElements);

   // Calculate memory addresses.
   char* tIntQueueMemory         = (char*)mMemory;
   char* tBlockHandleQueueMemory = tIntQueueMemory + tIntQueueSize;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   mIntQueue.initialize(cNumElements,aConstructorFlag,tIntQueueMemory);
   mBlockHandleQueue.initialize(cNumElements,aConstructorFlag,tBlockHandleQueueMemory);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize interprocess synchronization.

   mSpecific->mSemaphore = CreateSemaphore(
      NULL,
      0,
      200,
      "AAATESTSHARESEM");

   mSpecific->mMutex = CreateMutex(
      NULL,
      FALSE,
      "AAATESTSHAREMUTEX");

   ReleaseMutex(mSpecific->mMutex);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SharedSynch::finalize()
{
   // Finalize memory.
   mIntQueue.finalize();

   if (mFreeMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
   }
   mMemory = 0;
   mFreeMemoryFlag = false;

   if (mSpecific)
   {
      // Finalize interprocess synchronization.
      CloseHandle(mSpecific->mSemaphore);
      CloseHandle(mSpecific->mMutex);
      delete mSpecific;
      mSpecific=0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns the number of bytes that an instance of this class
// will need to be allocated for it.

int SharedSynch::getMemorySize()
{
   int tIntQueueSize         = LFValueQueue<int>::getMemorySize(cNumElements);
   int tBlockHandleQueueSize = LFValueQueue<BlockHandle>::getMemorySize(cNumElements);
   int tMemorySize = tIntQueueSize + tBlockHandleQueueSize;
   return tMemorySize;
}

//******************************************************************************

bool SharedSynch::putSemaphore(void)
{
   return 0!=ReleaseSemaphore(mSpecific->mSemaphore,1,NULL);
}

//******************************************************************************

bool SharedSynch::getSemaphore(void)
{
   DWORD status = WaitForSingleObject(mSpecific->mSemaphore,INFINITE);
   return status == WAIT_OBJECT_0;
}

//******************************************************************************

bool SharedSynch::putMutex(void)
{
   return 0!=ReleaseMutex(mSpecific->mMutex);
}

//******************************************************************************

bool SharedSynch::getMutex(void)
{
   DWORD status = WaitForSingleObject(mSpecific->mMutex,INFINITE);
   return status == WAIT_OBJECT_0;
}
}//namespace
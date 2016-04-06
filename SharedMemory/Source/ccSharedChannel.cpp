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


#define  _CCSHAREDCHANNEL_CPP_
#include "ccSharedChannel.h"

using namespace std;

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// pimpl idiom.

class SharedChannel::Specific
{
public:
   HANDLE mSemaphore;
   HANDLE mMutex;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor, initialize members for an empty stack of size zero 

SharedChannel::SharedChannel()
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

SharedChannel::~SharedChannel()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the stack to a fixed size. It initializes member
// variables and and the stack array, given external memory.

void SharedChannel::initialize(bool aServerFlag,bool aConstructorFlag,void* aMemory)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize memory.

   // Deallocate memory, if any exists.
   finalize();

   // pimpl idiom.
   mSpecific = new SharedChannel::Specific;

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mMemory = malloc(SharedChannel::getMemorySize());
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
   int tQueueSize = LFValueQueue<int>::getMemorySize(cNumElements);

   // Calculate memory addresses.
   char* tQueueMemory = (char*)mMemory;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize variables.

   mQueue.initialize(cNumElements,aConstructorFlag,tQueueMemory);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize interprocess synchronization.

   if (aServerFlag)
   {
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
   else
   {
      mSpecific->mSemaphore = OpenSemaphore(
         EVENT_ALL_ACCESS | EVENT_MODIFY_STATE | SYNCHRONIZE,
         FALSE,
         "AAATESTSHARESEM");

      mSpecific->mMutex = OpenMutex(
         MUTEX_ALL_ACCESS | MUTEX_MODIFY_STATE | SYNCHRONIZE,
         FALSE,
         "AAATESTSHAREMUTEX");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SharedChannel::finalize()
{
   // Finalize memory.
   mQueue.finalize();

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

int SharedChannel::getMemorySize()
{
   int tQueueSize = LFValueQueue<int>::getMemorySize(cNumElements);
   int tMemorySize = tQueueSize;
   return tMemorySize;
}

//******************************************************************************

bool SharedChannel::putSemaphore(void)
{
   return 0!=ReleaseSemaphore(mSpecific->mSemaphore,1,NULL);
}

//******************************************************************************

bool SharedChannel::getSemaphore(void)
{
   DWORD status = WaitForSingleObject(mSpecific->mSemaphore,INFINITE);
   return status == WAIT_OBJECT_0;
}

//******************************************************************************

bool SharedChannel::putMutex(void)
{
   return 0!=ReleaseMutex(mSpecific->mMutex);
}

//******************************************************************************

bool SharedChannel::getMutex(void)
{
   DWORD status = WaitForSingleObject(mSpecific->mMutex,INFINITE);
   return status == WAIT_OBJECT_0;
}
}//namespace
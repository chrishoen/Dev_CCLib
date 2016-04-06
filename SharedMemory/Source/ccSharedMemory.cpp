/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <Windows.h>
#include "prnPrint.h"

#include "cc_functions.h"

#define  _CCSHAREDMEMORY_CPP_
#include "ccSharedMemory.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class SharedMemory::Specific
{
public:
   HANDLE mShareFileMap;
   HANDLE mSemaphore;
   HANDLE mMutex;
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Default Constructor.

SharedMemory::SharedMemory()
{
   mSpecific = 0;
   mFreeMemoryFlag = false;
   mMemory = 0;
   mNumBytes = 0;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void SharedMemory::initializeForServer(int aNumBytes)
{
   mSpecific = new SharedMemory::Specific;

   mSpecific->mShareFileMap=CreateFileMapping(
      INVALID_HANDLE_VALUE,
      NULL,
      PAGE_READWRITE,
      0,
      aNumBytes,
      "AAATESTSHAREMEMFILE");

   PVOID tMemory=MapViewOfFile(
      mSpecific->mShareFileMap,
      FILE_MAP_READ | FILE_MAP_WRITE,0,0,0);

   mMemory = tMemory;

   mSpecific->mSemaphore=CreateSemaphore(
      NULL,
      0,
      200,
      "AAATESTSHARESEM");

   mSpecific->mMutex=CreateMutex(
      NULL,
      FALSE,
      "AAATESTSHAREMUTEX");

   ReleaseMutex(mSpecific->mMutex);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void SharedMemory::initializeForClient()
{
   mSpecific = new SharedMemory::Specific;

   mSpecific->mShareFileMap=OpenFileMapping(
      FILE_MAP_READ | FILE_MAP_WRITE,FALSE,
      "AAATESTSHAREMEMFILE");

   PVOID tMemory=MapViewOfFile(
      mSpecific->mShareFileMap,
      FILE_MAP_READ | FILE_MAP_WRITE,0,0,0);

   mMemory = tMemory;

   mSpecific->mSemaphore=OpenSemaphore(
      EVENT_ALL_ACCESS | EVENT_MODIFY_STATE | SYNCHRONIZE,
      FALSE,
      "AAATESTSHARESEM");

   mSpecific->mMutex=OpenMutex(
      MUTEX_ALL_ACCESS | MUTEX_MODIFY_STATE | SYNCHRONIZE,
      FALSE,
      "AAATESTSHAREMUTEX");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SharedMemory::finalize()
{
   CloseHandle(mSpecific->mShareFileMap);
   CloseHandle(mSpecific->mSemaphore);
   CloseHandle(mSpecific->mMutex);

   delete mSpecific;
}

//******************************************************************************

bool SharedMemory::putSemaphore(void)
{
   return 0!=ReleaseSemaphore(mSpecific->mSemaphore,1,NULL);
}

//******************************************************************************

bool SharedMemory::getSemaphore(void)
{
   DWORD status = WaitForSingleObject(mSpecific->mSemaphore,INFINITE);
   return status == WAIT_OBJECT_0;
}

//******************************************************************************

bool SharedMemory::putMutex(void)
{
   return 0!=ReleaseMutex(mSpecific->mMutex);
}

//******************************************************************************

bool SharedMemory::getMutex(void)
{
   DWORD status = WaitForSingleObject(mSpecific->mMutex,INFINITE);
   return status == WAIT_OBJECT_0;
}
}//namespace
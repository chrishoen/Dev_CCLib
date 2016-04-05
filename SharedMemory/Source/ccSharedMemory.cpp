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
   mSpecific->mShareFileMap=CreateFileMapping(
      INVALID_HANDLE_VALUE,
      NULL,
      PAGE_READWRITE,
      0,
      aNumBytes,
      "TESTMYSHAREMEMFILE");

   PVOID tMemory=MapViewOfFile(
      mSpecific->mShareFileMap,
      FILE_MAP_READ | FILE_MAP_WRITE,0,0,0);

   mMemory = tMemory;

   mSpecific->mSemaphore=CreateSemaphore(
      NULL,
      0,
      200,
      "TESTMYSHARESEM");

   mSpecific->mMutex=CreateMutex(
      NULL,
      FALSE,
      "TESTMYSHAREMUTEX");

   ReleaseMutex(mSpecific->mMutex);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void SharedMemory::initializeForClient()
{
   mSpecific->mShareFileMap=OpenFileMapping(
      FILE_MAP_READ | FILE_MAP_WRITE,FALSE,
      "TESTMYSHAREMEMFILE");

   PVOID tMemory=MapViewOfFile(
      mSpecific->mShareFileMap,
      FILE_MAP_READ | FILE_MAP_WRITE,0,0,0);

   mMemory = tMemory;

   mSpecific->mSemaphore=OpenSemaphore(
      EVENT_ALL_ACCESS | EVENT_MODIFY_STATE | SYNCHRONIZE,
      FALSE,
      "TESTMYSHARESEM");

   mSpecific->mMutex=OpenMutex(
      MUTEX_ALL_ACCESS | MUTEX_MODIFY_STATE | SYNCHRONIZE,
      FALSE,
      "TESTMYSHAREMUTEX");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SharedMemory::finalize()
{
   CloseHandle(mSpecific->mShareFileMap);
   CloseHandle(mSpecific->mSemaphore);
   CloseHandle(mSpecific->mMutex);
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
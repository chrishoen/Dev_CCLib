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
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Default Constructor.

SharedMemory::SharedMemory()
{
   mSpecific = 0;
   mFreeMemoryFlag = false;
   mMemory1 = 0;
   mMemory2 = 0;
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

   char* tMemory = (char*)MapViewOfFile(
      mSpecific->mShareFileMap,
      FILE_MAP_READ | FILE_MAP_WRITE,0,0,0);

   mMemory1 = tMemory;
   mMemory2 = tMemory + cMemorySize1;
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

   char* tMemory = (char*)MapViewOfFile(
      mSpecific->mShareFileMap,
      FILE_MAP_READ | FILE_MAP_WRITE,0,0,0);

   mMemory1 = tMemory;
   mMemory2 = tMemory + cMemorySize1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SharedMemory::finalize()
{
   CloseHandle(mSpecific->mShareFileMap);

   if (mSpecific)
   {
      delete mSpecific;
      mSpecific = 0;
   }
}

}//namespace
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
// pimpl idiom.
 
class SharedMemory::Specific
{
public:
   HANDLE mShareFileMap;
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor.

SharedMemory::SharedMemory()
{
   mSpecific = 0;
   mMemory = 0;
   mSynchMemory = 0;
   mBlockPoolMemory = 0;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Create the shared memory and calculate addresses.

void SharedMemory::initializeForServer(int aNumBytes)
{
   // pimpl idiom.
   mSpecific = new SharedMemory::Specific;

   // Create Shared memory.
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

   // Calculate addresses.
   mMemory          = tMemory;
   mSynchMemory     = tMemory;
   mBlockPoolMemory = tMemory + cc_round_upto16(cSynchMemorySize);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Open the shared memory and calculate addresses.

void SharedMemory::initializeForClient()
{
   // pimpl idiom.

   mSpecific = new SharedMemory::Specific;

   // Open Shared memory.
   mSpecific->mShareFileMap=OpenFileMapping(
      FILE_MAP_READ | FILE_MAP_WRITE,FALSE,
      "AAATESTSHAREMEMFILE");

   char* tMemory = (char*)MapViewOfFile(
      mSpecific->mShareFileMap,
      FILE_MAP_READ | FILE_MAP_WRITE,0,0,0);

   // Calculate addresses.
   mMemory          = tMemory;
   mSynchMemory     = tMemory;
   mBlockPoolMemory = tMemory + cc_round_upto16(cSynchMemorySize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close the shared memory.

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
/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <Windows.h>
#include "prnPrint.h"

#include "cc_functions.h"
#include "ccSharedMemory.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class SharedMemory::Specific
{
public:
   HANDLE mHandle;
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

void SharedMemory::initialize(char* aName, int aNumBytes)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize memory.

   mNumBytes = cc_round_upto16(aNumBytes);

   void* aMemory=0;
   // Deallocate memory, if any exists.
   finalize();

   // If the instance of this class is not to reside in external memory
   // then allocate memory for it on the system heap.
   if (aMemory == 0)
   {
      mMemory = malloc(mNumBytes);
      mFreeMemoryFlag = true;
   }
   // If the instance of this class is to reside in external memory
   // then use the memory pointer that was passed in.
   else
   {
      mMemory = aMemory;
      mFreeMemoryFlag = false;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SharedMemory::finalize()
{
   if (mFreeMemoryFlag)
   {
      if (mMemory)
      {
         free(mMemory);
      }
   }
   mMemory = 0;
   mFreeMemoryFlag = false;
}

}//namespace
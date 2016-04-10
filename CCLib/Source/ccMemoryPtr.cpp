/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "ccBlockPoolCentral.h"
#include "ccMemoryPtr.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructors.

MemoryPtr::MemoryPtr()
{
   mMemoryPtr = 0;
}

MemoryPtr::MemoryPtr(void* aMemoryPtr)
{
   mMemoryPtr  = aMemoryPtr;
}

void MemoryPtr::set(void* aMemoryPtr)
{
   mMemoryPtr  = aMemoryPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get memory pointer value.

void* MemoryPtr::vfetch()
{
   return mMemoryPtr;
}

char* MemoryPtr::cfetch()
{
   return (char*)mMemoryPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set null.

void MemoryPtr::setNull()
{
   mMemoryPtr = 0;
}

bool MemoryPtr::isNull()
{
   return mMemoryPtr==0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Add a number of bytes to the memory pointer.
// Return the original memory pointer as a void*.
// This changes the memory pointer.

void* MemoryPtr::vfetch_add(int aNumBytes)
{
   void* tVOriginalPtr = mMemoryPtr;
   char* tCPtr = ((char*)mMemoryPtr) + aNumBytes;
   mMemoryPtr  = (void*)tCPtr;
   return tVOriginalPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Add a number of bytes to the memory pointer.
// Return the original memory pointer as a char*.
// This changes the memory pointer.

char* MemoryPtr::cfetch_add(int aNumBytes)
{
   char* tCOriginalPtr = (char*)mMemoryPtr;
   char* tCPtr = ((char*)mMemoryPtr) + aNumBytes;
   mMemoryPtr  = (void*)tCPtr;
   return tCOriginalPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Subtract a number of bytes from the memory pointer.
// Return the original memory pointer as a void*.
// This changes the memory pointer.

void* MemoryPtr::vfetch_sub(int aNumBytes)
{
   void* tVOriginalPtr = mMemoryPtr;
   char* tCPtr = ((char*)mMemoryPtr) - aNumBytes;
   mMemoryPtr  = (void*)tCPtr;
   return tVOriginalPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Subtract a number of bytes from the memory pointer.
// Return the original memory pointer as a char*.
// This changes the memory pointer.

char* MemoryPtr::cfetch_sub(int aNumBytes)
{
   char* tCOriginalPtr = (char*)mMemoryPtr;
   char* tCPtr = ((char*)mMemoryPtr) - aNumBytes;
   mMemoryPtr  = (void*)tCPtr;
   return tCOriginalPtr;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Return the memory pointer plus a number of bytes as a void*.
// This does not change the memory pointer.

void* MemoryPtr::vplus(int aNumBytes)
{
   char*  tCPtr = ((char*)mMemoryPtr) + aNumBytes;
   void*  tVPtr = (void*)tCPtr;
   return tVPtr;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Return the memory pointer plus a number of bytes as a char*.
// This does not change the memory pointer.

char* MemoryPtr::cplus(int aNumBytes)
{
   char*  tCPtr = ((char*)mMemoryPtr) + aNumBytes;
   return tCPtr;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Return the memory pointer minus a number of bytes as a void*.
// This does not change the memory pointer.

void* MemoryPtr::vminus(int aNumBytes)
{
   char*  tCPtr = ((char*)mMemoryPtr) - aNumBytes;
   void*  tVPtr = (void*)tCPtr;
   return tVPtr;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Return the memory pointer minus a number of bytes as a char*.
// This does not change the memory pointer.

char* MemoryPtr::cminus(int aNumBytes)
{
   char*  tCPtr = ((char*)mMemoryPtr) - aNumBytes;
   return tCPtr;
}

} //namespace


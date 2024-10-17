/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "risPortableCalls.h"

#include "risMemMap.h"

namespace Ris
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// Max string size used in subsequent calls.
static const int cPageSize = 4096;

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Instruct the OS kernel to map a physical address to a virtual address.
// Return the virtual address.

char* getMemMapVirtualAddress(unsigned aPhysicalAddress, int aNumPages)
{
   // Calculate the number of bytes to allocate.
   size_t tLength = cPageSize * aNumPages;
   unsigned tMask = tLength - 1;

   // Get the physical address from the input. Mask according to the length.
//   off_t tPhysicalAddress = (off_t)aPhysicalAddress & (off_t)~tMask;
   off_t tPhysicalAddress = (off_t)aPhysicalAddress;

   // Open a file to the memory system.
   int tMemoryFd = open("/dev/mem", O_RDWR | O_SYNC);

   // Map the memory.
   char* tVirtualAddress = (char*)mmap(0, tLength, PROT_READ | PROT_WRITE, MAP_SHARED, tMemoryFd, tPhysicalAddress);

   // Close the file.
   close(tMemoryFd);

   // Done.
   return tVirtualAddress;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Unmap the virtual address.

void unmapMemMapVirtualAddress(void* aVirtualAddress, int aNumPages)
{
   // Calculate the number of bytes to allocate.
   size_t tLength = cPageSize * aNumPages;

   munmap(aVirtualAddress, tLength);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


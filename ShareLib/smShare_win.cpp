/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <stdio.h>

#include "smShareParms.h"

#include "smShare.h"

namespace SM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create a shared memory region for the global instance and call placement
// new with the shared memory address. If this is the first process to access
// the region (it was created created, not opened) then initialize the global
// instance. Otherwise, do not initialize it, because the first process
// already did.

void initializeShare(bool aInitVars)
{
   printf("initializeShare BEGIN\n");
   // Allocate heap memory.
   int tNumPages = SM::gShareParms.mNumPages1;
   size_t tSize = tNumPages*4096;
   void* tVirtualAddress1 = malloc(tSize);

   // Constructor new on the virtual address.
   // gShare = (Share*)tVirtualAddress1;
   gShare = new(tVirtualAddress1)Share;

   printf("Share size               %d\n", (int)sizeof(Share));
   printf("Share ResourceCount      %d\n", gShare->mResourceCount);

   // Initialize sync codes.
   gShare->mCpuSync1 = 101;
   gShare->mCpuSync2 = 102;

   // For cpu scope, always initialize members. For rpu scope, 
   // the rpu will initialize, so it must always run first.
   if (aInitVars)
   {

      // Initialize members.
      gShare->initialize();
   }
   printf("initializeShare END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close the shared memory region for the global instance.

void finalizeShare()
{
   free(gShare);
   printf("finalizeShare\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

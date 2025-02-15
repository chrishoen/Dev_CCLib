/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include "risMemMap.h"
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
   // Map the physical address to a virtual address.
   unsigned tPhysicalAddress1 = SM::gShareParms.mAddress1;
   int tNumPages = SM::gShareParms.mNumPages1;
   char* tVirtualAddress1 = Ris::getMemMapVirtualAddress(tPhysicalAddress1, tNumPages);

   // Constructor new on the virtual address.
   // gShare = (Share*)tVirtualAddress1;
   gShare = new(tVirtualAddress1)Share;

   printf("Share address            %d %x\n", tNumPages, tPhysicalAddress1);
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
   int tNumPages = SM::gShareParms.mNumPages1;
   Ris::unmapMemMapVirtualAddress(gShare, tNumPages);
   printf("finalizeShare\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

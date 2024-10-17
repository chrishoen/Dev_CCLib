#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risBaseDir.h"
#include "someMemoryParms.h"
#include "someQueueParms.h"
#include "smShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("QueueTest2 Program****************************************BEGIN\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Program.

   // Enter process.
   Ris::Threads::enterProcessHigh();

   // Set the base directory to the current directory.
   Ris::setBaseDirectoryToCurrent();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters files.

   // Read parameters files.
   Some::gMemoryParms.reset();
   Some::gMemoryParms.readSection("Default");

   // Read parameters files.
   Some::gQueueParms.reset();
   Some::gQueueParms.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize shared memory.

   // Initialize shared memory.
   SM::initializeShare(Some::gQueueParms.mScope == 1);
   // Special.
   if (Some::gQueueParms.mScope == 1)
   {
      SM::gShare->mSX.mQueueSelect = Some::gQueueParms.mSelect;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::Show1, true);
   Prn::setFilter(Prn::Show2, false);
   Prn::setFilter(Prn::Show3, false);
   Prn::setFilter(Prn::Show4, false);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resources.

void main_finalize()
{
   // Finalize print facility.
   Prn::finalizePrint();

   // Finalize shared memory.
   SM::finalizeShare();

   // Exit process.
   Ris::Threads::exitProcess();

   // Done.
   printf("\n");
   printf("QueueTest2 Program****************************************END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

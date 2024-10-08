#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risBaseDir.h"
#include "someQueueParms.h"
#include "smShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("QueueTest1 Program****************************************BEGIN\n");

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
   // Initialize.

   // Initialize shared memory.
   SM::initializeShare();

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters files.

   // Read parameters files.
   Some::gQueueParms.reset();
   Some::gQueueParms.readSection("default");
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
   printf("QueueTest1 Program****************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

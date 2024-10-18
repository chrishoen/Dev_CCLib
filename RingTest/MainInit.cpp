#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risBaseDir.h"
#include "someRingParms.h"
#include "smShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("RingTest Program****************************************BEGIN\n");

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
   Some::gRingParms.reset();
   Some::gRingParms.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Initialize shared memory. If this is scope1, cpu only,
   // then initialize the variables. If this is scope2, cpu-rpu,
   // then the rpu initializes the variables.
   SM::initializeShare(Some::gRingParms.mScope == 1);

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
   printf("RingTest Program****************************************END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

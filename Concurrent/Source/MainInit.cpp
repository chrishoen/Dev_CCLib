#include "stdafx.h"

#include <windows.h>

#include "GSettings.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

static const int cTimerPeriod = 10;

void enterProcessHigh()
{
   // Set process priority class and affinity
   SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
   SetProcessAffinityMask(GetCurrentProcess(), 0x3E);

   // Set process timer resolution to one millisecond
   timeBeginPeriod(cTimerPeriod);
   // Seed random numbers
   my_srand();
}

//******************************************************************************

void exitProcess()
{
   timeEndPeriod(cTimerPeriod);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void main_initialize(int argc,char** argv)
{
   // Read settings file
   gGSettings.readFromFileName();
   gGSettings.show();

   // Enter process
   enterProcessHigh();

   // Initialize print facility
   Prn::resetPrint();
   Prn::initializePrint();

   // Initialize print filters
   Prn::setFilter(Prn::SocketInit1, false);
   Prn::setFilter(Prn::SocketInit2, true);
   Prn::setFilter(Prn::SocketRun1,  false);
   Prn::setFilter(Prn::SocketRun2,  false);
   Prn::setFilter(Prn::SocketRun3,  false);
   Prn::setFilter(Prn::SocketRun4,  false);

   Prn::setFilter(Prn::ThreadRun1,  true);
   Prn::setFilter(Prn::ThreadRun2,  false);
   Prn::setFilter(Prn::ThreadRun3,  true);
   Prn::setFilter(Prn::ThreadRun4,  false);

   Prn::setFilter(Prn::ProcRun1,    true);
   Prn::setFilter(Prn::ProcRun2,    true);
   Prn::setFilter(Prn::ProcRun3,    false);
   Prn::setFilter(Prn::ProcRun4,    true);

   Prn::setFilter(Prn::ViewRun1,    true, 1);
   Prn::setFilter(Prn::ViewRun2,    true, 1);
   Prn::setFilter(Prn::ViewRun3,    false,1);
   Prn::setFilter(Prn::ViewRun4,    true, 1);

   Prn::setFilter(Prn::QCallInit1, true);
   Prn::setFilter(Prn::QCallInit2, true);
   Prn::setFilter(Prn::QCallRun1,  false);
   Prn::setFilter(Prn::QCallRun2,  false);
   Prn::setFilter(Prn::QCallRun3,  false);
   Prn::setFilter(Prn::QCallRun4,  false);

   Prn::print(0,"Concurrent*******************************************BEGIN");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize

void main_finalize()
{
   Prn::print(0,"Concurrent*******************************************END");

   // Close print
   Prn::finalizePrint();

   // Exit process
   exitProcess();
}


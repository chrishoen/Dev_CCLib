#include <windows.h>

#include "prnPrint.h"
#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"

#include "ccBlockPool.h"
#include "someBlockPoolIndex.h"
#include "someMyBlockA.h"
#include "someMyBlockB.h"


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void main_initialize(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process

   Ris::Threads::enterProcessHigh();

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
   Prn::setFilter(Prn::ThreadRun4,  true);

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

   Prn::print(0,"MyTreeBlock*******************************************BEGIN");

   // Initialize block pools.
   CC::initializeBlockPoolFacility();

   // Create block pool.
   CC::BlockPoolParms tBlockPoolParms;

   tBlockPoolParms.reset();
   tBlockPoolParms.mPoolIndex = Some::cBlockPoolIndex_MyBlockA;
   tBlockPoolParms.mNumBlocks = 1000;
   tBlockPoolParms.mBlockSize = sizeof(Some::MyBlockA);
   CC::createBlockPool(&tBlockPoolParms);

   tBlockPoolParms.reset();
   tBlockPoolParms.mPoolIndex = Some::cBlockPoolIndex_MyBlockB;
   tBlockPoolParms.mNumBlocks = 1000;
   tBlockPoolParms.mBlockSize = sizeof(Some::MyBlockB);
   CC::createBlockPool(&tBlockPoolParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize

void main_finalize()
{
   Prn::print(0,"MyTreeBlock*******************************************END");

   // Close print
   Prn::finalizePrint();

   // Finalize block pools.
   CC::finalizeBlockPoolFacility();

   // Exit process
   Ris::Threads::exitProcess();
}


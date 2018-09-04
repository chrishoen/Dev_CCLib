#pragma once

/*==============================================================================

Realtime infastructure library Threads

This file contains classes that encapsulate standard rtos multithreading
synchronization constructs. It supplies events, semaphores, and threads.
The purpose of the classes is to wrap the rtos api thread synchronization
calls.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This encapsulates a mutex semaphore.

   class MutexSemaphore
   {
   public:

      MutexSemaphore();             // Creates the mutex semaphore
      virtual ~MutexSemaphore();    // Deletes the mutex semaphore

      void lock   ();               // Lock the mutex
      void unlock ();               // Unlock the mutex

   protected:
      class Specific;
      Specific* mSpecific;
   };

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



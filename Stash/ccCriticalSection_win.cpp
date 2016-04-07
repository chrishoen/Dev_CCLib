/*==============================================================================

This file contains functions that imlement a critical section.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h> 

#include <stdio.h>
#include <assert.h>

#include "ccCriticalSection.h"

#pragma unmanaged

 namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Global variable

class CriticalSectionWrapper
{
public:
   CriticalSectionWrapper()
   {
      // Initialize the critical section one time only.
      InitializeCriticalSectionAndSpinCount(&mCriticalSection,0x80000400); 
   }

   ~CriticalSectionWrapper()
   {
    // Release resources used by the critical section object.
    DeleteCriticalSection(&mCriticalSection);
   }

   void enterCriticalSection()
   {
       // Request ownership of the critical section.
       EnterCriticalSection(&mCriticalSection); 
   }
   void leaveCriticalSection()
   {
       // Release ownership of the critical section.
       LeaveCriticalSection(&mCriticalSection);
   }
   
   CRITICAL_SECTION mCriticalSection; 
};

CriticalSectionWrapper gCriticalSectionWrapper;

void enterCriticalSection()
{
   gCriticalSectionWrapper.enterCriticalSection();
}

void leaveCriticalSection()
{
   gCriticalSectionWrapper.leaveCriticalSection();
}

}//namespace











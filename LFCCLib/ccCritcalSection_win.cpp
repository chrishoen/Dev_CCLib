/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <windows.h> 

#include "ccCriticalSection.h"

#pragma unmanaged

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Created a critical section. Pass the returned code to the following
// functions.

void* createCriticalSection()
{
   CRITICAL_SECTION* tCriticalSection = new CRITICAL_SECTION;
   InitializeCriticalSectionAndSpinCount(tCriticalSection, 0x80000400);
   return (void*)tCriticalSection;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Enter a critical section. This is used to lock a resource for a short
// time interval.

void enterCriticalSection(void* aCriticalSection)
{
   EnterCriticalSection((CRITICAL_SECTION*)aCriticalSection);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Leave a critical section. This is used to unlock a resource.

void leaveCriticalSection(void* aCriticalSection)
{
   LeaveCriticalSection((CRITICAL_SECTION*)aCriticalSection);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Destroy a critical section.

void destroyCriticalSection(void* aCriticalSection)
{
   DeleteCriticalSection((CRITICAL_SECTION*)aCriticalSection);
   delete aCriticalSection;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


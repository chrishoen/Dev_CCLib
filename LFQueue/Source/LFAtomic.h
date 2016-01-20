#ifndef _LFATOMIC_H_
#define _LFATOMIC_H_

#include <windows.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Easier to use compare and exchange functions.

inline bool boolCompExch(int* aDestin, int aExchange, int aCompare)
{
   int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
   return tOriginal == aCompare; 
}

inline int valCompExch(int* aDestin, int aExchange, int aCompare)
{
   int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
   return tOriginal; 
}

#endif


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

inline bool my_bool_compexch(int* aDestin, int aExchange, int aCompare)
{
   int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
   return tOriginal == aCompare; 
}

inline int my_val_compexch(int* aDestin, int aExchange, int aCompare)
{
   int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
   return tOriginal; 
}

inline int my_fetch_add(int* aDestin, int aExchange, int aCompare)
{
   int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
   return tOriginal; 
}

#endif

